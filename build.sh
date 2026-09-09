#!/bin/bash
# I've added this build script in to support IDE's on Linux that do not have a CMake extension such as nvim etc
cmake -S . -B build
cd build
make
