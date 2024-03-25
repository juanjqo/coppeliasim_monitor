#pragma once
#include <string>
#include <yaml-cpp/yaml.h>
#include <Eigen/Dense>
#include <juancho_tools.h>
#include <dqrobotics/interfaces/vrep/DQ_VrepInterface.h>
#include <memory>
#include <yaml-cpp/yaml.h>

class CoppeliaSimDriver
{
protected:
    std::string ip_;
    std::vector<std::string> jointnames_;
    Eigen::VectorXd q_min_;
    Eigen::VectorXd q_max_;
    Eigen::VectorXd q_dot_min_;
    Eigen::VectorXd q_dot_max_;
    int port_;

    std::unique_ptr<DQ_VrepInterface> vi_;
    bool parameters_ready_;

public:
    CoppeliaSimDriver();
    void set_parameters(const std::string& ip,
                        const int& port,
                        const std::vector<std::string>& jointnames,
                        const std::tuple<Eigen::VectorXd, Eigen::VectorXd>& joint_limits,
                        const std::tuple<Eigen::VectorXd, Eigen::VectorXd>& joint_velocity_limits
                        );
    void set_parameters_from_yaml(const std::string& yaml_file_path);

    std::string get_ip();
    std::vector<std::string> get_jointnames();
    std::tuple<Eigen::VectorXd, Eigen::VectorXd> get_joint_limits();
    std::tuple<Eigen::VectorXd, Eigen::VectorXd> get_joint_velocity_limits();
    int get_port();
};

