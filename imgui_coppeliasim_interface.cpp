#include "imgui_coppeliasim_interface.h"


ImguiCoppeliaSimInterface::ImguiCoppeliaSimInterface(const juangui_wrapper_parameters &parameters)
:JuanGui_Wrapper(parameters)
{

}

void ImguiCoppeliaSimInterface::my_custom_gui()
{
    ImGui::Begin("Hello, Juanchito 2!");

    ImGui::End();

    ImGui::Begin("Camila la bobita");
    ImGui::End();

    {
        int my_image_width = 0;
        int my_image_height = 0;
        GLuint my_image_texture = 0;
        bool ret = LoadTextureFromFile(capi_path_.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);

        ImGui::Begin("OpenGL Texture Text");
        //ImGui::Text("pointer = %x", my_image_texture);
        //ImGui::Text("size = %d x %d", my_image_width, my_image_height);
        ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
        ImGui::End();
    }
}

void ImguiCoppeliaSimInterface::set_capi_path(const std::string &my_path)
{
    capi_path_ = my_path;
}
