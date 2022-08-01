#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource Shader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1,
        Vertex = 0,
        Fragment = 1
    };

    ShaderType currentType = ShaderType::NONE;
    std::string line;
    std::stringstream ss[2];
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                currentType = ShaderType::Vertex;
            if (line.find("fragment") != std::string::npos)
                currentType = ShaderType::Fragment;
        }
        else
            ss[(int)currentType] << line << "\n";
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int CompileShader(const std::string& Source, unsigned int type) {

    unsigned int id = glCreateShader(type);
    const char* src = Source.c_str();
    
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);

        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);

        std::cout << "Failed to compile" << std::endl << message << std::endl;
    }

    return id;


}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

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

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "!Error!" << std::endl;

    std::cout << "gl version " << glGetString(GL_VERSION);
    
    //Shader and stuff
    float positions[6] = {
        -1.0f,-1.0f,
         0.0,  1.0,
         1.0f,-1.0f
    };

    //Vertex buffer
    unsigned int bufferiD;
    glGenBuffers(1, &bufferiD);
    glBindBuffer(GL_ARRAY_BUFFER, bufferiD);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //Shader
    
    ShaderProgramSource program = Shader("res/shaders/Shader.shader");

    unsigned int shader = CreateShader(program.VertexSource, program.FragmentSource);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}