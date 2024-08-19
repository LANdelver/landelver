# LANdelver

LANdelver is a virtual tabletop application that hopes to bring the best parts of online D&D and video games to the in person experience. This application is a websocket enabled tool for screen tables or for displaying combat environments on a television or computer monitor. Players and dungeon masters will engage with the tool on their personal devices through a website allowing for character creation and combat controls. 

Another critical feature of LANdelver is a unique Lua scripting API that allows for the automation of enemies and spells into the battleground. This will help make combat less time exhaustive, enable large scale battles, and offer fun visual feedback to the players to keep up engagement. All of this is run locally using your Local Area Network (LAN) which means only the dungeon master has to keep all of the data + no data will be stored by a third party so you own all of your information and content!

### CMake

- Install python version 3.12 and its dev libs
- Install lua and its dev libs
- Type the following command:

```sh
cmake -S . -B build
```

> if you want with debug symbols put the flag `-DCMAKE_BUILD_TYPE=Debug`

- After CMake config you project build:

```sh
cmake --build build
```

- Inside the build folder are another folder (named the same as the project name on CMakeLists.txt) with the executable and resources folder.

### Server

- Go to web folder directory
- Run the script to find your local IP address
- Type the following command for one-time setup: 

```
python -m http.server 8000 --bind <lan ip>
```

- Now go to server directory and run server.py

### Contributing

LANdelver is still very early in development and is not open to contributions from independent parties at this time.

### License

This game sources are licensed under an unmodified GPL v3.0 license. Check [LICENSE](LICENSE) for further details.

LANdelver is unofficial Fan Content permitted under the Fan Content Policy. Not approved/endorsed by Wizards. Portions of the materials used are property of Wizards of the Coast. (c)Wizards of the Coast LLC.

*Copyright (c) 2024 Sariah Echols*

*Copyright (c) 2024 Lance Borden*
