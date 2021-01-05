import {E} from './Element.js';
import Table from './Table.js';
import {get, hex, toHexString, hexStringToData, makeList, makeCollapsibleList, makeDescriptionAndNotes} from './Util.js';

import Context from './gl/Context.js';
import ViewControl from './gl/ViewControl.js';
import LightControl from './gl/LightControl.js';
import VertexBuffer from './gl/gx/VertexBuffer.js';
import ModFile from './ModFile.js';

class Renderer {
    constructor(view) {
        this.view  = view;
        this.ctx   = view.ctx;
    }

    reset() {
        /** Reset all state to default.
         */
        this._didRender = false;
        this.ctx.gx.reset();
    }

    render() {
        const gl = this.ctx.gl;
        const gx = this.ctx.gx;
        this.reset();
        //gx._setShaderMtxs();

        this.vtxBuf = new VertexBuffer(gx);
        gx.program.use();
        gx._setShaderMtxs();
        gl.enable(gl.BLEND);
        //draw cube at origin
        //this._drawCube({
        //    x:0, y:0, z:0, size:10, fill:true,
        //})
        this._drawGrid();
        this._drawBlocks();
        //this._drawObjects();
        //this.vtxBuf.bind();
        //gx.program.use();
        //gx._setShaderMtxs();
        //gl.drawArrays(gl.LINE_LOOP, 0, 16*this.view.romlist.items.length);
    }

    renderPickBuffer() {
        //this._renderer.render();
    }

    _drawGrid() { //draw planes for map grid
        console.log("Draw map grid...");
        const gl = this.ctx.gl;
        const gx = this.ctx.gx;
        let count = 0;
        let first = this.vtxBuf.vtxCount;
        const map = this.view.map;
        for(let z=0; z<map.height; z++) {
            for(let x=0; x<map.width; x++) {
                let block = map.getBlockByPos(x, z);
                if(block) {
                    let mod  = block.mod;
                    let sub  = block.sub;
                    let unk1 = block.unk1;
                    let unk2 = block.unk2;
                    let col  = [
                        (block.mod & 0x1F) << 5,
                        (block.sub & 0x3F) << 2,
                        block.unk1,
                        0x7F];
                    let bx   = x * 640, bz = z * 640;
                    let v    = [ //XXX this is very wasteful. use indexed rendering.
                        {POS:[bx+ 10, 0, bz+ 10], COL0:col},
                        {POS:[bx+620, 0, bz+ 10], COL0:col},
                        {POS:[bx+620, 0, bz+620], COL0:col},
                        {POS:[bx+ 10, 0, bz+620], COL0:col},
                    ];
                    this.vtxBuf.addVtxs(v[0], v[1], v[2], v[0], v[2], v[3]);
                    count += 6;
                }
            }
        }
        this.vtxBuf.bind();
        gl.drawArrays(gl.TRIANGLES, first, count);
    }

    _drawBlocks() { //draw actual map geometry
        console.log("Draw blocks...");
        const map = this.view.map;
        const gl = this.ctx.gl;
        const color = [0, 0, 0, 255];
        let first = this.vtxBuf.vtxCount;
        let count = 0;
        for(let y=0; y<map.height; y++) {
            for(let x=0; x<map.width; x++) {
                const block = this.view.blocks[(y*map.width)+x];
                if(!block) continue;

                for(let vtx of block.vtxs) {
                    this.vtxBuf.addVtx({POS:vtx, COL0:color});
                    count++;
                }
            }
        }
        this.vtxBuf.bind();
        gl.drawArrays(gl.POINTS, first, count);
    }

    _drawObjects() { //draw cubes at objects
        console.log("Draw objects...");
        for(let item of this.view.romlist.items) {
            this._drawCube({
                x: item.objDef.x,
                y: item.objDef.y,
                z: item.objDef.z,
                color: [
                    ( item.objDef.type       & 0x0F) << 4,
                    ((item.objDef.type >> 4) & 0x0F) << 4,
                    ((item.objDef.type >> 8) & 0x0F) << 4,
                    255,
                ],
                size:10, fill:true,
            })
        }
    }

