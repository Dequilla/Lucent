# A crossplatform game engine using OpenGL
##### NOTE *A hobby project*
###### *I learn as I go*

## WoW - Way Of Working
- Work is done on dev or branches of dev
- Work to be added to master has to go through a pull request
- More TBD

## Requirements

Uses Freetype, SDL, GLEW, ASSIMP, GLM and OpenGL under the hood.

#### Building
CEngine uses CMAKE as it's building system. It is recommended to build out of source.

#### Linux - libraries required
On Ubuntu packages(tested):
- libsdl2-dev
- libglew-dev
- libassimp-dev
- libfreetype6-dev

`sudo apt-get install libsdl2-dev libglew-dev libassimp-dev libfreetype6-dev`

Other distros/unix-based systems are yet to be tested.

To build you also need CMAKE as stated before:

`sudo apt-get install cmake`

Now you can build it:

```shell
cd path/to/CEngine/build
sh build.sh
```

You can add `--clean` to create a clean build(ex: `sh build.sh --clean`).

The build will appear in `CEngine/build/bin/src`

#### Windows - libraries required
On Windows any libaries needed come with the project under the "deps"-folder.


### Current progress
![alt text](https://github.com/Dequilla/CEngine/raw/master/progress_latest.png "An image of the engine in action with the current build")
