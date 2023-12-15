cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Find OpenCV libraries
find_package(OpenCV REQUIRED)

# Add executable
add_executable(MyProject main.cpp KLT.cpp FAST.cpp)

# Link executable to OpenCV libraries
target_link_libraries(MyProject ${OpenCV_LIBS})

#to launch: 

# cmake .
# cmake --build .
# ./MyProject