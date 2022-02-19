#!/bin/sh
cmake -S . -B ./bin/
cd bin
make
./ioc