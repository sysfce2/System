#! /bin/bash

cd "$(dirname "$0")"

clang++ -Wl,--no-undefined -I../include main.cpp ../src/System.cpp ../src/Filesystem.cpp ../src/Library.cpp ../src/System_internals.cpp -ldl -o linux.exe
clang++ -Wl,--no-undefined -DWANT_SYSTEM_SHARED_LIBRARY_EXPORTS -I../include shared_main.cpp ../src/System.cpp ../src/SystemExports.cpp ../src/System_internals.cpp -ldl -shared -fPIC -o shared.so
