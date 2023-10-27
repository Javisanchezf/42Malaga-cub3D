/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:40:45 by antdelga          #+#    #+#             */
/*   Updated: 2023/10/27 17:21:22 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	picasso(double t, int col, t_cub3data *data, t_pixels color)
{
	int			i;

	t = (HEIGHT / (t / BLOCKSIZE));
	t = (HEIGHT - t) / 2;
	i = -1;
	while (++i < HEIGHT - 1)
	{
		if (i < t)
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.ceiling, 0);
		else if (i < HEIGHT - t)
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), color, 0);
		else
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.floor, 0);
		put_rgbimg(&data->full_img->pixels[(i * WIDTH + col + 1) * 4], &data->full_img->pixels[(i * WIDTH + col) * 4]);
	}
}

static void	ft_wall_direction(t_cub3data *data, t_coords p, int dist, double iter)
{
	int	rest_y;
	int rest_x;
	int	aux;

	if (ft_iswall(p, data) == 2)
	{
		picasso(dist, iter * (WIDTH / ANGLE), data, data->color.white); // DOORS
		return ;
	}
	aux = (p.y * data->width * BLOCKSIZE + p.x) * 4;
	rest_x = p.x % BLOCKSIZE;
	rest_y = p.y % BLOCKSIZE;
	if (rest_x <= 2 && data->map_close.img[aux - 2 * 4] != 255)
		picasso(dist, iter * (WIDTH / ANGLE), data, data->color.red); //EAST?
	else if (rest_x >= BLOCKSIZE - 2 && data->map_close.img[aux + 2 * 4] != 255)
		picasso(dist, iter * (WIDTH / ANGLE), data, data->color.golden); //WEST?
	else if (rest_y <= 2)
		picasso(dist, iter * (WIDTH / ANGLE), data, data->color.blue); //SOUTH
	else if (rest_y >= BLOCKSIZE - 2)
		picasso(dist, iter * (WIDTH / ANGLE), data, data->color.green); //NORTH
}

static int	ft_take_dist(t_cub3data *data, double iter, t_coords *p)
{
	int			dist;
	double		fix;
	double		cos_c;
	double		sin_c;
	int			iswall;

	dist = 1;
	fix = cos((iter + 180 - (ANGLE / 2)) * TORADIANS);
	cos_c = (cos(data->player.angle + (iter - (ANGLE / 2)) * TORADIANS)) / fix;
	sin_c = (sin(data->player.angle + (iter - (ANGLE / 2)) * TORADIANS)) / fix;
	p->x = data->player.pos.x + dist * cos_c;
	p->y = data->player.pos.y + dist * sin_c;
	while (p->x >= 0 && p->y >= 0 && p->x < WIDTH * BLOCKSIZE && \
	p->y < HEIGHT * BLOCKSIZE && ++dist)
	{
		iswall = ft_iswall(*p, data);
		if ((iswall == 2 && data->door_open == 0) || iswall == 1)
			break ;
		p->x = data->player.pos.x + dist * cos_c;
		p->y = data->player.pos.y + dist * sin_c;
	}
	return (dist);
}

void	raycasting(t_cub3data *data, t_coords pos)
{
	static const double	iter_variation = 1.0 / (WIDTH / ANGLE);
	double				iter;
	int					dist;

	iter = 0;
	while (iter <= ANGLE)
	{
		dist = ft_take_dist(data, iter, &pos);
		ft_wall_direction(data, pos, dist, iter); //Esta se puede hacer que sea tipo img y que devuelva la textura correspondiente para llamar luego a la que pinta con la textura
		iter += iter_variation;
	}
}
