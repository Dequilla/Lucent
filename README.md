# A crossplatform game engine using OpenGL
##### NOTE *A hobby project*
###### *I learn as I go*

## Requirements

Uses SDL, GLEW, ASSIMP, GLM and OpenGL under the hood.

#### Building
CEngine uses CMAKE as it's building system. It is recommended to build out of source.

#### Linux - libraries required
On Ubuntu packages(tested):
- libsdl2-dev
- libglew-dev
- libassimp-dev

`sudo apt-get install libsdl2-dev libglew-dev libassimp-dev`

Other distros/unix-based systems are yet to be tested.

To build you also need CMAKE as stated before:

`sudo apt-get install cmake-curses-gui`

Now you can build it:

```shell
cd .../CEngine    (root/top directory of CEngine)
mkdir build
cd build
ccmake ../
```

Then press C twice to configure then G to generate. Press Q to quit, then run
`make` (Not sure if "make" will work nativly, may neet to install some packages).


#### Window - libraries required
On Windows any libaries needed come with the project under the "deps"-folder.


### Current progress
![alt text](https://github.com/Dequilla/CEngine/raw/master/progress_latest.png "An image of the engine in action with the current build")
