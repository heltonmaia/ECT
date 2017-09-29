#!/bin/bash
g++ -ggdb `pkg-config --cflags opencv` -o `basename teste_pontos.cpp .cpp` teste_pontos.cpp `pkg-config --libs opencv`


