echo "Compilando tudo ..."
g++ -ggdb train.cpp -o train `pkg-config --cflags --libs opencv`
g++ -ggdb test.cpp -o test `pkg-config --cflags --libs opencv`
g++ -ggdb hog.cpp -o hog `pkg-config --cflags --libs opencv`
g++ -ggdb edges.cpp -o edges `pkg-config --cflags --libs opencv`

g++ -ggdb sampling/samples_hog.cpp -o sampling/hog `pkg-config --cflags --libs opencv`
g++ -ggdb sampling/samples_test.cpp -o sampling/test `pkg-config --cflags --libs opencv`