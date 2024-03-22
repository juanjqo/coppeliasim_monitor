#pragma once
#include <juangui_wrapper.h>
#include <juancho_tools.h>
#include <cmath>
#include <my_yaml_reader.h>
#include <memory>
#include <filesystem>


class ImguiCoppeliaSimInterface: public JuanGui_Wrapper
{
protected:
    std::shared_ptr<MyYamlReader> my_yaml_reader_ptr_;
public:

    ImguiCoppeliaSimInterface(const juangui_wrapper_parameters& parameters);



    void my_custom_gui() override;



    //void signal_generator();

    //void Demo_RealtimePlots();


};
