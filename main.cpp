
#include "imgui_coppeliasim_interface.h"


using namespace std;

int main()
{
    juangui_wrapper_parameters parameters;
    parameters.width = 1920;
    parameters.height = 1080;
    parameters.title = "CoppeliaSim Commander by Juan Jose Quiroz Omana";
    parameters.screen_mode = "LIGHT_MODE";
    parameters.font_path = "default";
    parameters.font_size = 14;

    ImguiCoppeliaSimInterface imgui_coppeliasim_interface(parameters);


    imgui_coppeliasim_interface.loop();

    return 0;
}
