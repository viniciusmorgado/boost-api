cd "$(dirname "${BASH_SOURCE[0]}")/../..";
rm -R build/*;
cd build;
rm -R .cmake;
rm -R CMakeFiles;
