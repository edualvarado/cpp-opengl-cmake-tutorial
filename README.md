# C++/OpenGL Project Building Tutorial with CMake (Windows)

- [Introduction](#Introduction)
- [Initial Setup](#InitialSetup)
- [Generate a VS project using CMake](#VSCMake)
  - [Using the GUI](#GUI)
- [VS Configuration](#VSConfiguration)
- [Running the executable](#Executable)

<a name="Introduction"></a>

## Introduction

In this tutorial, you will learn how to build a **C++** and **OpenGL** project using **CMake** and **MS Visual Studio** for Windows.
In addition, we will be using **VCL** (Visual Computing Library) as OpenGL library for 3D programming.

The code contains two main parts:
* `library/vcl/` - It contains the 3D graphics library.
* `src/main.cpp` - The one C++ file containing our source code, which will be deployed afterwards into an standalone executable.

<a name="InitialSetup"></a>

## Initial Setup

For this short tutorial, we will be using **Windows 10** (x64), although other OS are perfectly compatible as well (in that case, please refer to other tutorials).

First, install [CMake](https://cmake.org/): We will be using this tool to build the project along with all its dependencies. For further details, refer to the [Official Documentation](https://cmake.org/).

Second, we will be using Windows and MS Visual Studio as IDE and C++ compiler (already set up). Besides, we will need the following add-ons in your Visual Studio installation: 
* **Desktop development with C++**
* **C++ CMake tools for Windows**

Refer to the [Official Documentation of MS Visual Studio](https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation) for further details.

<a name="#VSCMake"></a>

## Generate a VS project using CMake

First, we need to use CMake to build our project. To do so, all `CMakeList.txt` files must be already written and included in the root directory, in addition to all those dependencies (such as CMake is able to link all the necessary libraries). In the code,  the `CMakeList.txt` files are already provided.

In order to build the project, we can use the GUI from CMake:

<a name="GUI"></a>

### Using the GUI

To start CMake, open the executable `CMake (cmake-gui)`. There are two options that you need to define in this user-interface:
* `Where is the source code`: Add the root directory of your project. It must contain the main `CMakeList.txt` file.
* `Where to build the binaries`: Directory where you will store the built project. Normally it should be on `root_directory/build` (if you do not have a `build/` folder, you can create one).

After that, you will need to configure the generator to build a solution for your specific version of Visual Studio, under the option **Configure** (normally set up correctly by default).

Finally, click on **Generate**. On the log window, you can check the process status. After the process is completed, inside the `build/` directory you will fine all the required Visual Studio files along with the solution project `your_project.sln`.

Once the project is built, you will not have to do it again. Only if you modify your CMake, you should build it again to avoid any possible errors.

<a name="VSConfiguration"></a>

## VS Configuration

Once the solution along with all VS files are created in your `build/` folder, you can open the project by double-clicking to the `*.sln` file.

Inside the **Solution Explorer** window, you will be able to see all the different files that belong to your built project. There, do right click on the solution file and select **Properties**. You need to change the target, such that when you run the project, you do it on your code and not on any of the generic project that CMake builds for you, for example for testing reasons (such as `ALL_BUILD` or `ZERO_CHECK`).

Also, change the build type from `Debug` to `RelWithDebInfo`, in order to build it with the same optimization than a **Release** build but adding debug information on it.

Finally, on the option **Local Windows Debugger**, select the properties `your_project Debug Properties`. There, you can modify several options when building, such as the location of the `.exe` file with the option **Output Directory** (I tend to place it on the root directory normally, and not in the `build/` folder). Then, change the **Working Directory** in the **Debugging** property, from `$(ProjectDir)` to `$(TargetDir)`.

<a name="Executable"></a>

## Running the executable

Now, you can compile your project by clicking on **Build/Build Solution**. The executable can be run by opening the `.exe` file from the Folder Explorer (without debug information), or from Visual Studio, by clicking on **Local Windows Debugger** if you want to visualize the debug information.
