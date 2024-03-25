#include "coppeliasim_driver.h"


CoppeliaSimDriver::CoppeliaSimDriver() {
    parameters_ready_ = false;
}



void CoppeliaSimDriver::set_parameters(const std::string& ip,
                                       const int& port,
                                       const std::vector<std::string>& jointnames,
                                       const std::tuple<VectorXd, VectorXd>& joint_limits,
                                       const std::tuple<VectorXd, VectorXd>& joint_velocity_limits)
{
    ip_ = ip;
    port_ = port;
    jointnames_ = jointnames;
    std::tie(q_min_, q_max_) = joint_limits;
    std::tie(q_dot_min_, q_dot_max_) = joint_velocity_limits;
}

std::vector<std::string> CoppeliaSimDriver::get_jointnames()
{
    return jointnames_;
}


std::tuple<VectorXd, VectorXd> CoppeliaSimDriver::get_joint_limits()
{
    return {q_min_, q_max_};
}

std::tuple<VectorXd, VectorXd> CoppeliaSimDriver::get_joint_velocity_limits()
{
    return {q_dot_min_, q_dot_max_};
}

int CoppeliaSimDriver::get_port()
{
    return port_;
}
