cmake_minimum_required(VERSION 2.8)

# List the files of the current local project 
#    Default behavior: Automatically add all hpp and cpp files from src/ directory
#    You may want to change this definition in case of specific file structure
file(GLOB_RECURSE src_files ${CMAKE_CURRENT_LIST_DIR}/src/*.[ch]pp)

# Generate the executable_name from the current directory name
get_filename_component(executable_name ${CMAKE_CURRENT_LIST_DIR} NAME)
# Another possibility is to set your own name: set(executable_name your_own_name) 
message(STATUS "Configure steps to build executable file [${executable_name}]")
project(${executable_name})

# Add current src/ directory
include_directories("src")

# Include files from the library (vcl as well as external dependencies)
#  > The relative path to the VCL library may need to be adapted
include("library/CMakeLists.txt")


# Add all files to create executable
#  @src_files: the local file for this project
#  @src_files_vcl: all files of the VCL library
#  @src_files_third_party: all third party libraries compiled with the project
add_executable(${executable_name} ${src_files_vcl} ${src_files_third_party} ${src_files})

# Set Compiler for Unix system
if(UNIX)
   set(CMAKE_CXX_COMPILER g++)                      # Can switch to clang++ if prefered
   add_definitions(-g -O2 -std=c++14 -Wall -Wextra) # Can adapt compiler flags if needed
endif()

# Set Compiler for Windows/Visual Studio
if(MSVC)
    add_definitions(/MP /wd4244)   # Parallel build (/MP)
    source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src_files})  #Allow to explore source directories as a tree in Visual Studio
endif()



# Link options for Unix
target_link_libraries(${executable_name} ${GLFW_LIBRARIES})
if(UNIX)
   target_link_libraries(${executable_name} dl) #dlopen is required by Glad on Unix
endif()

