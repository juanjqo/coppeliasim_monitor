#include "imgui_coppeliasim_interface.h"


ImguiCoppeliaSimInterface::ImguiCoppeliaSimInterface(const juangui_wrapper_parameters &parameters)
:JuanGui_Wrapper(parameters)
{

}

void ImguiCoppeliaSimInterface::my_custom_gui()
{
    ImGui::Begin("Hello, Juanchito 2!");

    ImGui::End();
}
