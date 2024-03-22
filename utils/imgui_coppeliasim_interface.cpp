#include "imgui_coppeliasim_interface.h"
#include <my_custom_definitions.h>

ImguiCoppeliaSimInterface::ImguiCoppeliaSimInterface(const juangui_wrapper_parameters &parameters)
:JuanGui_Wrapper(parameters)
{
    std::string config_yaml = get_cfg_folder_path() + std::string("config.yaml");
    //std::string config_yaml = "/home/juanjqo/git/coppeliasim_commander/cfg/config.yaml";
    bool status_config_path = std::filesystem::exists(config_yaml);

    my_yaml_reader_ptr_ = std::make_shared<MyYamlReader>(config_yaml);
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
        std::string capi_path = get_assets_folder_path() + std::string("images/capi.jpg");
        bool ret = LoadTextureFromFile(capi_path.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);

        ImGui::Begin("OpenGL Texture Text");
        //ImGui::Text("pointer = %x", my_image_texture);
        //ImGui::Text("size = %d x %d", my_image_width, my_image_height);
        ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
        ImGui::End();
    }
}

