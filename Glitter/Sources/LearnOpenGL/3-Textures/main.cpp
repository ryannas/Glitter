// Local Headers
#include "glitter.hpp"

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION // define before including stb_image.h
#include <stb_image.h>

#include "shader.hpp"

GLITTER_SIMPLE_MAIN_BEGIN() {
    // define shaders
    Glitter::Shader Shader;
    Shader.attach("LearnOpenGL/3-Textures/VertexShader.vert");
    Shader.attach("LearnOpenGL/3-Textures/FragmentShader.frag");

    Shader.activate();
    Shader.link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    constexpr float vertices[] = {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0); // vertex positions
    glEnableVertexAttribArray(0); // enable vertex attribute 0 (position)

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); // vertex positions
    glEnableVertexAttribArray(1); // enable vertex attribute 0 (position)

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float))); // vertex positions
    glEnableVertexAttribArray(2); // enable vertex attribute 0 (position)

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // import texture
    GLuint textures[2];
    glGenTextures(2, textures); // generate texture ID
    const std::string texture_paths[] = {
        PROJECT_SOURCE_DIR "/Glitter/Resources/container.jpg",
        PROJECT_SOURCE_DIR "/Glitter/Resources/awesomeface.png"
    };

    stbi_set_flip_vertically_on_load(true);
    for (int i = 0; i < 2; ++i) {
        glBindTexture(GL_TEXTURE_2D, textures[i]); // bind texture to target

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // set texture wrapping to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // set texture filtering to GL_LINEAR for minification
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // set texture filtering to GL_LINEAR for magnification

        // copy texture data to GPU
        int width, height, nrChannels;
        unsigned char *data = stbi_load(texture_paths[i].c_str(), &width, &height, &nrChannels, 0);
        if (!data) {
            fprintf(stderr, "Failed to load texture: %s\n", texture_paths[i].c_str());
            return EXIT_FAILURE;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, i == 0 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data); // free image data after copying to GPU
    }

    // Rendering Loop
    GLITTER_SIMPLE_UPDATE_BEGIN() {

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);

        Shader.activate(); // use shader
        Shader.bind("texture0", 0); // bind texture unit 0 to uniform "texture1"
        Shader.bind("texture1", 1); // bind texture unit 0 to uniform "texture1"

        glBindVertexArray(VAO); // bind VAO to draw
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw triangles using indices
    }
    GLITTER_SIMPLE_UPDATE_END()

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
GLITTER_SIMPLE_MAIN_END()
