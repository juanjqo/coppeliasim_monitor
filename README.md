![Static Badge](https://img.shields.io/badge/Platform-Ubuntu_x64-orange)![Static Badge](https://img.shields.io/badge/tested-green)![Static Badge](https://img.shields.io/badge/Platform-Apple_silicon-magenta)![Static Badge](https://img.shields.io/badge/untested-red)![Static Badge](https://img.shields.io/badge/Written_in-C%2B%2B17-blue)![Static Badge](https://img.shields.io/badge/dqrobotics-cpp-ff0000)![Static Badge](https://img.shields.io/badge/dqrobotics-interface_vrep-ff0000)![Static Badge](https://img.shields.io/badge/backend-glfw_opengl3-green)

CopppeliaSim Monitor is powered by [Dear Imgui](https://github.com/ocornut/imgui) and [DQ Robotics](https://dqrobotics.github.io/).


## Requirements


### MacOS (Apple Silicon)

#### DQ Robotics

```shell
git clone https://github.com/dqrobotics/cpp
...
```

```shell
brew install glfw
brew install fmt
brew install eigen
brew install yaml-cpp
```

### Ubuntu 

#### DQ Robotics

```shell
sudo add-apt-repository ppa:dqrobotics-dev/development
sudo apt-get update
sudo apt-get install libdqrobotics
sudo apt-get install libdqrobotics-interface-vrep
```

```shell
sudo apt-get update
sudo apt install xorg-dev
sudo apt install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules
sudo apt install cmake g++ libeigen3-dev fakeroot
```
