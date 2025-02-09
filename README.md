# boost-api
C++ Service template created only with Boost.Beast library.

# How to debug the thing

./scripts/linux/debug_build.sh

gdb ./boost_api

set logging enabled on

run

# will stop on a breakpoint

next

# next until the segment fault, or the bug