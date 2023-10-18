/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:40:45 by antdelga          #+#    #+#             */
/*   Updated: 2023/10/18 21:57:42 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	picasso(int t, int col, t_cub3data *data)
{
	int			i;
	t_coords	p;

	i = -1;
	col *= 2;
	// t = t / cos

	// ft_printf("%d\n", t % BLOCKSIZE);
	// t = (HEIGHT / (pow(2, (t / BLOCKSIZE)))) + (HEIGHT * (t % BLOCKSIZE) / BLOCKSIZE);
	t = (HEIGHT / (pow(2, (t / BLOCKSIZE)) - 1));
	// t = t - ((((pow(2, ((t) / BLOCKSIZE)) - 1)) - ((pow(2, ((t + BLOCKSIZE) / BLOCKSIZE)) - 1))) * (t % BLOCKSIZE)) / BLOCKSIZE;
	t = (HEIGHT - t) / 2;
	while (++i < HEIGHT - 1)
	{
		if (i < t)
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.blue, 1);
		else if (i < HEIGHT - t)
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.white, 0);
		else
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.green, 1);
	}
	p.y = 0;
	while (++p.y < 2)
	{
		p.x = -1;
		while (++p.x < HEIGHT - 1)
			put_rgbimg(&data->full_img->pixels[(p.x * data->full_img->width + col + p.y) * 4], &data->full_img->pixels[(p.x * data->full_img->width + col) * 4]);
	}
}

void	raycasting(t_cub3data *data, t_coords pos)
{
	t_coords	p;
	double		iter;
	double		t;
	int			iswall;

	iter = 0;
	pos.x = pos.x + PLAYER_SIZE / 2 * cos(data->player.orientation);
	pos.y = pos.y + PLAYER_SIZE / 2 * sin(data->player.orientation);
	while (iter <= 66.01)
	{
		t = 0;
		p.x = pos.x + (t * cos(data->player.orientation + (iter + 147) * PI / 180)) / cos((iter - 33)	* PI / 180);
		p.y = pos.y + (t * sin(data->player.orientation + (iter + 147) * PI / 180)) / cos((iter - 33)	* PI / 180);
		while (p.x >= 0 && p.y >= 0 && p.x < WIDTH * BLOCKSIZE && p.y < HEIGHT * BLOCKSIZE && ++t)
		{
			iswall = ft_iswall(p, data);
			if ((iswall == 2 && data->door_open == 0) || iswall == 1)
				break;
			p.x = pos.x + (t * cos(data->player.orientation + (iter + 147) * PI / 180)) / cos((iter - 33)	* PI / 180);
			p.y = pos.y + (t * sin(data->player.orientation + (iter + 147) * PI / 180)) / cos((iter - 33)	* PI / 180);
		}
		picasso(t, (int)round(iter * 14), data);
		iter += 0.0714285714285714;
	}
}