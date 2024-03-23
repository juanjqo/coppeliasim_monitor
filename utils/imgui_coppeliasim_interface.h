#pragma once
#include <juangui_wrapper.h>
#include <juancho_tools.h>
#include <cmath>
#include <my_yaml_reader.h>
#include <memory>
#include <filesystem>
#include <dqrobotics/interfaces/vrep/DQ_VrepInterface.h>
#include <thread>
#include <atomic>


class ImguiCoppeliaSimInterface: public JuanGui_Wrapper
{
protected:
    std::shared_ptr<MyYamlReader> my_yaml_reader_ptr_;
    std::string ip_;
    std::vector<std::string> jointnames_;
    Eigen::VectorXd q_min_;
    Eigen::VectorXd q_max_;
    Eigen::VectorXd q_;
    Eigen::VectorXd q_dot_;

    int port_;
    std::string status_msg_;
    std::shared_ptr<DQ_VrepInterface> vi_;

    bool show_message_window_ = false;
    std::string message_window_;
    void set_message_window_parameters(const bool& flag, const std::string& msg);

    bool show_exit_window_ = false;


    void _start_echo_robot_state_mode();
    std::thread echo_robot_state_mode_thread_;
    void _start_echo_robot_state_mode_thread();
    std::atomic<bool> finish_echo_robot_state_;
    void _finish_echo_robot_state();

    void _check_parameter_sizes();

    void _stop_app();

public:

    ImguiCoppeliaSimInterface(const juangui_wrapper_parameters& parameters);



    void my_custom_gui() override;
    void show_main_menu_bar();
    void show_coppeliasim_app_parameters();

    void show_message_window();
    void show_exit_window();

    void create_sas_driver_buttons();

    void connect_coppeliasim();
    void initialize_coppeliasim();
    void deinitialize_coppeliasim();
    void disconnect_coppeliasim();





};
