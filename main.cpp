#include <iostream>
#include "imgui_coppeliasim_interface.h"
#include <vector>

using namespace std;

int main()
{
    juangui_wrapper_parameters parameters;
    parameters.width = 1920;
    parameters.height = 1080;
    parameters.title = "CoppeliaSim Commander by Juancho";
    parameters.screen_mode = "LIGHT_MODE";
    parameters.font_path = FONT_RESOURCE_DIR;
    parameters.font_size = 25;

    ImguiCoppeliaSimInterface imgui_coppeliasim_interface(parameters);
    imgui_coppeliasim_interface.set_capi_path(CAPI_RESOURCE_DIR);

    imgui_coppeliasim_interface.loop();

    imgui_coppeliasim_interface.cleanup();




    return 0;
}
