![Static Badge](https://img.shields.io/badge/Platform-Ubuntu_x64-orange)![Static Badge](https://img.shields.io/badge/untested-red)![Static Badge](https://img.shields.io/badge/Platform-Apple_silicon-magenta)![Static Badge](https://img.shields.io/badge/tested-green)![Static Badge](https://img.shields.io/badge/Written_in-C%2B%2B17-blue)![Static Badge](https://img.shields.io/badge/dqrobotics-cpp-ff0000)![Static Badge](https://img.shields.io/badge/dqrobotics-interface_coppeliasim-ff0000)![Static Badge](https://img.shields.io/badge/backend-glfw_opengl3-green)

![ezgif com-video-to-gif-converter (2)](https://github.com/juanjqo/coppeliasim_monitor/assets/23158313/f1ead4dd-0d53-4f84-83ec-f2bcbd9bf696)


CopppeliaSim Monitor is powered by [Dear Imgui](https://github.com/ocornut/imgui), [DQ Robotics](https://dqrobotics.github.io/), and the unofficial [DQ Robotics Coppelia Interface](https://github.com/juanjqo/cpp-interface-coppeliasim).

| CoppeliaSim  | SO | Status |
| ------------- | ------------- |------------- |
| ![Static Badge](https://img.shields.io/badge/CoppeliaSim-4.6.0--rev18-orange)![Static Badge](https://img.shields.io/badge/arm64-blue)| macOS Sonoma (Apple Silicon) | ![Static Badge](https://img.shields.io/badge/experimental-red)|
| ![Static Badge](https://img.shields.io/badge/CoppeliaSim-4.6.0--rev18-orange)![Static Badge](https://img.shields.io/badge/x64-blue)   | Ubuntu 22.04 LTS  |  ![Static Badge](https://img.shields.io/badge/Unsupported-gray)|
| ![Static Badge](https://img.shields.io/badge/CoppeliaSim-4.6.0--rev18-orange)![Static Badge](https://img.shields.io/badge/x64-blue)   | Windows 11  |  ![Static Badge](https://img.shields.io/badge/Unsupported-gray)


## Requirements

- DQ Robotics
- [cpp-interface-coppeliasim](https://github.com/juanjqo/cpp-interface-coppeliasim)

### MacOS (Apple Silicon)

```shell
brew install glfw
brew install fmt
brew install eigen
brew install yaml-cpp
```

### Ubuntu (Not supported, but I'm working on it!)



```shell
sudo add-apt-repository ppa:dqrobotics-dev/development
sudo apt-get update
sudo apt-get install libdqrobotics
```

```shell
sudo apt-get update
sudo apt install xorg-dev
sudo apt install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules
sudo apt install cmake g++ libeigen3-dev fakeroot
```
