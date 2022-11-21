#include <iostream>
#include "Renderer.h"
static void GLClearerore() {
    while (glGetError() != GL_NO_ERROR);
}
static bool GLCheckerore(const char* filename, const char* funciton, int line) {
    /*  bool has_erore = true;*/
    while (GLenum erore = glGetError()) {
        std::cout << "Opengl Erore" << "   " << filename << "    " << funciton << "     " << line << "       " << erore << std::endl;
        //has_erore = false;
        return false;
    }
    return true;
    //return has_erore;
}
