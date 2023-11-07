/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:35:13 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/26 12:04:48 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_convert_to_circle(mlx_image_t *image, int radius)
{
	t_coords	center;
	t_coords	index;
	int			distance;
	int			pixelindex;

	center.x = image->width / 2;
	center.y = image->height / 2;
	index.y = -1;
	while (++index.y < (int) image->height)
	{
		index.x = -1;
		while (++index.x < (int) image->width)
		{
			distance = (index.x - center.x) * (index.x - \
center.x) + (index.y - center.y) * (index.y - center.y);
			pixelindex = (index.y * image->width + index.x) * 4;
			if (distance > radius * radius)
				image->pixels[pixelindex + 3] = 0;
		}
	}
}

static void	ft_crop_minimap(t_cub3data *data, int startx, int start)
{
	t_coords	p;

	p.y = -1;
	while (++p.y < (int)data->minimap->height)
	{
		if (start + p.y * data->map_close.width * 4 > 0 && start + \
data->map_close.width * 4 * 3 + p.y * data->map_close.width * 4 < \
data->map_close.height * data->map_close.width * 4)
		{
			p.x = -1;
			while (++p.x < (int)data->minimap->width * 4)
			{
				if (startx + p.x > 0 && startx + p.x < \
				(int)data->map_close.width * 4)
					data->minimap->pixels[p.y * data->minimap->width * \
4 + p.x] = data->map_close.img[start + p.y * data->map_close.width * 4 + p.x];
				else if (startx + p.x >= data->map_close.width * 4)
					break ;
			}
		}
		else if (start + data->map_close.width * 4 * 3 + p.y * \
data->map_close.width * 4 >= data->map_close.height * data->map_close.width * 4)
			break ;
	}
	ft_convert_to_circle(data->minimap, data->minimap->width / 2);
}

void	ft_draw_minimap(t_cub3data *data)
{
	int			startx;
	int			starty;
	int			start;

	ft_memset(data->minimap->pixels, 200, data->minimap->width * \
	data->minimap->height * sizeof(int));
	starty = (data->player.pos.y - data->minimap->height / 2);
	startx = (data->player.pos.x - data->minimap->width / 2) * 4;
	start = starty * data->map_close.width * 4 + startx;
	ft_crop_minimap(data, startx, start);
}
