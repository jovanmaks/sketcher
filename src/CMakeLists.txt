cmake_minimum_required(VERSION 3.17.4)

project(Sketcher VERSION  0.1)

include( GNUInstallDirs )

set( GLFWM_VERSION_MAJOR "3" )
set( GLFWM_VERSION_MINOR "2" )
#set(CMAKE_BUILD_TYPE Debug)
#This also disables optimization.
#For profiling instead of debugging, you generally want both optimization and symbols (aka -g O2).

find_package( OpenGL REQUIRED )
find_package( glfw3 REQUIRED )

set( SRCS

../src/Application.cpp

../src/Renderer.cpp
../src/VertexBuffer.cpp
../src/IndexBuffer.cpp
../src/VertexArray.cpp
../src/Shader.cpp
../src/Texture.cpp
../src/Grid.cpp



../src/vendor/stb_image/stb_image.cpp

../src/vendor/imgui/imgui_demo.cpp
../src/vendor/imgui/imgui_draw.cpp
../src/vendor/imgui/imgui_impl_glfw.cpp
../src/vendor/imgui/imgui_impl_opengl3.cpp
../src/vendor/imgui/imgui_widgets.cpp
../src/vendor/imgui/imgui.cpp

)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})
    
   

target_link_libraries( Sketcher ${../lib} GL )
target_link_libraries( Sketcher ${../lib} GLEW )
target_link_libraries( Sketcher ${../lib} glfw )