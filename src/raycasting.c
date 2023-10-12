/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:33:28 by antdelga          #+#    #+#             */
/*   Updated: 2023/10/12 14:34:02 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define WIDTH 5120
#define HEIGHT 2880

int	main(void)
{
	// VARIABLES
	int	x = 0;
	double posX = 22, posY = 12;  // Posicion inicial jugador
	double dirX = -1, dirY = 0; // Vector director inicial del jugador, a donde mira
	double planeX = 0, planeY = 0.66; // Plano de la camara, ortogonal al vector del jugador

	double cameraX;
	double rayDirX;
	double rayDirY;

	int	mapX;
	int	mapY;

	// Longitud del rayo en ambas dimensiones
	double sideDistX;
	double sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double perpWallDist;

	// Paso en sentido X y sentido Y
	int stepX;
	int stepY;

	int hit; // Choque con muro
	int side; // Muro de arriba a abajo o de izquerda a derecha?

	int lineHeight; // Altura de la linea vertical que hay que pintar

	int drawStart;
	int drawEnd;

	int worldMap[mapHeight][mapWidth] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	/* LANZAR VENTANA DE MLX*/
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	mlx_image_t* img = mlx_new_image(mlx, screenWidth, screenHeight);

	while (windowOpen) /* MIENTRAS NO CIERRES LA VENTANA */
	{
		while (x < screenWidth)
		{
			cameraX = 2 * x / (double) screenWidth - 1; // Coordenada X en subespacio de camara
			
			// Posicion y direccion del rayo
			rayDirX = dirX + planeX * cameraX;
			rayDirY = dirY + planeY * cameraX;

			//which box of the map we're in
			mapX = (int) posX;
			mapY = (int) posY;

			deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
			deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

			// Para controlar los choques
			hit = 0;
			
			// Calcular el paso
			if(rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if(rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}

			// Algoritmo DDA
			while(hit == 0)
			{
				// jump to next map square, either in x-direction, or in y-direction
				if(sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				// Comprobar choque con el muro
				if(worldMap[mapX][mapY] > 0) hit = 1;
			}
			
			// Distancia proyectada en el subespacio de la camara, menor distancia desde el jugador hasta el muro con el que ha chocado el rayo en el plano de la camara
			if (side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);

			//Calculate height of line to draw on screen
			lineHeight = (int)(screenHeight / perpWallDist);

			// Pixel mas alto y mas bajo que hay que pintar para hacer la linea vertical
			drawStart = -lineHeight / 2 + screenHeight / 2;
			if(drawStart < 0) drawStart = 0;
			drawEnd = lineHeight / 2 + screenHeight / 2;
			if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

			//give x and y sides different brightness
			// if(side == 1) {color = color / 2;}

			// Hay que dibujar una franja vertical completa desde el centro
			verLine(x, drawStart, drawEnd, color);
			
			// Aumenta contador
			x++;
		}
	}
	return (0);
}