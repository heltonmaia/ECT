cmake_minimum_required(VERSION 2.8)
project( orb )
find_package( OpenCV REQUIRED )
add_executable( orb orb.cpp)
target_link_libraries( orb ${OpenCV_LIBS} )

