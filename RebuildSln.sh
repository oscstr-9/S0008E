 
rm -rf bin
rm -rf build
mkdir build
cd build/
cmake ..
make
g++ Main.cpp -o main
cd ..
