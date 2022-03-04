rm cmake_install.cmake
rm CMakeCache.txt
cmake ./
make landmark
make test
rm cmake_install.cmake
rm CMakeCache.txt