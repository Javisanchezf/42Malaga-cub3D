/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:40:45 by antdelga          #+#    #+#             */
/*   Updated: 2023/10/26 21:44:30 by antdelga         ###   ########.fr       */
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
	double		cos;
	double		sin;
	int			niidea;
}		t_aux;

void	picasso(double t, int col, t_cub3data *data, t_pixels color)
{
	int			i;
	t_coords	p;

	i = -1;
	col *= 2;
	t = (HEIGHT / (t / BLOCKSIZE));
	t = (HEIGHT - t) / 2;
	while (++i < HEIGHT - 1)
	{
		if (i < t)
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.ceiling, 0);
		else if (i < HEIGHT - t)
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), color, 1);
		else
			put_rgbcolor(&(data->full_img->pixels[(i * WIDTH + col) * 4]), data->color.floor, 0);
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

	aux.iter = 0;
	while (aux.iter <= ANGLE)
	{
		aux.dist = 1;
		aux.correction = cos((aux.iter + 180 - (ANGLE / 2)) * PI / 180);
		aux.cos = cos(data->player.angle + (aux.iter - (ANGLE / 2)) * PI / 180);
		aux.sin = sin(data->player.angle + (aux.iter - (ANGLE / 2)) * PI / 180);
		aux.p.x = pos.x + (aux.dist * aux.cos) / aux.correction;
		aux.p.y = pos.y + (aux.dist * aux.sin) / aux.correction;
		while (aux.p.x >= 0 && aux.p.y >= 0 && aux.p.x < WIDTH * BLOCKSIZE && \
		aux.p.y < HEIGHT * BLOCKSIZE && ++aux.dist)
		{
			aux.iswall = ft_iswall(aux.p, data);
			if ((aux.iswall == 2 && data->door_open == 0) || aux.iswall == 1)
				break ;
			aux.p.x = pos.x + (aux.dist * aux.cos) / aux.correction;
			aux.p.y = pos.y + (aux.dist * aux.sin) / aux.correction;
		}
		aux.niidea = (aux.p.y * data->width * BLOCKSIZE + aux.p.x) * 4;
		if (data->map_close.img[aux.niidea] == 254 && ((data->map_close.img[aux.niidea + 8 * 4 * data->width * BLOCKSIZE] != 252) || (data->map_close.img[aux.niidea - 8 * 4 * data->width * BLOCKSIZE] != 252)) && ((data->map_close.img[aux.niidea + 8 * 4 * data->width * BLOCKSIZE] != 251) || (data->map_close.img[aux.niidea - 8 * 4 * data->width * BLOCKSIZE] != 251)))
			picasso(aux.dist, aux.iter * (WIDTH / (ANGLE * SAMPLE)), data, data->color.red);
		else if (data->map_close.img[aux.niidea] == 253 && ((data->map_close.img[aux.niidea + 8 * 4 * data->width * BLOCKSIZE] != 252) || (data->map_close.img[aux.niidea - 8 * 4 * data->width * BLOCKSIZE] != 252)) && ((data->map_close.img[aux.niidea + 8 * 4 * data->width * BLOCKSIZE] != 251) || (data->map_close.img[aux.niidea - 8 * 4 * data->width * BLOCKSIZE] != 251)))
			picasso(aux.dist, aux.iter * (WIDTH / (ANGLE * SAMPLE)), data, data->color.golden);
		else if (data->map_close.img[aux.niidea] == 252 || ((data->map_close.img[aux.niidea] == 254 || data->map_close.img[aux.niidea] == 253) && ((data->map_close.img[aux.niidea + 8 * 4 * data->width * BLOCKSIZE] == 252) || (data->map_close.img[aux.niidea - 8 * 4 * data->width * BLOCKSIZE] == 252))))
			picasso(aux.dist, aux.iter * (WIDTH / (ANGLE * SAMPLE)), data, data->color.blue);
		else if (data->map_close.img[aux.niidea] == 251 || ((data->map_close.img[aux.niidea] == 254 || data->map_close.img[aux.niidea] == 253) && ((data->map_close.img[aux.niidea + 8 * 4 * data->width * BLOCKSIZE] == 251) || (data->map_close.img[aux.niidea - 8 * 4 * data->width * BLOCKSIZE] == 251))))
			picasso(aux.dist, aux.iter * (WIDTH / (ANGLE * SAMPLE)), data, data->color.green);
		else
			picasso(aux.dist, aux.iter * (WIDTH / (ANGLE * SAMPLE)), data, data->color.white);
		aux.iter += (1.0 / (WIDTH / (ANGLE * SAMPLE)));
	}
}

/*  WIDTH = ANGLE * SAMPLE * X
 ITER+ * X = 1 */
