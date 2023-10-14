/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:12:59 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/14 12:54:05 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	put_rgb(uint8_t *pixels, t_pixels color)
{
	pixels[0] = color.r;
	pixels[1] = color.g;
	pixels[2] = color.b;
	pixels[3] = rand() % 106 + 150;
}

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
	if (p.x + BLOCKSIZE > data->minimap.width)
		p.x = data->minimap.width - BLOCKSIZE;
	if (p.y + BLOCKSIZE > data->minimap.height)
		p.y = data->minimap.height - BLOCKSIZE;
	i = p.y - 1;
	while (++i < p.y + BLOCKSIZE)
	{
		j = p.x - 1;
		while (++j < p.x + BLOCKSIZE)
			put_rgb(&(data->minimap.img[(i * \
		data->minimap.width + j) * 4]), color);
	}
}

static void	drawchest(t_cub3data *data, t_coords p)
{
	t_coords	i;

	drawsquare(data, p, data->color.blue);
	p.x = p.x * BLOCKSIZE - 1 + (BLOCKSIZE / 2 - CHEST_SIZE / 2);
	p.y = p.y * BLOCKSIZE - 1 + (BLOCKSIZE / 2 - CHEST_SIZE / 2);
	i.y = -1;
	while (++i.y < CHEST_SIZE)
	{
		i.x = -1;
		while (++i.x < CHEST_SIZE)
		{
			if (data->chest_i->pixels[(i.y * CHEST_SIZE + i.x) * 4 + 3] != 0)
			{
				data->minimap.img[((p.y + i.y) * data->minimap.width + p.x + i.x) * 4] = data->chest_i->pixels[(i.y * CHEST_SIZE + i.x) * 4];
				data->minimap.img[((p.y + i.y) * data->minimap.width + p.x + i.x) * 4 + 1] = data->chest_i->pixels[(i.y * CHEST_SIZE + i.x) * 4 + 1];
				data->minimap.img[((p.y + i.y) * data->minimap.width + p.x + i.x) * 4 + 2] = data->chest_i->pixels[(i.y * CHEST_SIZE + i.x) * 4 + 2];
				data->minimap.img[((p.y + i.y) * data->minimap.width + p.x + i.x) * 4 + 3] = data->chest_i->pixels[(i.y * CHEST_SIZE + i.x) * 4 + 3];
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
			else if (data->map[p.y][p.x] == '0' || data->map[p.y][p.x] == '2' ||
data->map[p.y][p.x] == 'N' || data->map[p.y][p.x] == 'S'
|| data->map[p.y][p.x] == 'W' || data->map[p.y][p.x] == 'E')
				drawsquare(data, p, data->color.blue);
			else if (data->map[p.y][p.x] == 'F')
				drawchest(data, p);
		}
	}
}

void	map_construct(t_cub3data *data)
{
	ft_memset(data->minimap.img, 200, data->minimap.width * \
	data->minimap.height * sizeof(int));
	draw_map(data);
	draw_minimapfixed(data);
	ufo_rays(data, &data->player.ray_img, data->player.orientation, data->color.golden);
}
