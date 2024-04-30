#pragma once
#include <juangui_wrapper.h>
#include <juancho_tools.h>
#include <cmath>
#include <my_yaml_reader.h>
#include <memory>
#include <filesystem>
#include <coppeliasim_driver.hpp>
#include <thread>
#include <atomic>
#include <harry_plotter.h>


class ImguiCoppeliaSimInterface: public JuanGui_Wrapper
{
protected:
    std::shared_ptr<MyYamlReader> my_yaml_reader_ptr_;
    std::string ip_;
    std::vector<std::string> jointnames_;
    VectorXd q_min_;
    VectorXd q_max_;
    VectorXd q_;
    VectorXd q_dot_;
    VectorXd q_dot_min_;
    VectorXd q_dot_max_;
    double simulation_time_ = 0.0;

    int n_joints_;

    bool data_available_;
    void _update_data_from_driver();

    int port_;
    std::string status_msg_;
    std::unique_ptr<CoppeliaSimDriver> coppeliasim_driver_;

    bool show_message_window_ = false;
    std::string message_window_;
    void set_message_window_parameters(const bool& flag, const std::string& msg);

    bool show_exit_window_ = false;


    void _check_parameter_sizes();

    void _stop_app();

    void _create_table_data(const std::vector<std::string>& labels,
                            const std::vector<Eigen::VectorXd>& q_table);

    std::vector<Eigen::VectorXd> _create_vector_for_table_data(const VectorXd& min,
                                                               const VectorXd& value,
                                                               const VectorXd& max);

public:

    ImguiCoppeliaSimInterface(const juangui_wrapper_parameters& parameters);



    void my_custom_gui() override;
    void show_main_menu_bar();
    void show_coppeliasim_app_parameters();
    void show_table_parameters();
    void show_console_window();

    void show_joint_position_plots();



    void show_message_window();
    void show_exit_window();

    void create_sas_driver_buttons();

    void connect_coppeliasim();
    void initialize_coppeliasim();
    void deinitialize_coppeliasim();
    void disconnect_coppeliasim();





};
