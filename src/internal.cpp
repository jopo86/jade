#include "internal.h"

namespace jade::internal {
    void Allocs::free() {
        for (void* arr : arrs) delete[] arr;
        glDeleteVertexArrays(vaos.size(), vaos.data());
        glDeleteBuffers(bufs.size(), bufs.data());
        glDeleteTextures(texs.size(), texs.data());
        for (GLuint prog : progs) glDeleteProgram(prog);
    }
}
