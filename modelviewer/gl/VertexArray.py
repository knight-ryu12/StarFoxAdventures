import logging; log = logging.getLogger(__name__)
import OpenGL.GL as gl
from OpenGL.raw.GL.ARB.vertex_array_object import glGenVertexArrays, \
glBindVertexArray

class VertexArray:
    """GL vertex array object."""

    class _Binding:
        """Object returned by VertexArray.bound()."""

        def __init__(self, arr):
            self.arr = arr

        def __enter__(self):
            self.arr.bind()
            return self.arr

        def __exit__(self, type, value, traceback):
            self.arr.unbind()


    def __init__(self, ctx):
        self.ctx = ctx
        self.id  = ctx.glGenVertexArrays(1)
        self.bind()


    def bind(self):
        #log.debug("Bind vertex array %d", self.id)
        self.ctx.glBindVertexArray(self.id)

    def unbind(self):
        self.ctx.glBindVertexArray(0)


    def bound(self):
        """Create a temporary binding: `with myArray.bound() ...`"""
        return self._Binding(self)


    def render(self, mode, count=None, offset=0):
        """Render vertex array.

        mode: Type of primitives; eg GL_POINTS, GL_LINES...
        count: Number of indices to render.
        offset: First index offset to render.
        """
        self.bind()
        # XXX count=None should mean all... but how do we know how many?
        self.ctx.glDrawArrays(mode, offset, count)


    def renderInstanced(self, mode, offset=0, length=0, count=0):
        """Render multiple instances of vertex array.

        mode: Type of primitives; eg GL_POINTS, GL_LINES...
        offset: First index offset to render.
        length: Number of indices to render.
        count: Number of instances of this range to render.
        """
        self.bind()
        self.ctx.glDrawArraysInstanced(mode, offset, length, count)
