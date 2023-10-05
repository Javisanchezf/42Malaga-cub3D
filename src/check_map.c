/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:34:03 by antdelga          #+#    #+#             */
/*   Updated: 2023/10/05 18:45:49 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void imprimirArray2D(char **array, int filas, int columnas) 
{
	printf("\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c", array[i][j]);
        }
        printf("\n");
    }
	printf("\n");
}

int	check_enviroment(t_cub3data data, int i, int j)
{
	int	i1;
	int	j1;

	i1 = i;
	j1 = j;

	// ARRIBA
	while (--i >= 0)
	{
		if (!(data.map[i][j] == ' '))
		{
			if (data.map[i][j] == '1')
			{
				data.map[i][j] = 'X';
				imprimirArray2D(data.map, data.map_height, data.map_width);
				data.map[i][j] = '1';
				break ;
			}
			else
				{
					imprimirArray2D(data.map, data.map_height, data.map_width);
					printf("ERROR EN LA CASILLA %d, %d\n", i, j);
					return (1);
				}
		}
		data.map[i][j] = 'X';
		imprimirArray2D(data.map, data.map_height, data.map_width);
		data.map[i][j] = ' ';
	}

	printf("ABAJO\n");
	i = i1;
	while (++i < data.map_height)
	{
		if (!(data.map[i][j] == ' '))
		{
			if (data.map[i][j] == '1')
			{
				data.map[i][j] = 'X';
				imprimirArray2D(data.map, data.map_height, data.map_width);
				data.map[i][j] = '1';
				break ;
			}
			else
				{
					imprimirArray2D(data.map, data.map_height, data.map_width);
					printf("ERROR EN LA CASILLA %d, %d\n", i, j);
					return (1);
				}
		}
		data.map[i][j] = 'X';
		imprimirArray2D(data.map, data.map_height, data.map_width);
		data.map[i][j] = ' ';
	}

	i = i1;
	printf("IZQUIERDA\n");
	while (--j >= 0)
	{
		if (!(data.map[i][j] == ' '))
		{
			if (data.map[i][j] == '1')
			{
				data.map[i][j] = 'X';
				imprimirArray2D(data.map, data.map_height, data.map_width);
				data.map[i][j] = '1';
				break ;
			}
			else
				{
					imprimirArray2D(data.map, data.map_height, data.map_width);
					printf("ERROR EN LA CASILLA %d, %d\n", i, j);
					return (1);
				}
		}
		data.map[i][j] = 'X';
		imprimirArray2D(data.map, data.map_height, data.map_width);
		data.map[i][j] = ' ';
	}

	j = j1;
	printf("DERECHA\n");
	while (++j < (data.map_width))
	{
		if (!(data.map[i][j] == ' '))
		{
			if (data.map[i][j] == '1')
			{
				data.map[i][j] = 'X';
				imprimirArray2D(data.map, data.map_height, data.map_width);
				data.map[i][j] = '1';
				break ;
			}
			else
				{
					imprimirArray2D(data.map, data.map_height, data.map_width);
					printf("ERROR EN LA CASILLA %d, %d\n", i, j);
					return (1);
				}
		}
		data.map[i][j] = 'X';
		imprimirArray2D(data.map, data.map_height, data.map_width);
		data.map[i][j] = ' ';
	}
	return (0);
}

int ft_check_wall(t_cub3data data)
{
	int	i;
	int	j;
	int	error;

	i = -1;
	j = -1;
	error = 0;

	while (++i < data.map_height && !error)
	{
		while (++j < data.map_width && !error)
		{
			if (data.map[i][j] == ' ')
				error = check_enviroment(data, i, j);
		}
		j = -1;
	}
	if (error)
		printf("MAPA INVALIDO\n");
	else
		printf("MAPA CORRECTO\n");
	return (1);
}
