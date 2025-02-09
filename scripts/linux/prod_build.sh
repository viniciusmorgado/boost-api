cd "$(dirname "${BASH_SOURCE[0]}")/../..";
cd build;
cmake -DCMAKE_CXX_COMPILER=clang++ ..;
make;
