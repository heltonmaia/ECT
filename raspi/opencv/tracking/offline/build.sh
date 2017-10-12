#!/bin/bash
g++ -ggdb `pkg-config --cflags opencv` -o `basename trackoff.cpp .cpp` track_offline.cpp funcoes_toff.cpp `pkg-config --libs opencv`
