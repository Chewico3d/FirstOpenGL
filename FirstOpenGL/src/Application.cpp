#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "abs/VertexBuffer.h"
#include "abs/IndexBuffer.h"
#include "abs/VerexBufferLayout.h"
#include "abs/VertexArray.h"
#include "abs/Shader.h"
#include "Renderer.h"
#include "../oth/Texture.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "gl version " << glGetString(GL_VERSION);
    
    //Shader and stuff
    float positions[] = {
         0.5f,-0.5f, 1.0f, 0.0f ,
         0.5,  0.5 , 1.0f, 1.0f ,
        -0.5f,-0.5f, 0.0f, 0.0f ,
        -0.5f, 0.5f, 0.0f, 1.0f
    };

    unsigned int indexs[6] = {
        0, 2, 1,
        3, 2, 1

    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //Vertex buffer

    VertexArray va;
    VertexBuffer vb( positions, 4 * 4 * sizeof(float));

    VerexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    //Index buffer
    IndexBuffer ib(indexs, 6);


    //proj
    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1),glm::vec3(-1.0f, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(-0.0f, 0, 0));

    glm::mat4 mvp = model * proj * view;

    Shader shader("res/shaders/Shader.shader");
    shader.Bind();

    shader.SetUniform4f("u_Color", 0.2f, 0.2f, 1.0f,1.0f);
    Renderer rnd;

    Texture tex("img/saul.png");
    tex.Bind(0);

    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniformMat4f("u_MVP", mvp);

    
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        rnd.Clear();

        ImGui_ImplGlfwGL3_NewFrame();
        rnd.Draw(va, ib, shader);

        ImGui::Text("Hello, world!");                           // Edit 1 float using a slider from 0.0f to 1.0f    
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */   
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}