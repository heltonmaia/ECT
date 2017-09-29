g++ -ggdb `pkg-config --cflags opencv` -o `basename camera1ed.cpp .cpp` camera1ed.cpp `pkg-config --libs opencv`
