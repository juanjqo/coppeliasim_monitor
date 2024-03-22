#include <iostream>
#include "imgui_coppeliasim_interface.h"

using namespace std;

int main()
{
    juangui_wrapper_parameters parameters;
    parameters.width = 1280;
    parameters.height = 720;
    parameters.title = "Juanchotronics";
    parameters.screen_mode = "LIGHT_MODE";
    parameters.font_path = FONT_RESOURCE_DIR;
    parameters.font_size = 25;

    ImguiCoppeliaSimInterface imgui_coppeliasim_interface(parameters);


    imgui_coppeliasim_interface.loop();

    imgui_coppeliasim_interface.cleanup();

    return 0;
}
