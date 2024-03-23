#pragma once
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <Eigen/Dense>
#include <juancho_tools.h>

class MyYamlReader
{

protected:
    std::string ip_;
    std::vector<std::string> jointnames_;
    std::vector<double> q_min_;
    std::vector<double> q_max_;
    std::vector<double> q_dot_min_;
    std::vector<double> q_dot_max_;
    int port_;

    std::string config_path_;
    void _start_settings();
public:
    MyYamlReader(const std::string& config_path);
    std::string get_ip();
    std::vector<std::string> get_jointnames();
    std::tuple<Eigen::VectorXd, Eigen::VectorXd> get_joint_limits();
    std::tuple<Eigen::VectorXd, Eigen::VectorXd> get_joint_velocity_limits();
    int get_port();
};


