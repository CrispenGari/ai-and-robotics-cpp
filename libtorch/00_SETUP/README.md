## LibTorch Setup for C++ and Visual Studio 2019

In this `README` file we are going to show step by step in setting up `pytorch` for `C++` on a `CPU` on a windows machine.

First things first make sure you downloaded and installed [`Visual Studio Code 2019`](https://visualstudio.microsoft.com/downloads/) on your windows machine.

> We are going to configure this pytorch on a windows computer using `Cmake`.

### Downloading LibTorch

LibTorch is a C++/Java distribution for pytorch. If you go pytorch [documentation](https://pytorch.org/get-started/locally/) you can either select the debug or released distribution of lib-torch the procedure in configuration will be the same.

### Downloading `LibTorch` distribution

You can download LibTorch distribution running the following command on windows:

```shell
wget https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-1.10.1%2Bcpu.zip
```

> Note that the latest version of `LibTorch` distribution can be downloaded [here](https://pytorch.org/get-started/locally/).

### Extracting the Distribution

In my case I'm going to create a folder in the `C` drive called `LibTorch` and in this folder I will extract the downloaded LibTorch distribution.

### Creating a Cmake Project

After downloading and extracting `LibTorch` copy the path of where it is located in my case libtorch is located in the `C` drive:

<img src="https://github.com/CrispenGari/ai-and-robotics-cpp/blob/main/libtorch/00_SETUP/images/0.png" width="100%" alt=""/>

the path will be:

```shell
C:\libtorch
```

1. Open Visual Studio Code and Create a `Cmake` Project.
2. When the project is created open the file called `CMakeLists.txt` and add the following configurations:

```c++
cmake_minimum_required (VERSION 3.8)

find_package(Torch REQUIRED)
add_executable (CMakeProject2 "CMakeProject2.cpp" "CMakeProject2.h")

target_link_libraries(CMakeProject2 "${TORCH_LIBRARIES}")

if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET CMakeProject2
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:CMakeProject2>)
endif (MSVC)
```

- One thing to note is that Visual Studio code created `CMakeLists.txt` file by default with some basic configurations.

- `find_package(Torch REQUIRED)` tells `CMake` to find pytorch package and it is a required package. Next we are going to tell it where to find the package.

Click the pointed dropdown from the figure

<img src="https://github.com/CrispenGari/ai-and-robotics-cpp/blob/main/libtorch/00_SETUP/images/1.png" width="100%" alt=""/>

- Then select **`Manage Configurations`**.
- Scroll down and find where it says **Command Arguments**
- Under **`CMake Command Arguments`** and the path where your `TorchLib` is as follows:

```shell
-DCMAKE_PREFIX_PATH="<absolute path to torchlib>"
```

Example in my case torch lib is located at:

```shell
C:\libtorch
```

So my **`CMake Command Arguments`** will be:

```shell
-DCMAKE_PREFIX_PATH="C:\\libtorch"
```

<img src="https://github.com/CrispenGari/ai-and-robotics-cpp/blob/main/libtorch/00_SETUP/images/2.png" width="100%" alt=""/>
Click `Ctrl + S` to save.

> Now we are ready to open the `.cpp` file and write some code.

### Creating a simple pytorch tensor

Now we can open `CMakeProject2.cpp` file and add the following code to it:

```c++
#include "CMakeProject2.h"
#include <torch/torch.h>
using namespace std;

int main()
{
	torch::Tensor tensor = torch::eye(3);
	cout <<tensor << endl;
	return 0;
}

```

Click Debug and then you will be able to se the following output if everything went well

### Output

If everything goes well we will be able to see the following output on the screen.

```shell
 1  0  0
 0  1  0
 0  0  1
[ CPUFloatType{3,3} ]
```

### Refs

1. [raminnabati.com](https://raminnabati.com/post/004_adv_pytorch_integrating_pytorch_cpp_frontend_in_visual_studio_on_windows/)
2. [pytorch.org/get-started](https://pytorch.org/get-started/locally/)
3. [pytorch.org/tutorials/advanced/cpp_frontend](https://pytorch.org/tutorials/advanced/cpp_frontend.html)
4. [docs.microsoft.com](https://docs.microsoft.com/en-us/answers/questions/414756/setting-visual-studio-for-pytorch-c.html)
