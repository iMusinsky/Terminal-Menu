#!/bin/bash

build_dir="build"

echo "Removing old build"
rm -r $build_dir

mkdir $build_dir && cd $build_dir
cmake ../ -DBUILD_EXAMPLE=ON && cmake --build .
cd ../
