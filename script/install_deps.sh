#!/bin/bash

source /etc/os-release

case $ID in
    ubuntu)
        echo "Ubuntu Linux"
        sudo apt update
        sudo apt install -y libglew-dev libassimp-dev libfreetype-dev
        sudo apt install -y build-essential git make \
            pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
            libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
            libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
            libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
            libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev \
            libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev libx11-dev
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
