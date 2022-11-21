#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Renderer.h"


struct ShaderProgramSource {
    std::string  VertexProgramSource;
    std::string FragmentProgramSource;

};
static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::stringstream ss[2];
    enum class shadertype 
    {
        NONE=-1 , VERTEX=0, FRAGMENT=1
    };
    shadertype type = shadertype::NONE;
    std::ifstream stream(filepath);
    std::string line;
    while (getline(stream, line) ){
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = shadertype::VERTEX;
            else if (line.find("fragment")!= std::string::npos)
                type = shadertype::FRAGMENT;
        }
        else {
            ss[int(type)] << line << "\n";
        }
    }
    return { ss[0].str(),ss[1].str() };
}

static unsigned int compileshader(unsigned int  type, const std::string& source ) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1, &src, nullptr);
    glCompileShader(id);
    //Erore handling must be done here 
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result==GL_FALSE) {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout <<"faild to compile "<<(type == GL_VERTEX_SHADER ? "FRAGMENT":"SHADER" )<< message;
        glDeleteShader(id);
        return 0;
    }


    return id;
}
static int CreateShader(const std::string& vertexshader, const std::string& fragmentshader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileshader(GL_VERTEX_SHADER, vertexshader);
    unsigned int fs = compileshader(GL_FRAGMENT_SHADER, fragmentshader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;

}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        std::cout << "erore " << std::endl;
    

    float position[] = {
        -.5,-.5,
         .5,-.5,
         .5, .5,
          -.5,.5,
          
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };
    std::cout << glGetString(GL_VERSION) << std::endl;
    //std::cout << sizeof(position)<<std::endl;

    unsigned int vao;
    GLLOGCALL(glGenVertexArrays(1, &vao));
    GLLOGCALL(glBindVertexArray(vao));


    //###########################

    //GLLOGCALL(unsigned int ibo);
    //GLLOGCALL(glGenBuffers(1, &ibo));
    //GLLOGCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    //GLLOGCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
    
    ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
    //std::cout<< "vertext Shader"<< std::endl;
    //std::cout << source.VertexProgramSource << std:: endl;
    //std::cout << "fragment Shader" << std::endl;
    //std::cout << source.VertexProgramSource << std:: endl;


    unsigned int shader = CreateShader(source.VertexProgramSource, source.FragmentProgramSource);
    glUseProgram(shader);
    

    GLLOGCALL(int location = glGetUniformLocation(shader, "u_color"));
    //GLLOGCALL(int position1 = glGetUniformLocation(shader, "position"));
    
    ASSERT(location != -1);
    GLLOGCALL(glUniform4f(location, 0.2, .3, .8, 1.));
    glfwSwapInterval(1);
    float r = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLLOGCALL(glClear(GL_COLOR_BUFFER_BIT));
        //GLClearerore();
        GLLOGCALL(glUniform4f(location, r, .3, .8, 1.));
        GLLOGCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        if (r > 1)
            r = 0;
        r += .05f;
        //ASSERT( GLCheckerore());
        /* Swap front and back buffers */
        GLLOGCALL(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLLOGCALL(glfwPollEvents());
    }
    GLLOGCALL(glDeleteProgram(shader));
    GLLOGCALL(glfwTerminate());
    return 0;
}