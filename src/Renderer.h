#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


//for raise(SIGTRAP) function in gcc - instead of __debugbreak()
#include <signal.h>
#include <iostream>


#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x)   GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))




void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{

    private:
    public:
        void Clear() const;
        void Draw      (const VertexArray& va, const IndexBuffer& ib, const Shader& Shader) const;
        void DrawLines (const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};