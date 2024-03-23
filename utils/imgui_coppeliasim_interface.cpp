#include "imgui_coppeliasim_interface.h"
#include <my_custom_definitions.h>

ImguiCoppeliaSimInterface::ImguiCoppeliaSimInterface(const juangui_wrapper_parameters &parameters)
:JuanGui_Wrapper(parameters)
{
    std::string config_yaml = get_cfg_folder_path() + std::string("config_test.yaml");
    //std::string config_yaml = "/home/juanjqo/git/coppeliasim_commander/cfg/config.yaml";
    if (!std::filesystem::exists(config_yaml))
    {
        std::cerr<<"Wrong yaml path file. "<<std::endl;
    }

    my_yaml_reader_ptr_ = std::make_shared<MyYamlReader>(config_yaml);
    ip_ = my_yaml_reader_ptr_->get_ip();
    port_ = my_yaml_reader_ptr_->get_port();
    jointnames_ = my_yaml_reader_ptr_->get_jointnames();
    std::tie(q_min_, q_max_) = my_yaml_reader_ptr_->get_joint_limits();
}



void ImguiCoppeliaSimInterface::my_custom_gui()
{
    ImGui::Begin("CoppeliaSim Parameters");

    ImGui::Text(ip_.c_str());

    ImGui::End();

    ImGui::Begin("In construction");
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

