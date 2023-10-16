/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:44:13 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/16 18:56:20 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	converttocircle(mlx_image_t *image, int radius)
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

void	ufo_rays(t_cub3data *data, mlx_image_t *img, double angle)
{
	t_coords	p;
	double		i;
	int			t;

	ft_memset(img->pixels, 0, img->width * 4 * img->height);
	i = 175;
	while (i < 185)
	{
		t = 1;
		p.x = img->width / 2 + t * cos(angle + i * PI / 180);
		p.y = img->height / 2 + t * sin(angle + i * PI / 180);
		while (p.x >= 0 && p.y >= 0 && p.x < (int) img->width && p.y < (int) img->height && ++t)
		{
			if (data->minimap->pixels[p.y * img->width * 4 + p.x * 4] != 27 || data->minimap->pixels[p.y * img->width * 4 + p.x * 4 + 3] == 0)
				break ;
			put_rgbcolor(&img->pixels[p.y * img->width * 4 + p.x * 4], data->color.golden, 0);
			p.x = img->width / 2 + t * cos(angle + i * PI / 180);
			p.y = img->height / 2 + t * sin(angle + i * PI / 180);
		}
		i += 0.2;
	}
}

void	locuramap_close(t_cub3data *data)
{
	int	startx;
	int	starty;
	int	start;
	t_coords	p;

	starty = data->player.pos.y - data->minimap->height / 2;
	startx = (data->player.pos.x - data->minimap->width / 2) * 4;
	start = starty * data->map_close.width * 4 + startx;
	p.y = -1;
	while (++p.y < (int)data->minimap->height)
	{
		if (start + p.y * data->map_close.width * 4 > 0 && start + data->map_close.width * 4 * 3 + p.y * data->map_close.width * 4 < data->map_close.height * data->map_close.width * 4)
		{
			p.x = -1;
			while (++p.x < (int)data->minimap->width * 4)
			{
				if (startx + p.x > 0 && startx + p.x < (int)data->map_close.width * 4)
					data->minimap->pixels[p.y * data->minimap->width * 4 + p.x] = data->map_close.img[start + p.y * data->map_close.width * 4 + p.x];
				else if (startx + p.x >= data->map_close.width * 4)
					break ;
			}
		}
		else if (start + data->map_close.width * 4 * 3 + p.y * data->map_close.width * 4 >= data->map_close.height * data->map_close.width * 4)
			break ;
	}
	converttocircle(data->minimap, data->minimap->width / 2);
}

void	draw_minimap(t_cub3data *data)
{
	ft_memset(data->minimap->pixels, 200, data->minimap->width * data->minimap->height * sizeof(int));
	locuramap_close(data);
}
