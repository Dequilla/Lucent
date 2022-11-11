#!/bin/sh

echo "\nBuilding: \n"

echo " ▄█       ███    █▄   ▄████████    ▄████████ ███▄▄▄▄       ███    " 
echo "███       ███    ███ ███    ███   ███    ███ ███▀▀▀██▄ ▀█████████▄" 
echo "███       ███    ███ ███    █▀    ███    █▀  ███   ███    ▀███▀▀██" 
echo "███       ███    ███ ███         ▄███▄▄▄     ███   ███     ███   ▀" 
echo "███       ███    ███ ███        ▀▀███▀▀▀     ███   ███     ███    " 
echo "███       ███    ███ ███    █▄    ███    █▄  ███   ███     ███    " 
echo "███▌    ▄ ███    ███ ███    ███   ███    ███ ███   ███     ███    " 
echo "█████▄▄██ ████████▀  ████████▀    ██████████  ▀█   █▀     ▄████▀  " 
echo "▀"

echo "\n\n-LU- Creating bin..."
mkdir -p bin/

# Enter bin
cd bin/

# If we want a clean build clear bin
if [ "$1" = "--clean" ]; then
    echo "-LU- Clearing previous build..."

    rm -rf *
fi

# Run cmake in our root folder where our topmost CMakeLists.txt file is
echo "-LU- Running cmake..."
if [ "$1" = "--debug" ]; then
    echo "-LU- Building as debug..."
    cmake -DCMAKE_BUILD_TYPE=Debug ../../
else
    echo "-LU- Building as release..."
    cmake -DCMAKE_BUILD_TYPE=Release ../../
fi

# Compile program
echo "-LU- Running make..."
make

# Now move resources files
echo "-LU- Moving resources..."
cd src/

if [ -d "$Resources/" ]; then
    rm -rf Resources/
fi

cp -r ../../../src/Resources/ Resources/

if [ -d "$Shaders/" ]; then
    rm -rf Shaders/
fi

cp -r ../../../src/Shaders/ Shaders/
