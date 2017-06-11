rm -f build
mkdir -p build
cd build
cmake ../
make
make test
