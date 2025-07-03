#!/bin/bash

source /etc/os-release

case $ID in
    ubuntu)
        echo "Ubuntu Linux TODO"
        ;;

    debian)
        echo "Debian TODO"
        ;;

    arch)
        echo "Arch Linux"
        sudo pacman -S sdl3 glew assimp freetype2
        ;;
esac
    
