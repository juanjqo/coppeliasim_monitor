cmake_minimum_required(VERSION 3.5)

project(coppeliasim_commander LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/imgui_template)
include(${IMGUI_TEMPLATE_DIR}/dependencies.cmake)

include_directories(${IMGUI_TEMPLATE_DIR}/commons/)


set(CUSTOM_JUANGUI_WRAPPER imgui_coppeliasim_interface)
add_library (${CUSTOM_JUANGUI_WRAPPER}
             ${CUSTOM_JUANGUI_WRAPPER}.h
             ${CUSTOM_JUANGUI_WRAPPER}.cpp)
target_link_libraries(${CUSTOM_JUANGUI_WRAPPER} juangui_wrapper)


add_executable(coppeliasim_commander main.cpp)

target_link_libraries(coppeliasim_commander
                      dqrobotics
                      dqrobotics-interface-vrep
                      imgui
                      implot
                      imgui-knobs
                      glfw
                      juancho-tools
                      OpenGL::GL
                      ${CUSTOM_JUANGUI_WRAPPER})

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC FONT_RESOURCE_DIR="${IMGUI_TEMPLATE_DIR}/fonts/Ubuntu/Ubuntu-Regular.ttf")
