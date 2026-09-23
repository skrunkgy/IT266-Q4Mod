#!/bin/bash
# Script to build stuff, comes with compile commands for clangd :)
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
