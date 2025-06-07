cmake_minimum_required(VERSION 3.0)
project(Glitter)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Glitter/Vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Glitter/Vendor/assimp)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(Glitter/Vendor/bullet)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(Glitter/Headers/
                    Glitter/Headers/Utils/
                    Glitter/Vendor/assimp/include/
                    Glitter/Vendor/bullet/src/
                    Glitter/Vendor/glad/include/
                    Glitter/Vendor/glfw/include/
                    Glitter/Vendor/glm/
                    Glitter/Vendor/stb/)

file(GLOB VENDORS_SOURCES Glitter/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS Glitter/Headers/*.hpp)
file(GLOB PROJECT_SHADERS Glitter/Shaders/*.comp
                          Glitter/Shaders/*.frag
                          Glitter/Shaders/*.geom
                          Glitter/Shaders/*.vert)

file(GLOB PROJECT_UTILS Glitter/Headers/Utils/*.hpp
                        Glitter/Sources/Utils/*.cpp)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Vendors" FILES ${VENDORS_SOURCES})
source_group("Utils" FILES ${PROJECT_UTILS})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

file (GLOB_RECURSE PROJECT_SOURCE_DIRS LIST_DIRECTORIES true Glitter/Sources/LearnOpenGL/*)
foreach (PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIRS})
    if (IS_DIRECTORY ${PROJECT_SOURCE_DIR})
        file(GLOB PROJECT_SOURCES LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/*)
        if (NOT PROJECT_SOURCES)
            continue()
        endif ()
        get_filename_component(FOLDER_NAME ${PROJECT_SOURCE_DIR} NAME)
        source_group("LearnOpenGL-${FOLDER_NAME}" FILES ${PROJECT_SOURCES})

        add_executable(${FOLDER_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                       ${PROJECT_SHADERS} ${PROJECT_CONFIGS} ${PROJECT_UTILS}
                       ${VENDORS_SOURCES})

        target_link_libraries(${FOLDER_NAME} assimp glfw
                              ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                              BulletDynamics BulletCollision LinearMath)

        set_target_properties(${FOLDER_NAME} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

        add_custom_command(
                TARGET ${FOLDER_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Glitter/Shaders $<TARGET_FILE_DIR:${FOLDER_NAME}>
                DEPENDS ${PROJECT_SHADERS})
    endif()
endforeach ()
