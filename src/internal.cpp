#include "internal.h"

namespace jade::internal {
    void Allocs::free() {
        for (void* arr : arrs) delete[] arr;
        glDeleteVertexArrays((GLsizei)vaos.size(), vaos.data());
        glDeleteBuffers((GLsizei)bufs.size(), bufs.data());
        glDeleteTextures((GLsizei)texs.size(), texs.data());
        for (GLuint prog : progs) glDeleteProgram(prog);
        for (FT_Face face : faces) FT_Done_Face(face);
    }
}
