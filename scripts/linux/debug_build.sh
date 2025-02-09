cd "$(dirname "${BASH_SOURCE[0]}")/../..";
cd build;
cmake -DCMAKE_BUILD_TYPE=Debug ..;
make;
