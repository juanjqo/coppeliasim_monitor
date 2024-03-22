#include "my_yaml_reader.h"


void MyYamlReader::_start_settings()
{
    try {
        std::cout << "Config file path: " << config_path_ <<std::endl;
        YAML::Node config = YAML::LoadFile(config_path_);
        //const int size = config.size();
        std::cout << "----------------------------------------------" <<std::endl;

        //std::cout << "Constraints found in the config file: " << config.size() <<std::endl;
        std::cout << "----------------------------------------------" <<std::endl;
        //----------------------------------------------------------------------------------

        int i = 0;
        // The outer element is an array
        for(auto dict : config) {
            // The array element is a map containing the Description and Parameters keys:
            auto name = dict["Description"];
            //std::cout << "       " <<std::endl;
            //std::cout<<"Constraint: "<<i+1<<std::endl;
            std::cout <<"Description: " << name << std::endl;
            auto rect = dict["Parameters"];
            /*
            for(auto pos : rect) {
                auto raw_vfi_type = pos["vfi_type"].as<std::string>();
                auto raw_cs_entity_environment = pos["cs_entity_environment"].as<std::string>();
                auto raw_cs_entity_robot = pos["cs_entity_robot"].as<std::string>() ;
                auto raw_entity_environment_primitive_type =  pos["entity_environment_primitive_type"].as<std::string>();
                auto raw_entity_robot_primitive_type = pos["entity_robot_primitive_type"].as<std::string>();
                auto raw_robot_index = pos["robot_index"].as<double>();
                auto raw_joint_index =  pos["joint_index"].as<double>();
                auto raw_safe_distance = pos["safe_distance"].as<double>();
                auto raw_direction =  pos["direction"].as<std::string>();
                auto raw_entity_robot_attached_direction = pos["entity_robot_attached_direction"].as<std::string>();
                auto raw_entity_environment_attached_direction = pos["entity_environment_attached_direction"].as<std::string>();


                    std::cout << raw_vfi_type << ",\t"
                              << raw_cs_entity_environment  << ",\t"
                              << raw_cs_entity_robot << ",\t"
                              << raw_entity_robot_primitive_type << ",\t"
                              << raw_entity_environment_primitive_type << ",\t"
                              << raw_robot_index << ",\t"
                              << raw_joint_index  << ",\t"
                              << raw_safe_distance<< ",\t"
                              << raw_direction << ",\t"
                              << raw_entity_robot_attached_direction << ",\t"
                              << raw_entity_environment_attached_direction << std::endl; */

                /*
                vfi_type_list_.     push_back(map_strings_to_vfiType(raw_entity_robot_primitive_type,
                                                                raw_entity_environment_primitive_type));
                direction_list_.    push_back(map_string_to_direction(raw_direction));
                safe_distance_list_.push_back(raw_safe_distance);
                robot_index_list_.  push_back(raw_robot_index);
                joint_index_list_.  push_back(raw_joint_index);
                dq_offset_list_.    push_back(_get_robot_primitive_offset_from_vrep(raw_cs_entity_robot,
                                                                                raw_robot_index,  //raw_robot_index,
                                                                                raw_joint_index));
                robot_attached_dir_list_.push_back(map_attached_direction_string_to_dq(raw_entity_robot_attached_direction));
                envir_attached_dir_list_.push_back(map_attached_direction_string_to_dq(raw_entity_environment_attached_direction));
                workspace_derivative_list_.push_back(DQ(0));
                cs_entity_environment_list_.push_back(raw_cs_entity_environment);

                //std::cout<<"VFI to be used: "<<map_vfyType_to_strig(map_strings_to_vfiType(raw_entity_robot_primitive_type,
                //                                                                        raw_entity_environment_primitive_type))<<std::endl;


                i++;
            }*/
        }

        std::cout << "----------------------------------------------" <<std::endl;

    } catch(const YAML::BadFile& e) {
        std::cerr << e.msg << std::endl;
        //return 1;
    } catch(const YAML::ParserException& e) {
        std::cerr << e.msg << std::endl;
        //return 1;
    }

}

MyYamlReader::MyYamlReader(const std::string &config_path)
{
    config_path_ = config_path;
    _start_settings();
}
