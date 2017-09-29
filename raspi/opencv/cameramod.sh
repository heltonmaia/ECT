#!/bin/bash
g++ -ggdb `pkg-config --cflags opencv` -o `basename cameramod.cpp .cpp` cameramod.cpp funcoes.cpp `pkg-config --libs opencv`
