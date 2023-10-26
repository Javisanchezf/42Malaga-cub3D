/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:12:59 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/26 11:41:36 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	drawsquare(t_cub3data *data, t_coords p, t_pixels color)
{
	int	i;
	int	j;

	p.x *= BLOCKSIZE;
	p.y *= BLOCKSIZE;
	if (p.x < 0)
		p.x = 0;
	if (p.y < 0)
		p.y = 0;
	if (p.x + BLOCKSIZE > data->map_close.width)
		p.x = data->map_close.width - BLOCKSIZE;
	if (p.y + BLOCKSIZE > data->map_close.height)
		p.y = data->map_close.height - BLOCKSIZE;
	i = p.y - 1;
	while (++i < p.y + BLOCKSIZE)
	{
		j = p.x - 1;
		while (++j < p.x + BLOCKSIZE)
			put_rgbcolor(&(data->map_close.img[(i * \
		data->map_close.width + j) * 4]), color, 1);
	}
}

static void	drawchest(t_cub3data *data, t_coords p)
{
	t_coords	i;

	drawsquare(data, p, data->color.blue);
	p.x = p.x * BLOCKSIZE - 1 + (BLOCKSIZE / 2 - data->chest_i->width / 2);
	p.y = p.y * BLOCKSIZE - 1 + (BLOCKSIZE / 2 - data->chest_i->width / 2);
	i.y = -1;
	while (++i.y < (int)data->chest_i->width)
	{
		i.x = -1;
		while (++i.x < (int)data->chest_i->width)
		{
			if (data->chest_i->pixels[(i.y * \
			data->chest_i->width + i.x) * 4 + 3] > 60)
			{
				put_rgbimg(&data->map_close.img[((p.y + i.y) * \
data->map_close.width + p.x + i.x) * 4], &data->chest_i->pixels[(i.y * \
data->chest_i->width + i.x) * 4]);
			}
		}
	}
}

static void	draw_map(t_cub3data *data)
{
	t_coords	p;

	p.y = -1;
	while (data->map[++p.y])
	{
		p.x = -1;
		while (data->map[p.y][++p.x])
		{
			if (data->map[p.y][p.x] == '1')
				drawsquare(data, p, data->color.white);
			else if (data->map[p.y][p.x] == '0' ||
data->map[p.y][p.x] == 'N' || data->map[p.y][p.x] == 'S' ||
data->map[p.y][p.x] == 'W' || data->map[p.y][p.x] == 'E')
				drawsquare(data, p, data->color.blue);
			else if (data->map[p.y][p.x] == 'F')
				drawchest(data, p);
			else if (data->map[p.y][p.x] == '2')
				drawsquare(data, p, data->color.red);
		}
	}
}

void	map_construct(t_cub3data *data)
{
	int	i;

	ft_memset(data->map_close.img, 200, data->map_close.width * \
	data->map_close.height * sizeof(int));
	draw_map(data);
	i = 0;
	while (i < data->map_close.height * data->map_close.rwidth)
	{
		if (data->map_close.img[i] != 104)
		{
			data->map_open.img[i] = data->map_close.img[i];
			data->map_open.img[i + 1] = data->map_close.img[i + 1];
			data->map_open.img[i + 2] = data->map_close.img[i + 2];
			data->map_open.img[i + 3] = data->map_close.img[i + 3];
		}
		else
			put_rgbcolor(&data->map_open.img[i], data->color.green, 1);
		i += 4;
	}
	ft_draw_minimap(data);
	ft_draw_ufo_rays(data, data->player.ray_img, data->player.angle);
	raycasting(data, data->player.pos);
}
