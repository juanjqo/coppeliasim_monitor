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

    vi_ = std::make_shared<DQ_VrepInterface>();
}

void ImguiCoppeliaSimInterface::_check_parameter_sizes()
{
    if (q_min_.size() != q_max_.size())
    {

    }
}

void ImguiCoppeliaSimInterface::_stop_app()
{
    deinitialize_coppeliasim();
    disconnect_coppeliasim();
    this->JuanGui_Wrapper::stop_and_quit(true);
}

void ImguiCoppeliaSimInterface::my_custom_gui()
{
    show_main_menu_bar();
    show_coppeliasim_app_parameters();


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

void ImguiCoppeliaSimInterface::create_sas_driver_buttons()
{
    static bool button_connect_disable = false;
    static bool button_initialize_disable = true;
    static bool button_deinitialize_disable = true;
    static bool button_disconnect_disable = true;



    ImGui::BeginDisabled(button_connect_disable);
    if (ImGui::Button("Connect"))
    {
        button_connect_disable   = true;
        button_initialize_disable = false;
        status_msg_ = "connecting...";
        connect_coppeliasim();
    }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(button_initialize_disable);
    if (ImGui::Button("Initialize"))
    {
        button_initialize_disable = true;
        button_deinitialize_disable = false;
        status_msg_ = "initializing...";
        initialize_coppeliasim();
    }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(button_deinitialize_disable);
    if (ImGui::Button("Deinitialize"))
    {
        button_deinitialize_disable = true;
        button_disconnect_disable = false;
        status_msg_ = "deinitializing...";
        deinitialize_coppeliasim();
    }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(button_disconnect_disable);
    if (ImGui::Button("Disconnect"))
    {
        status_msg_ = "disconnecting...";
        disconnect_coppeliasim();
    }
    ImGui::EndDisabled();
    ImGui::SeparatorText("");
    ImGui::Text("%s", std::string("Status:   " + status_msg_).c_str());
    ImGui::SeparatorText("");
}

void ImguiCoppeliaSimInterface::connect_coppeliasim()
{
    try
    {
        if (!vi_->connect(ip_, port_,100,10))
            throw std::runtime_error("Unable to connect to CoppeliaSim.");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        status_msg_ = "connected!";
    }
    catch (std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
        vi_->stop_simulation();
        vi_->disconnect();
    }
}

void ImguiCoppeliaSimInterface::initialize_coppeliasim()
{
    vi_->start_simulation();
    status_msg_ = "Initialized!";
    _start_echo_robot_state_mode_thread();
}

void ImguiCoppeliaSimInterface::deinitialize_coppeliasim()
{
    vi_->stop_simulation();
    status_msg_ = "Deinitialized!";
    _finish_echo_robot_state();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (echo_robot_state_mode_thread_.joinable())
    {
        echo_robot_state_mode_thread_.join();
    }

}

void ImguiCoppeliaSimInterface::disconnect_coppeliasim()
{
   vi_->disconnect();
    status_msg_ = "Disconnected!";
}

void ImguiCoppeliaSimInterface::_start_echo_robot_state_mode()
{
    while(!finish_echo_robot_state_)
    {
        q_ = vi_->get_joint_positions(jointnames_);
        q_dot_ = vi_->get_joint_velocities(jointnames_);
    }
    status_msg_ = "Finished echo robot state.";
}



void  ImguiCoppeliaSimInterface::_start_echo_robot_state_mode_thread()
{
    finish_echo_robot_state_ = false;
    status_msg_ = "Checking echo robot state thread";
    if (echo_robot_state_mode_thread_.joinable())
    {
        echo_robot_state_mode_thread_.join();
    }
    status_msg_ ="Starting echo robot state thread";
    echo_robot_state_mode_thread_ = std::thread(&ImguiCoppeliaSimInterface::_start_echo_robot_state_mode, this);
}


void  ImguiCoppeliaSimInterface::_finish_echo_robot_state()
{
    status_msg_ = "Finishing echo robot state.";
    finish_echo_robot_state_ = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}





void ImguiCoppeliaSimInterface::show_main_menu_bar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            //ShowExampleMenuFile();
            if (ImGui::MenuItem("Load configuration file")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Quit"))
                show_exit_window_ = true;

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("User Manual")) {}
            if (ImGui::MenuItem("About CoppeliaSim Monitor")) {}
            if (ImGui::MenuItem("Credits")) {
                set_message_window_parameters(true, "Juan Jose Quiroz Omana");
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
        show_message_window();
        show_exit_window();
    }
}

void ImguiCoppeliaSimInterface::show_coppeliasim_app_parameters()
{
    ImGui::Begin("CoppeliaSim");
    ImGui::SeparatorText("");
    //ImVec2 size = ImVec2(32.0f, 32.0f);
    //ImVec4 my_color = ImVec4(0.13f, 0.26f, 0.40f, 1.0f);

    ImGui::Text("%s", std::string("ip:   " + ip_).c_str());
    ImGui::Spacing();
    ImGui::Text("%s", std::string("port: " + std::to_string(port_)).c_str());
    ImGui::SeparatorText("");
    create_sas_driver_buttons();
    ImGui::SeparatorText("");

    static bool disabled = false;
    ImGui::Checkbox("Disable", &disabled);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

}


void ImguiCoppeliaSimInterface::set_message_window_parameters(const bool &flag, const std::string &msg)
{
    show_message_window_ = flag;
    message_window_ = msg;
}

void ImguiCoppeliaSimInterface::show_message_window()
{
    // 3. Show another simple window.

    if (show_message_window_)
    {
        ImGui::Begin("Message", &show_message_window_);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("%s", message_window_.c_str());
        if (ImGui::Button("Ok"))
            show_message_window_ = false;
        ImGui::End();
    }
}

void ImguiCoppeliaSimInterface::show_exit_window()
{
    if (show_exit_window_ )
    {
        ImGui::Begin("Message", &show_exit_window_ );   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("%s", std::string("Do you want to exit?").c_str());
        if (ImGui::Button("Yes"))
            _stop_app();
        ImGui::SameLine();
        if (ImGui::Button("No"))
            show_exit_window_  = false;
        ImGui::End();
    }
}



/*
if (ImGui::BeginTable("split", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
{
    for (int i = 0; i < 100; i++)
    {
        char buf[32];
        sprintf(buf, "%03d", i);
        ImGui::TableNextColumn();
        ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
    }
    ImGui::EndTable();
*/
