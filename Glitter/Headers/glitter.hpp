// Preprocessor Directives
#ifndef GLITTER
#define GLITTER
#pragma once

// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Useful Macros
#define GLITTER_SIMPLE_MAIN_BEGIN() \
    int main(int argc, char * argv[]) { \
        glfwInit(); \
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); \
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); \
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); \
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); \
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); \
        auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr); \
        if (mWindow == nullptr) { \
            fprintf(stderr, "Failed to Create OpenGL Context"); \
            return EXIT_FAILURE; \
        } \
        glfwMakeContextCurrent(mWindow); \
        gladLoadGL();

#define GLITTER_SIMPLE_MAIN_END() \
        glfwTerminate(); \
        return EXIT_SUCCESS; \
    }

#define GLITTER_SIMPLE_UPDATE_BEGIN() \
    while (glfwWindowShouldClose(mWindow) == false) { \
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); \
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

#define GLITTER_SIMPLE_UPDATE_END() \
        glfwSwapBuffers(mWindow); \
        glfwPollEvents(); \
    }

// Define Some Constants
const int mWidth = 1280;
const int mHeight = 800;

#endif //~ Glitter Header
