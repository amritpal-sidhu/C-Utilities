#!/bin/bash

set -e


build_type="Debug"
source_dir="${PWD}"
build_dir="${PWD}/_build"
options=("-D CMAKE_BUILD_TYPE=$build_type")

case $1 in

"")
    cmake -S $source_dir -B $build_dir ${options[*]}
    cmake --build $build_dir
;;

"-c"|"--clean")  cmake --build $build_dir --target clean
;;

"-d"|"--delete")  rm -rf $build_dir
;;

"-h"|"--help"|*)
    echo "Usage: ./build.sh [options]"
    echo "Options:"
    echo "When called with no options cmake will configure and build the project"
    echo "-h, --help         print this message"
    echo "-c, --clean        clean the cmake project"
    echo "-d, --delete       remove the build directory"
;;

esac
