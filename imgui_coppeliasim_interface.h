#pragma once
#include <juangui_wrapper.h>
#include <juancho_tools.h>
#include <cmath>




class ImguiCoppeliaSimInterface: public JuanGui_Wrapper
{
protected:
    std::string capi_path_;
public:

    ImguiCoppeliaSimInterface(const juangui_wrapper_parameters& parameters);


    void my_custom_gui() override;

    void set_capi_path(const std::string& my_path);

    //void signal_generator();

    //void Demo_RealtimePlots();


};
