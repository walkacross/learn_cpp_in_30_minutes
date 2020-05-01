cmake_minimum_required(VERSION 3.14)
project(hello)

set(CMAKE_CXX_STANDARD 14)

add_executable(hello1 main.cpp src/hello1.cpp)
#add_executable(hello2 main.cpp src/hello2.cpp)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/

target_include_directories(hello1
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

#target_include_directories(hello2
#        PRIVATE
#        ${PROJECT_SOURCE_DIR}/include)