    _drawCube(cube) {
        /** Draw a cube.
         *  @param cube.x X coord of center.
         *  @param cube.y Y coord of center.
         *  @param cube.z Z coord of center.
         *  @param [cube.size=1] width of cube.
         *  @param [cube.color=[255,0,0,255]] cube color.
         *  @param [cube.fill=false] whether to fill rather than outline.
         */
        /*4________5
          /|      /.
         / |     / |
        .-------.  |
        |0 | __1|__|6
        |  /7   | /
        |3/    2|/
        '-------' */
        let first = this.vtxBuf.vtxCount;
        const gl = this.ctx.gl;
        const gx = this.ctx.gx;
        const vtxs = [
            [-1, -1, -1], [ 1, -1, -1], [ 1,  1, -1], [-1,  1, -1],
            [-1, -1,  1], [ 1, -1,  1], [ 1,  1,  1], [-1,  1,  1],
        ];
        let idxs;
        if(cube.fill) idxs = [ //triangles
            0, 1, 2,   0, 2, 3,   4, 5, 6,   4, 6, 7, //-Z, +Z faces
            0, 4, 7,   0, 7, 3,   1, 5, 6,   1, 6, 2, //-X, +X faces
            0, 4, 5,   0, 5, 1,   3, 7, 6,   3, 6, 2, //-Y, +Y faces
        ];
        else idxs = [ //line loop
            //follow the diagram above, connecting all lines.
            //it's not possible to do this without repeating some
            //lines; fortunately this doesn't matter.
            0, 1, 2, 3,  0, 4, 5, 6,  7, 4, 5, 1,  2, 6, 7, 3,
        ];
        const color = cube.color == undefined ? [255,0,0,255] : cube.color;
        const size  = cube.size == undefined ? 1 : cube.size;
        const s = size / 2;
        const x = cube.x - (size/2);
        const y = cube.y - (size/2);
        const z = cube.z - (size/2);
        for(let i of idxs) {
            let xs = vtxs[i][0], ys = vtxs[i][1], zs = vtxs[i][2];
            this.vtxBuf.addVtx({POS:[
                xs < 0 ? x-s : x+s,
                ys < 0 ? y-s : y+s,
                zs < 0 ? z-s : z+s,
            ], COL0:color});
        }
        //this.vtxBuf.bind();
        //gx.program.use();
        //gx._setShaderMtxs();
        //gl.drawArrays(cube.fill ? gl.TRIANGLES : gl.LINE_LOOP, 0, idxs.length);
        this.vtxBuf.bind();
        gl.drawArrays(cube.fill ? gl.TRIANGLES : gl.LINE_LOOP, first, idxs.length);
    }
}

export default class MapView {
    /** A page that attempts to render a map.
     */
    constructor(app) {
        this.app = app;
        this.element = E.div(E.canvas({id:'glCanvas'}));
    }

    getTitle() {
        const name = this.map ? this.map.internalName : this.romlistName;
        return `${name} - Map View`;
    }

    async run() {
        this.romlistName = this.app.params.get('romlist');
        if(this.romlistName == null) {
            const id = this.app.params.get('id');
            this.romlistName = this.app.game.maps[id].romlistName;
        }
        this.romlist = await this.app.game.getRomList(this.romlistName);

        this.map = this.app.game.maps[this.app.params.get('id')];
        await this.map.readMapsBin();

        await this._loadBlocks();

        this.ctx = new Context('#glCanvas');
        await this.ctx.loadPrograms();

        this.viewControl = new ViewControl(this.ctx);
        this.lightControl = new LightControl(this.ctx);
        this.element.append(
            E.div({id:'controls'},
                this.viewControl.element,
                this.lightControl.element,
                E.div({id:'glPicker'}),
            ),
        );

        this.renderer = new Renderer(this);
        this.ctx.setRenderer(this.renderer);

        this.viewControl.set({
            pos: {x:-2000, y:500, z:-1900},
            rot: {x:   75, y: 15, z:    0},
        });
        this.lightControl.set({
            ambColor: {r:255, g:255, b:255},
        });

        this.ctx.redraw();
        this.ctx.gx.printStats();
    }

    async _loadBlocks() {
        const trkBlk = new DataView((await get({ //XXX per-version path
            path:         `/disc/TRKBLK.tab`,
            mimeType:     'application/octet-stream',
            responseType: 'arraybuffer',
        })).response);

        const dir   = this.map.dirName;
        const mods  = {};
        this.blocks = [];
        for(let y=0; y<this.map.height; y++) {
            for(let x=0; x<this.map.width; x++) {
                let block = this.map.getBlockByPos(x, y);
                if(!block) {
                    this.blocks.push(null);
                    continue;
                }

                let modId = block.mod;
                if(modId >= 4) modId++; //dunno why the game does this
                if(!mods[modId]){
                    mods[modId] = await (new ModFile(this.app.game)).load(
                        `${dir}/mod${modId}.zlb.bin`,
                        `${dir}/mod${modId}.tab`);
                    //console.log("mod load", modId, mods[modId]);
                }
                const offs = trkBlk.getInt16(this.map.dirId * 2);
                const blk = mods[modId].blocks[block.sub+offs];
                //console.log("block %d.%d + %d", block.mod, block.sub, offs, blk);
                this.blocks.push(blk);
            }
        }
    }
}