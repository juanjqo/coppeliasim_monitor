#pragma once
#include <juangui_wrapper.h>
#include <juancho_tools.h>
#include <cmath>




class ImguiCoppeliaSimInterface: public JuanGui_Wrapper
{
protected:

public:

    ImguiCoppeliaSimInterface(const juangui_wrapper_parameters& parameters);


    void my_custom_gui() override;



    //void signal_generator();

    //void Demo_RealtimePlots();


};
