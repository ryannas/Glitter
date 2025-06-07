// Local Headers
#include "glitter.hpp"

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include "shader.hpp"

GLITTER_SIMPLE_MAIN_BEGIN() {
    // define shaders
    Glitter::Shader Shader;
    Shader.attach("LearnOpenGL/2-Shaders/VertexShader.vert");
    Shader.attach("LearnOpenGL/2-Shaders/FragmentShader.frag");
    Shader.link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    constexpr float vertices[] = {
         0.f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // bottom left
    };

    // init buffers
    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO); // vertex array object, stores vertex attributes
    glGenBuffers(1, &VBO); // vertex buffer object, stores vertex data

    // bind vertex array object
    glBindVertexArray(VAO); // bind VAO to draw

    // bind buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind VBO to
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy vertex data to VBO

    // setup VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0); // vertex positions
    glEnableVertexAttribArray(0); // enable vertex attribute 0 (position)

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float))); // vertex colors
    glEnableVertexAttribArray(1); // enable vertex attribute 1 (color)

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Rendering Loop
    GLITTER_SIMPLE_UPDATE_BEGIN() {
        Shader.activate(); // use shader

        // update uniform value
        float timeValue = glfwGetTime(); // get current time
        float offset = sin(timeValue) * 0.1; // calculate green value based on time
        Shader.bind<float>("offset", offset);

        glBindVertexArray(VAO); // bind VAO to draw
        glDrawArrays(GL_TRIANGLES, 0, 3); // draw triangles using vertex data
    }
    GLITTER_SIMPLE_UPDATE_END()

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
GLITTER_SIMPLE_MAIN_END()
