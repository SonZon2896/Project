#! /bin/sh

cmake -DGLFW_BUILD_DOCS=OFF _DUSE_ADDER=ON -S . -B build

cd build ; make install