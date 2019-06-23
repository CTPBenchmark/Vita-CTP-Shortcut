#!/usr/bin/env bash
# Here the commands to build your app
cd /build/git
ls
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..;
make
