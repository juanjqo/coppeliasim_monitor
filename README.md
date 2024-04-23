![Static Badge](https://img.shields.io/badge/Platform-Ubuntu_x64-orange)![Static Badge](https://img.shields.io/badge/tested-green)![Static Badge](https://img.shields.io/badge/Platform-Apple_silicon-magenta)![Static Badge](https://img.shields.io/badge/untested-red)![Static Badge](https://img.shields.io/badge/Written_in-C%2B%2B17-blue)![Static Badge](https://img.shields.io/badge/dqrobotics-cpp-ff0000)![Static Badge](https://img.shields.io/badge/dqrobotics-interface_coppeliasim-ff0000)![Static Badge](https://img.shields.io/badge/backend-glfw_opengl3-green)

![ScreenRecording2024-04-23at12 55 03-ezgif com-video-to-gif-converter](https://github.com/juanjqo/coppeliasim_monitor/assets/23158313/752ca428-49db-4df5-9d47-04605d04c556)


CopppeliaSim Monitor is powered by [Dear Imgui](https://github.com/ocornut/imgui), [DQ Robotics](https://dqrobotics.github.io/), and the unofficial [DQ Robotics Coppelia Interface](https://github.com/juanjqo/cpp-interface-coppeliasim).


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
