#pragma once
#include <iostream>
#include <yaml-cpp/yaml.h>

class MyYamlReader
{

protected:
    std::string config_path_;
    void _start_settings();
public:
    MyYamlReader(const std::string& config_path);
};


