echo "Compiling..."
g++ -ggdb -std=c++11 train.cpp -o train `pkg-config --cflags --libs opencv`
g++ -ggdb -std=c++11 test.cpp -o test `pkg-config --cflags --libs opencv`
g++ -ggdb -std=c++11 hog.cpp -o hog `pkg-config --cflags --libs opencv`
g++ -ggdb -std=c++11 edges.cpp -o edges `pkg-config --cflags --libs opencv`
echo "Done!"

#g++ -ggdb -std=c++11 sampling/samples_hog.cpp -o sampling/hog `pkg-config --cflags --libs opencv`
#g++ -ggdb -std=c++11 sampling/samples_test.cpp -o sampling/test `pkg-config --cflags --libs opencv`