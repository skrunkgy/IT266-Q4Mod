#!/bin/bash

# Script that simply builds binary with our cmake list

cmake -S . -B build
cd build
make
