/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimapfixed.c                                     :+:      :+:    :+:   */
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

void	ufo_rays(t_cub3data *data, mlx_image_t *img, double angle, t_pixels color)
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
			if (data->minimapfixed->pixels[p.y * img->width * 4 + p.x * 4] != 27 || data->minimapfixed->pixels[p.y * img->width * 4 + p.x * 4 + 3] == 0)
				break ;
			img->pixels[p.y * img->width * 4 + p.x * 4 + 0] = color.r;
			img->pixels[p.y * img->width * 4 + p.x * 4 + 1] = color.g;
			img->pixels[p.y * img->width * 4 + p.x * 4 + 2] = color.b;
			img->pixels[p.y * img->width * 4 + p.x * 4 + 3] = color.a;
			p.x = img->width / 2 + t * cos(angle + i * PI / 180);
			p.y = img->height / 2 + t * sin(angle + i * PI / 180);
		}
		i += 0.2;
	}
}

void	locuraminimap(t_cub3data *data)
{
	int	startx;
	int	starty;
	int	start;
	t_coords	p;

	starty = data->player.pos.y - data->minimapfixed->height / 2;
	startx = (data->player.pos.x - data->minimapfixed->width / 2) * 4;
	start = starty * data->minimap.width * 4 + startx;
	p.y = -1;
	while (++p.y < (int)data->minimapfixed->height)
	{
		if (start + p.y * data->minimap.width * 4 > 0 && start + data->minimap.width * 4 * 3 + p.y * data->minimap.width * 4 < data->minimap.height * data->minimap.width * 4)
		{
			p.x = -1;
			while (++p.x < (int)data->minimapfixed->width * 4)
			{
				if (startx + p.x > 0 && startx + p.x < (int)data->minimap.width * 4)
					data->minimapfixed->pixels[p.y * data->minimapfixed->width * 4 + p.x] = data->minimap.img[start + p.y * data->minimap.width * 4 + p.x];
				else if (startx + p.x >= data->minimap.width * 4)
					break ;
			}
		}
		else if (start + data->minimap.width * 4 * 3 + p.y * data->minimap.width * 4 >= data->minimap.height * data->minimap.width * 4)
			break ;
	}
	converttocircle(data->minimapfixed, data->minimapfixed->width / 2);
}

void	draw_minimapfixed(t_cub3data *data)
{
	ft_memset(data->minimapfixed->pixels, 200, data->minimapfixed->width * data->minimapfixed->height * sizeof(int));
	locuraminimap(data);
}
