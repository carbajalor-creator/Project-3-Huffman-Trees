cmake_minimum_required(VERSION 3.30)
project(CS315_Project_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(CS315_Project_3 main.cpp
        Scanner.cpp
        Scanner.hpp
        utils.cpp
        utils.hpp
        bst.cpp
        bst.hpp
        TreeNode.hpp)
