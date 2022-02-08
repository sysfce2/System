#! /bin/bash

cd "$(dirname "$0")"

clang++ -std=c++14 -I../include main.cpp ../src/System.cpp ../src/Filesystem.cpp ../src/Library.cpp ../src/System_internals.cpp -ldl -o macos.exe
clang++ -std=c++14 -I../include shared_main.cpp ../src/System.cpp ../src/System_internals.cpp -ldl -shared -fPIC -o shared.dylib
