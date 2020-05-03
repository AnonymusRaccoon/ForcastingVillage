# ForecastingVillage

You enter in a cursed village where it's raining constantly. Save the village from this curse by finding the 4 secrets items that will allow you to defeat the final enemy.

## Building
To build this project, you will first need to clone it with the recursive option ``git clone --recurse git@github.com:AnonymusRaccoon/ForecastingVillage.git``. This will clone the game engine and it's dependencies with this project.

After cloning the repository, you have two ways to build the repo. You can simply use the makefile and run ``make`` or you can use the cmake and run ``mkdir build && cd build && cmake .. && make -j``

## Libraries
This project has been made using [Gamacon](https://github.com/AnonymusRaccoon/Gamacon) an ECS C-Modular game engine and the [CSFML](https://www.sfml-dev.org/download/csfml/).
