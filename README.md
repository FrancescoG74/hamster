# Hamster Game (C++/Qt6)

This is a starter project for a 2D game called "Hamster" using C++ and Qt6.

## Requirements
- Qt 6 (Core, Gui, Widgets)
- CMake >= 3.16
- C++17 compatible compiler

## Build Instructions

1. Install Qt6 and CMake if not already installed.
2. From the project root, run:
	```bash
	cmake -B build
	cmake --build build
	```
3. Run the game:
	```bash
	./build/hamster
	```

## Project Structure

- `src/` — file sorgente C++ (`main.cpp`, `GameWidget.cpp`, `Hamster.cpp`)
- `include/` — header file (`GameWidget.h`, `Hamster.h`)
- `CMakeLists.txt` — configurazione build
- `build/` — directory di build (ignorata da git)
- `.vscode/` — impostazioni locali di Visual Studio Code (ignorata da git)

Puoi ora iniziare ad aggiungere la logica e l'interfaccia del tuo gioco!
