#!/bin/bash

source /etc/os-release

case $ID in
    ubuntu)
        echo "Ubuntu Linux"
        sudo apt update
        sudo apt install -y  libsdl3-dev libglew-dev libassimp-dev libfreetype-dev
        ;;

    debian)
        echo "Debian TODO"
        ;;

    arch)
        echo "Arch Linux"
        sudo pacman -S sdl3 glew assimp freetype2
        ;;
esac
    
