#pragma once
#include <glew.h>
#define ASSERT(x) if(!(x)) __debugbreak();
//#define print(x) std::cout<<x
#define GLLOGCALL(x) GLClearerore();\
    x;\
   ASSERT(GLCheckerore(#x,__FILE__,__LINE__))

static void GLClearerore();
static bool GLCheckerore(const char* filename, const char* funciton, int line);