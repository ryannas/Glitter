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
    Shader.attach("LearnOpenGL/1-HelloTriangles/VertexShader.vert");
    Shader.attach("LearnOpenGL/1-HelloTriangles/FragmentShader.frag");

    Shader.activate();
    Shader.link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    constexpr float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
   };
    constexpr unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    // init buffers
    GLuint VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO); // vertex array object, stores vertex attributes
    glGenBuffers(1, &VBO); // vertex buffer object, stores vertex data
    glGenBuffers(1, &EBO); // element buffer object, stores indices for indexed drawing

    // bind vertex array object
    glBindVertexArray(VAO); // bind VAO to draw

    // bind buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind VBO to
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy vertex data to VBO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // setup VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // vertex positions
    glEnableVertexAttribArray(0); // enable vertex attribute 0 (position)

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Rendering Loop
    GLITTER_SIMPLE_UPDATE_BEGIN() {
        Shader.activate(); // use shader
        glBindVertexArray(VAO); // bind VAO to draw
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw triangles using indices
    }
    GLITTER_SIMPLE_UPDATE_END()

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
GLITTER_SIMPLE_MAIN_END()
