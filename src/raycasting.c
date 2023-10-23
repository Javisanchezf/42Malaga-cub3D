/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:40:45 by antdelga          #+#    #+#             */
/*   Updated: 2023/10/23 22:31:36 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_aux
{
	t_coords	p;
	double		iter;
	double		dist;
	int			iswall;
	double		correction;
	double		cos_calc;
	double		sin_calc;
}		t_aux;

void	picasso(double t, int col, t_cub3data *data)
{
	int			i;
	t_coords	p;

	i = -1;
	col *= 2;
	t = (HEIGHT / pow(2, (t / (BLOCKSIZE)) - 1));
	t = (HEIGHT - t) / 2;
	while (++i < HEIGHT - 1)
	{
		if (i < t)
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.ceiling, 1);
		else if (i < HEIGHT - t)
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.golden, 1);
		else
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.floor, 1);
	}
	p.y = 0;
	while (++p.y < SAMPLE)
	{
		p.x = -1;
		while (++p.x < HEIGHT - 1)
			put_rgbimg(&data->full_img->pixels[(p.x * data->full_img->width + col + p.y) * 4], &data->full_img->pixels[(p.x * data->full_img->width + col) * 4]);
	}
}

void	raycasting(t_cub3data *data, t_coords pos)
{
	t_aux	aux;

	pos.x = pos.x + ((PLAYER_SIZE / 2) * cos(data->player.orientation));
	pos.y = pos.y + ((PLAYER_SIZE / 2) * sin(data->player.orientation));
	aux.iter = 0;
	while (aux.iter <= ANGLE)
	{
		aux.dist = 0;
		aux.correction = cos((aux.iter + 180 - (ANGLE / 2)) * PI / 180);
		aux.cos_calc = cos(data->player.orientation + (aux.iter - (ANGLE / 2)) * PI / 180);
		aux.sin_calc = sin(data->player.orientation + (aux.iter - (ANGLE / 2)) * PI / 180);
		aux.p.x = pos.x + (aux.dist * aux.cos_calc) / aux.correction;
		aux.p.y = pos.y + (aux.dist * aux.sin_calc) / aux.correction;
		while (aux.p.x >= 0 && aux.p.y >= 0 && aux.p.x < WIDTH * BLOCKSIZE && aux.p.y < HEIGHT * BLOCKSIZE && ++aux.dist)
		{
			aux.iswall = ft_iswall(aux.p, data);
			if ((aux.iswall == 2 && data->door_open == 0) || aux.iswall == 1)
				break;
			aux.p.x = pos.x + (aux.dist * aux.cos_calc) / aux.correction;
			aux.p.y = pos.y + (aux.dist * aux.sin_calc) / aux.correction;
		}
		picasso(aux.dist, aux.iter * (WIDTH / (ANGLE * SAMPLE)), data);
		aux.iter += (1.0 / (WIDTH / (ANGLE * SAMPLE)));
	}
} 

/*  WIDTH = ANGLE * SAMPLE * X
 ITER+ * X = 1 */
