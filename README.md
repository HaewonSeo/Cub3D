# Cub3D
My first RayCaster with miniLibX

## Summary
This project is inspired by the world-famous eponymous 90’s game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

## Instruction
+ I recommend running this program on MacOS.
+ Running programs on Windows requires using WSL2 or VM, and other complex configurations.
+ If you still want to run the program on Windows, please refer to the document below.
	+ https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#getting-a-screen-on-wsl2

1. ```git clone https://github.com/HaewonSeo/Cub3D.git```
2. ```make```
3.	- ```./cub3D ./cubs/cub.cub``` : start a game
	- ```./cub3D ./cubs/cub.cub --save``` : make a screenshot.bmp
4. `Press WASD key`, `left(<-), rigth(->), up, down arrow key` : move a player
5. `Press ESC key` : exit a game

+ Information about the game can be set in the /cubs/*.cub file.
+ .cub files have a format and must be followed.
+ The default rules are stored in the /cubs/cub.cub file.

## Preview
![screenshot](./screenshot.bmp)

## Reference
+ `Wolfenstein 3D` : http://users.atw.hu/wolf3d/
+ `Raycastiong` : https://lodev.org/cgtutor/raycasting.html
