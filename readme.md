# portal2-internal
___
A simple Portal 2/Portal Reloaded internal cheat base with imgui-based menu coded in a few days because why not

___
## Features:
 - simple menu engine
 - wnd-proc based input system
 - quite simple(but still) configs-system
 - bunnyhop and autostrafer along with some patches that would bring csgolike movement to portal2
 - support for the vulkan game version
 - chams
 - portal color changer
 - mat ambient light modifications
 - trails

![menu-preview](https://i.imgur.com/RqOjrqH.png)

___
## Contributing

Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

___
## Building

- CMake
	```commandline
	cmake -B build -A Win32
	cmake --build build --config Release
	```
- Visual Studio
	- Building from command line
		```commandline
		msbuild portal2-internal.sln /p:Configuration=Release
		```
	- Building from Visual Studio Interface using `msvc\portal2-internal.sln`
	- Creating sln file using cmake and building from it `build\portal2-internal.sln`
		```commandline
		cmake -B build -A Win32
		```

___
## Special thanks

###### Used libraries
- [nlohmann/json](https://github.com/nlohmann/json)
- [fmtlib/fmt](https://github.com/fmtlib/fmt)
- [ocornut/imgui](https://github.com/ocornut/imgui)

###### Projects used as references
- [spirthack/CSGOSimple](https://github.com/spirthack/CSGOSimple)
