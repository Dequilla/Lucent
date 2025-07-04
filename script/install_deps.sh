#!/bin/bash

source /etc/os-release

case $ID in
    ubuntu)
        echo "Ubuntu Linux"
        sudo apt update
        sudo apt install -y libglew-dev libassimp-dev libfreetype-dev
        ;;

    debian)
        echo "Debian TODO"
        ;;

    arch)
        echo "Arch Linux"
        sudo pacman -S glew assimp freetype2
        ;;
esac
    
git clone https://github.com/libsdl-org/SDL.git vendor/SDL
