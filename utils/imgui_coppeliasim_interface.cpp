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
    ImGui::Begin("CoppeliaSim");
    ImGui::SeparatorText("");
    //ImVec2 size = ImVec2(32.0f, 32.0f);
    ImVec4 my_color = ImVec4(0.13f, 0.26f, 0.40f, 1.0f);

    ImGui::Text(std::string("ip:   " + ip_).c_str());
     ImGui::Spacing();
    ImGui::Text(std::string("port: " + std::to_string(port_)).c_str());

    ImGui::SeparatorText("");
    static bool connect_status = false;


    static int always_on = 1;
    ImGui::RadioButton("C", &always_on, 0);
    ImGui::SameLine();
    ImGui::Button("Connect");
    ImGui::Button("Initialize");
    ImGui::Button("Deinitialize");
    ImGui::Button("Disconnect");
    //ImGui::ColorButton("Hola", ImVec4(0.13f, 0.26f, 0.40f, 1.0f), ImGuiColorEditFlags_None, ImVec2(40, 40));

    ImGui::SeparatorText("");

    static bool disabled = false;
    ImGui::Checkbox("Disable", &disabled);
    if (disabled)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }
    if (disabled)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }




    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Begin("In construction");
    ImGui::End();
  /*
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
*/
}

