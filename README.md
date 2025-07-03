# A crossplatform game engine using OpenGL

## Contributing
Lucent enforces clang formatting, config file included.

## Requirements
Lucent uses CMake as it's build system.

### Linux
A script to install dependencies them exists `./script/install_deps.sh` which 
detects platform and installs. Currently only arch-linux supported.

### Windows
A script has to be created. Needed dependencies are not included.

### Mac
A script has to be created. Needed dependencies are not included.

## Building
Now you can build it:

```shell
cd path/to/Lucent/build
sh build.sh
```

You can add `--clean` to create a clean build (ex: `sh build.sh --clean`).
You can add `--debug` to create a debug build (ex: `sh build.sh --debug`).
These flags cannot be combined as of now.

The build will appear in `Lucent/build/bin/src` run by `cd bin/src/ && ./Lucent`.

## Current progress
![alt text](https://github.com/Dequilla/Lucent/raw/master/progress_latest.png "An image of the engine in action with the current build")
