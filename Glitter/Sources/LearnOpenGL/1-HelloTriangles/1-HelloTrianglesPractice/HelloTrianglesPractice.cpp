// Local Headers
#include "glitter.hpp"

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include "shader.hpp"

GLITTER_SIMPLE_MAIN_BEGIN() {
    // define shaders
    Glitter::Shader Shader1, Shader2;

    Shader1.attach("LearnOpenGL/1-HelloTriangles/VertexShader.vert");
    Shader1.attach("LearnOpenGL/1-HelloTriangles/FragmentShader1.frag");
    Shader1.link();

    Shader2.attach("LearnOpenGL/1-HelloTriangles/VertexShader.vert");
    Shader2.attach("LearnOpenGL/1-HelloTriangles/FragmentShader2.frag");
    Shader2.link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    constexpr float vertices_1[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
    };

    constexpr float vertices_2[] = {
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f,  // top left
        0.5f,  0.5f, 0.0f,  // top right
    };

    // init buffers
    GLuint VBOs[2], VAOs[2];

    glGenVertexArrays(2, VAOs); // vertex array object, stores vertex attributes
    glGenBuffers(2, VBOs); // vertex buffer object, stores vertex data

    // bind first VAO, VBO
    {
        // bind vertex array object
        glBindVertexArray(VAOs[0]); // bind VAO to draw

        // bind buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // bind VBO to
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW); // copy vertex data to VBO

        // setup VAO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // vertex positions
        glEnableVertexAttribArray(0); // enable vertex attribute 0 (position)

        // unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    // bind second VAO, VBO
    {
        // bind vertex array object
        glBindVertexArray(VAOs[1]); // bind VAO to draw

        // bind buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // bind VBO to
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW); // copy vertex data to VBO

        // setup VAO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // vertex positions
        glEnableVertexAttribArray(0); // enable vertex attribute 0 (position)

        // unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    // Rendering Loop
    GLITTER_SIMPLE_UPDATE_BEGIN() {
        // draw first triangle
        {
            Shader1.activate(); // use shader
            glBindVertexArray(VAOs[0]); // bind VAO to draw
            glDrawArrays(GL_TRIANGLES, 0, 3); // draw triangles using vertex data
        }

        // draw second triangle
        {
            Shader2.activate(); // use shader
            glBindVertexArray(VAOs[1]); // bind VAO to draw
            glDrawArrays(GL_TRIANGLES, 0, 3); // draw triangles using vertex data
        }
    }
    GLITTER_SIMPLE_UPDATE_END()

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
}
GLITTER_SIMPLE_MAIN_END()
