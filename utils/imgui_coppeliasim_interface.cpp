#include "imgui_coppeliasim_interface.h"
#include <my_custom_definitions.h>


ImguiCoppeliaSimInterface::ImguiCoppeliaSimInterface(const juangui_wrapper_parameters &parameters)
    :JuanGui_Wrapper(parameters), data_available_(false)
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
    std::tie(q_dot_min_, q_dot_max_) = my_yaml_reader_ptr_->get_joint_velocity_limits();
    _check_parameter_sizes();
    coppeliasim_driver_ = std::make_unique<CoppeliaSimDriver>();
    coppeliasim_driver_->set_parameters(ip_, port_, jointnames_, {q_min_, q_max_}, {q_dot_min_, q_dot_max_});
}


void ImguiCoppeliaSimInterface::_check_parameter_sizes()
{
    if (static_cast<std::size_t>(q_min_.size()) != static_cast<std::size_t>(q_max_.size())
        or static_cast<std::size_t>(q_min_.size()) != jointnames_.size())
    {
        throw std::runtime_error("Incorrect size of q_min and q_max or jointnames. ");
    }
    if (static_cast<std::size_t>(q_dot_min_.size()) != static_cast<std::size_t>(q_dot_max_.size())
        or static_cast<std::size_t>(q_dot_min_.size()) != jointnames_.size())
    {
        throw std::runtime_error("Incorrect size of q_dot_min and q_dot_max or jointnames. ");
    }

    n_joints_ = jointnames_.size();
    q_ = Eigen::VectorXd::Zero(n_joints_);
    q_dot_= Eigen::VectorXd::Zero(n_joints_);
}

void ImguiCoppeliaSimInterface::_stop_app()
{
    deinitialize_coppeliasim();
    disconnect_coppeliasim();
    this->JuanGui_Wrapper::stop_and_quit(true);
}


void ImguiCoppeliaSimInterface::my_custom_gui()
{
    _update_data_from_driver();
    show_main_menu_bar();
    show_coppeliasim_app_parameters();
    show_table_parameters();
    //show_console_window();

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
        status_msg_ = "initialized!";
    }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(button_deinitialize_disable);
    if (ImGui::Button("Deinitialize"))
    {
        button_deinitialize_disable = true;
        button_disconnect_disable = false;
        status_msg_ = "deinitializing...";
        deinitialize_coppeliasim();
        status_msg_ = "deinitialized!";
    }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(button_disconnect_disable);
    if (ImGui::Button("Disconnect"))
    {
        status_msg_ = "disconnecting...";
        disconnect_coppeliasim();
        status_msg_ = "disconnected!";
    }
    ImGui::EndDisabled();
    ImGui::SeparatorText("");
    ImGui::Text("%s", std::string("Status:   " + status_msg_).c_str());
    ImGui::SeparatorText("");
}

void ImguiCoppeliaSimInterface::connect_coppeliasim()
{
    coppeliasim_driver_->connect();
}

void ImguiCoppeliaSimInterface::initialize_coppeliasim()
{
    coppeliasim_driver_->initialize();
    data_available_ = true;
}

void ImguiCoppeliaSimInterface::deinitialize_coppeliasim()
{
    coppeliasim_driver_->deinitialize();
    data_available_ = false;
}

void ImguiCoppeliaSimInterface::disconnect_coppeliasim()
{
    coppeliasim_driver_->disconnect();
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
    ImGui::Text("Simulation time (s): %.3f", simulation_time_);
    ImGui::End();

}


/**
 * @brief ImguiCoppeliaSimInterface::_update_data_from_driver
 */
void ImguiCoppeliaSimInterface::_update_data_from_driver()
{
    if (data_available_)
    {
        q_ = coppeliasim_driver_->get_configuration_space_positions();
        q_dot_ = coppeliasim_driver_->get_configuration_space_velocities();
        simulation_time_ = coppeliasim_driver_->get_simulation_time();
    }
}

/**
 * @brief ImguiCoppeliaSimInterface::set_message_window_parameters
 * @param flag
 * @param msg
 */
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




void ImguiCoppeliaSimInterface::show_table_parameters()
{

    auto q_table = _create_vector_for_table_data(q_min_, q_, q_max_);
    std::vector<std::string> q_labels = {"q_min", "q", "q_max"};

    auto q_dot_table = _create_vector_for_table_data(q_dot_min_, q_dot_, q_dot_max_);
    std::vector<std::string> q_dot_labels = {"q_dot_min", "q_dot", "q_dot_max"};


    ImGui::Begin("Joint Positions");
    _create_table_data(q_labels, q_table);
    ImGui::End();

    ImGui::Begin("Joint Velocities");
    _create_table_data(q_dot_labels, q_dot_table);
    ImGui::End();

}

void ImguiCoppeliaSimInterface::show_console_window()
{
    ImGui::Begin("Console");

    ImGui::End();
}

void ImguiCoppeliaSimInterface::_create_table_data(const std::vector<std::string> &labels,
                                                   const std::vector<VectorXd> &q_table)
{
    if (labels.size() != q_table.size())
    {
        throw std::runtime_error("Wrong sizes in labels and q_table.");
    }
    if (ImGui::BeginTable("split", labels.size(), ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
    {
        for (auto& data : labels)
        {
            ImGui::TableNextColumn();
            ImGui::Text("%s", data.c_str());
        }

        for (int i = 0; i < q_table.at(0).size(); i++)
        {
            for (std::size_t j = 0; j < q_table.size(); j++)
            {
                ImGui::TableNextColumn();
                ImGui::Button(std::to_string(q_table.at(j)[i]).c_str(), ImVec2(-FLT_MIN, 0.0f));
            }
        }
        ImGui::EndTable();
    }
}

std::vector<VectorXd> ImguiCoppeliaSimInterface::_create_vector_for_table_data(const VectorXd &min, const VectorXd &value, const VectorXd &max)
{
    std::vector<Eigen::VectorXd> q_table(3, VectorXd::Zero(min.size()));
    q_table.at(0) = min;
    q_table.at(1) = value;
    q_table.at(2) = max;
    return q_table;
}

