#!/bin/bash

mkdir -p bin
mkdir -p bin/resources

echo "Compiling C++ files..."
g++ -std=c++17 -Iinclude src/*.cpp -o bin/CatsBattle
if [ $? -ne 0 ]; then
    echo "C++ compilation failed!"
    exit 1
fi

echo "=============================="
echo "   Compiling Unit Tests...    "
echo "=============================="

g++ -std=c++17 unittests/tests.cpp src/Player.cpp src/Card.cpp src/utils.cpp -I include -I src -o bin/tests


if [ $? -eq 0 ]; then
    echo "Compilation Successful!"
    echo "--------------------------------"
    echo "   Running Tests..."
    echo "--------------------------------"

    ./bin/tests
    
    echo "--------------------------------"
else
    echo "❌ Compilation Failed."
    exit 1
fi