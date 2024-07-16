#!/bin/sh
cd libs
mkdir read_lib
cd readline_main
./configure --prefix=$(pwd)/../read_lib
make
make install