cmake_minimum_required(VERSION 3.5)

project(coppeliasim_monitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add custom (non compiling) targets so launch scripts and python files show up in QT Creator's project view.
file(GLOB_RECURSE EXTRA_FILES */*)
#add_custom_target(${PROJECT_NAME}_OTHER_FILES ALL WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} SOURCES ${EXTRA_FILES})
add_custom_target(cfg ALL WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} SOURCES ${EXTRA_FILES})


set(IMGUI_TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/imgui_template)
include(${IMGUI_TEMPLATE_DIR}/dependencies.cmake)

set (CAPYBARA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/capybara_toolkit/)
include(${CAPYBARA_DIR}/capybara_library.cmake)


set(COPPELIASIM_DRIVER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/coppeliasim_driver/)
include(${COPPELIASIM_DRIVER_DIR}/coppeliasim_driver_library.cmake)

include_directories(${IMGUI_TEMPLATE_DIR}/commons/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils/)

set(CUSTOM_JUANGUI_WRAPPER imgui_coppeliasim_interface)
add_library (${CUSTOM_JUANGUI_WRAPPER}
             ${CMAKE_CURRENT_SOURCE_DIR}/utils/${CUSTOM_JUANGUI_WRAPPER}.h
             ${CMAKE_CURRENT_SOURCE_DIR}/utils/${CUSTOM_JUANGUI_WRAPPER}.cpp
             )
target_link_libraries(${CUSTOM_JUANGUI_WRAPPER} juangui_wrapper)



include(FetchContent)

if(UNIX AND NOT APPLE)

    FetchContent_Declare(
      yaml-cpp
      GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
      GIT_TAG master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
    )
    FetchContent_GetProperties(yaml-cpp)

    if(NOT yaml-cpp_POPULATED)
      message(STATUS "Fetching yaml-cpp...")
      FetchContent_Populate(yaml-cpp)
      add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
    endif()
endif()

if(APPLE)
    FIND_PACKAGE(yaml-cpp REQUIRED)
    INCLUDE_DIRECTORIES(${YAMLCPP_INCLUDE_DIR})
endif()



add_library(my_yaml_reader
           ${CMAKE_CURRENT_SOURCE_DIR}/utils/my_yaml_reader.h
           ${CMAKE_CURRENT_SOURCE_DIR}/utils/my_yaml_reader.cpp
            )
target_link_libraries(my_yaml_reader yaml-cpp::yaml-cpp juancho-tools)





add_executable(coppeliasim_monitor main.cpp)

if(UNIX AND NOT APPLE)
target_link_libraries(${CMAKE_PROJECT_NAME}
                      dqrobotics
                      coppeliasim_driver
                      imgui
                      implot
                      imgui-knobs
                      harry_plotter
                      glfw
                      juancho-tools
                      OpenGL::GL
                      ${CUSTOM_JUANGUI_WRAPPER}
                      my_yaml_reader
                      yaml-cpp::yaml-cpp
                      capybara
                      )
endif()

if(APPLE)
  target_link_libraries(${CMAKE_PROJECT_NAME}
                          dqrobotics
                          coppeliasim_driver
                          imgui
                          implot
                          imgui-knobs
                          harry_plotter
                          ${CUSTOM_JUANGUI_WRAPPER}
                          juancho-tools
                          glfw
                          my_yaml_reader
                          capybara
                          yaml-cpp::yaml-cpp
                          "-framework Cocoa"
                          "-framework OpenGL"
                          "-framework IOKit")                       
endif()

#target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
#    FONT_RESOURCE_DIR="${IMGUI_TEMPLATE_DIR}/fonts/Ubuntu/Ubuntu-Regular.ttf")



set(ASSETS ${CMAKE_CURRENT_SOURCE_DIR}/assets/)
set(CFG ${CMAKE_CURRENT_SOURCE_DIR}/cfg/)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/utils/my_custom_definitions.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/utils/my_custom_definitions.h)
