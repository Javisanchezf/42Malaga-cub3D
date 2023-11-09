<div id="header" align="center">
  <img src="https://github.com/Javisanchezf/media/blob/main/cub3d_logo.png" width="200"/>
</div>

<h1 align="center">cub3D</h1>

> School 42 Project - Graphic design using Ray-Casting technique.

This repository contains all the files for the cub3D project in the School 42 curriculum.

<h2 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#requirements">Requirements</a>
	<span> · </span>
	<a href="#installation">Installation</a>
	<span> · </span>
	<a href="#usage">Usage</a>
	<span> · </span>
	<a href="#features">Features</a>
	<span> · </span>
	<a href="#controls">Controls</a>
	<span> · </span>
	<a href="#bonus">Bonus</a>
	<span> · </span>
	<a href="#author">Author</a>
	<span> · </span>
	<a href="#license">License</a>
</h2>

## About

The cub3D project is a graphic design project that utilizes the Ray-Casting technique to create a 3D representation of a maze. The project aims to develop a basic understanding of ray-casting, as well as graphic rendering using the MiniLibX library.

[You can find more information in the project subject](https://github.com/Javisanchezf/42Malaga-pdfs/blob/main/cub3D_subject.pdf).

The code in this repository follows [the rules of the Norminette](https://github.com/Javisanchezf/42Malaga-pdfs/blob/master/norme.pdf).

This is the result of the program:

<div align = center>
  <img src="https://github.com/Javisanchezf/42Malaga-cub3d/blob/main/screenshots/galaxy.webp" width="800"/>
</div>
<div align = center>
  <img src="https://github.com/Javisanchezf/42Malaga-cub3d/blob/main/screenshots/minecraft.webp" width="800"/>
</div>


## Requirements

The project is written in __C language__ and requires the following:

- Compiler `gcc`.
- Standard libraries:
  - `<stdlib.h>`
  - `<unistd.h>`
  - `<math.h>`
  - `<fcntl.h>`
- [MiniLibX Library](https://harm-smits.github.io/42docs/libs/minilibx)

## Installation

### 1. Download the repository

To download the repository, open a terminal and run:

```
git clone --recursive https://github.com/Javisanchezf/42Malaga-cub3d.git
cd 42Malaga-cub3d
```

### 2. Compiling the program

To compile the program, go to its path and run:


```
make
```


### 3. Running the program

To run the program, use the following command:


```
./cub3D maps/galaxy.cub
```


## Usage

- The program reads a scene description from a `.cub` file.
- The controls allow you to navigate through the 3D maze.
- Explore the maze and enjoy the ray-casting graphics!

## Features

- Basic ray-casting engine.
- Textured walls and sprites.
- Player movement and rotation.
- Map parsing from a configuration file.
- Configurable resolution and textures.
- Mouse rotation control.
- Doors that can open and close.
- Hidden final chest

## Controls

- `W` `A` `S` `D` - Move forward, left, backward, right.
- `0` - Active mouse control.
- `1` - Desactive mouse control.
- Arrow keys - Rotate the view.
- `Esc` - Close the program.

## Bonus

- Additional features implemented in the bonus section.
- Check the [subject](https://github.com/Javisanchezf/42Malaga-pdfs/blob/main/cub3d_subject.pdf) for details.

## Author

- Names: Javier Sánchez | Antonio Delgado
- 42 Logins: @javiersa | @antdelga

## License

This work is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).

You are free to:
* Share: copy and redistribute the material in any medium or format.
* Adapt: remix, transform, and build upon the material.

Under the following terms:
* Attribution: You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
* NonCommercial: You may not use the material for commercial purposes.
* ShareAlike: If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

<h3 align = right>Share the content!</h3>

[<img src="https://github.com/Javisanchezf/media/blob/main/whatsapp-icon.png" width="50" height="50" align = right></img>](https://api.whatsapp.com/send?text=Hey!%20Check%20out%20this%20cool%20repository%20I%20found%20on%20Github.%20%0ahttps://github.com/Javisanchezf/42Malaga-cub3d)
[<img src="https://github.com/Javisanchezf/media/blob/main/telegram-icon.webp" width="50" height="50" align = right></img>](https://t.me/share/url?url=https://github.com/javisanchezf/42Malaga-cub3d&text=Hey!%20Check%20out%20this%20cool%20repository%20I%20found%20on%20Github.)
[<img src="https://github.com/Javisanchezf/media/blob/main/twitter-icon.png" width="50" height="50" align = right></img>](https://twitter.com/intent/tweet?url=https://github.com/Javisanchezf/42Malaga-cub3d&text=Hey!%20Check%20out%20this%20cool%20repository%20I%20found%20on%20Github)
[<img src="https://github.com/Javisanchezf/media/blob/main/linkedin-icon.png" width="50" height="50" align = right></img>](https://www.linkedin.com/sharing/share-offsite/?url=https://github.com/javisanchezf/42Malaga-cub3d)
