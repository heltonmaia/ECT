cmake_minimum_required(VERSION 2.8)
project( track )
find_package( OpenCV REQUIRED )
add_executable( track main.cpp funcoes.cpp )
target_link_libraries( track ${OpenCV_LIBS} )

