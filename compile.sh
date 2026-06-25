#!/bin/bash
#
# Compile script for SocialNet Simulator
#
# This script compiles all .cpp files into an executable named "socialnet".
#
# Flags:
# -std=c++17 : Use the C++17 standard
# -o socialnet : Specify the output executable name
# -Wall      : Enable all common compiler warnings
# -Wextra    : Enable extra warnings
# -g         : Include debugging information
#

echo "Compiling SocialNet Simulator..."

# This is the main command. It lists all your .cpp source files.
g++ -std=c++17 -o socialnet AVLTree.cpp Graph.cpp SocialNet.cpp main.cpp -Wall -Wextra -g

# This part just checks if the command above was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Run with: ./socialnet"
else
    echo "Compilation failed."
fi

