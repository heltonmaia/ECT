echo "Upgrading and updating\n"
sudo apt-get update && sudo apt-get upgrade

echo "Install OS libraries\n" 
sudo apt-get remove x264 libx264-dev

sudo apt-get install build-essential checkinstall cmake pkg-config yasm git gfortran libjpeg8-dev libjasper-dev libpng12-dev libtiff5-dev libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine2-dev libv4l-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev qt5-default libgtk2.0-dev libtbb-dev libatlas-base-dev libfaac-dev libmp3lame-dev libtheora-dev libvorbis-dev libxvidcore-dev libopencore-amrnb-dev libopencore-amrwb-dev x264 v4l-utils libprotobuf-dev protobuf-compiler libgoogle-glog-dev libgflags-dev libgphoto2-dev libeigen3-dev libhdf5-dev doxygen 

echo "Install Python libraries\n"
sudo apt-get install python-dev python-pip python3-dev python3-pip -H pip2 install -U pip numpy -H pip3 install -U pip numpy

echo "Download opencv from Github\n"
git clone https://github.com/opencv/opencv_contrib.git
cd opencv_contrib
git checkout 3.3.1
cd ..

echo "Compile and install OpenCV with contrib modules\n"
echo "Create a build directory\n"
cd opencv
mkdir build
cd build

echo "Run CMake\n"
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_C_EXAMPLES=ON \
      -D INSTALL_PYTHON_EXAMPLES=ON \
      -D WITH_TBB=ON \
      -D WITH_V4L=ON \
      -D WITH_QT=ON \
      -D WITH_OPENGL=ON \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      -D BUILD_EXAMPLES=ON ..

echo "Compile and Install\n"
make -j4
sudo make install
sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig

echo "Done!\n"


