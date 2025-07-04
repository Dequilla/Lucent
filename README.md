# Lucent Engine

```
▄█       ███    █▄   ▄████████    ▄████████ ███▄▄▄▄       ███    
███       ███    ███ ███    ███   ███    ███ ███▀▀▀██▄ ▀█████████▄
███       ███    ███ ███    █▀    ███    █▀  ███   ███    ▀███▀▀██
███       ███    ███ ███         ▄███▄▄▄     ███   ███     ███   ▀
███       ███    ███ ███        ▀▀███▀▀▀     ███   ███     ███    
███       ███    ███ ███    █▄    ███    █▄  ███   ███     ███    
███▌    ▄ ███    ███ ███    ███   ███    ███ ███   ███     ███    
█████▄▄██ ████████▀  ████████▀    ██████████  ▀█   █▀     ▄████▀  
▀
```
A cross-plattform homebuilt rendering engine for educational purposes.

[![Lucent Build](https://github.com/Dequilla/Lucent/actions/workflows/lucent_cross_platform_build.yml/badge.svg?branch=master)](https://github.com/Dequilla/Lucent/actions/workflows/lucent_cross_platform_build.yml)

## Contributing
Lucent enforces clang formatting, config file included.

## Requirements
Lucent uses CMake as it's build system. Both clang and gcc builds are test-built for the master-branch on an ubuntu machine.

- *Linux*
  - A script to install dependencies them exists `./script/install_deps.sh` which detects platform and installs. Currently only arch-linux and ubuntu supported.
- *Windows*
  - A script has to be created. Needed dependencies are not included.
- *Mac*
  - A script has to be created. Needed dependencies are not included.

## Building
Now you can build it:

```shell
cd path/to/Lucent/build
sh build.sh
```
The build will appear in `Lucent/build/bin/src` run by `cd bin/src/ && ./Lucent`.
You can add `--clean` to create a clean build (ex: `sh build.sh --clean`).
You can add `--debug` to create a debug build (ex: `sh build.sh --debug`).
These flags cannot be combined as of now.

Or build and run via:
```shell
./script/run.sh
```

## Current progress
![alt text](https://github.com/Dequilla/Lucent/raw/master/progress_latest.png "An image of the engine in action with the current build")
