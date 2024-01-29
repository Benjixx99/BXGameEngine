![BXGameEngineLogo](https://github.com/Benjixx99/BXGameEngine/blob/main/BXGameEngineLogo.png)

# BXGameEngine

The BXGameEngine is a lightweight  2D Game Engine that allows **programmers** to develop 2D 
games with C++. It uses an [ECS](https://en.wikipedia.org/wiki/Entity_component_system) 
system at its core that makes it really simple to add properties to an entity.

## Technologies

A list of technologies used within the project:
* C++17
* [CMake](https://cmake.org/): Version 3.27.1
* [SFML](https://www.sfml-dev.org): Version 2.6.0
* [SQLite](https://www.sqlite.org): Version 3.44.2
* [Qt](https://www.qt.io) Version 6.6.1

## Build BXGameEngine

**Windows:**

Create a `sqlite3.lib` file, explained [here](https://gist.github.com/zeljic/d8b542788b225b1bcb5fce169ee28c55). After that move the `sqlite3.lib` file to `SQLite/lib` and 
the `sqlite3.h` file to `SQLite/include`.

Add the following paths to your system environment variable **path**: \
&emsp; driverLetter\yourPath\\`SFML-2.6.0\bin` \
&emsp; driverLetter\yourPath\\`Qt\6.6.1\msvc2019_64\bin` \
&emsp; driverLetter\yourPath\\`SQLite\include` \
&emsp; driverLetter\yourPath\\`SQLite\lib`

Open a terminal and navigate to the project directory where the `CMakeLists.txt` file is located
and then execute the following commands to build the BXGameEngine.

```
mkdir Build
cd Build
cmake -S ../ -B . 
cmake --build .
```

After the project was build move or copy the "Levels" and "Resources" folders and all needed `.dll`
files to `Build/Debug` where the executable file resides.

Needed `.dll` files: \
&emsp; `openal32.dll` , `Qt6Core.dll` , `Qt6Gui.dll` , `Qt6Widgets.dll` , `sfml-audio-d-2.dll` , \
&emsp; `sfml-graphics-d-2.dll` , `sfml-window-d-2.dll` , `sqlite3.dll` 

## Features to add to BXGameEngine

- Settings Menu
- Particle system
- More camera functions
- More NPC behaviours
- 3D features with OpenGL (later)

## Meaning of the acronyms used

- **AAD** = Algorithm And Datastructure
- **ECS** = Entity Components System
- **PAM** = Physics And Math
- **SSC** = System Service Classes

## Contact

If you want to contact me send an e-mail to: anon_writer@use.startmail.com

## License

This project uses the MIT license. For more information look at the [LICENSE](https://github.com/Benjixx99/BXGameEngine/blob/main/LICENSE) file.