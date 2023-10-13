/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimapfixed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:44:13 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/13 11:45:40 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	converttocircle(t_img *image, int radius)
{
	t_coords	center;
	t_coords	index;
	int			distance;
	int			pixelindex;

	center.x = image->width / 2;
	center.y = image->height / 2;
	index.y = -1;
	while (++index.y < image->height)
	{
		index.x = -1;
		while (++index.x < image->width)
		{
			distance = (index.x - center.x) * (index.x - \
center.x) + (index.y - center.y) * (index.y - center.y);
			pixelindex = (index.y * image->width + index.x) * 4;
			if (distance > radius * radius)
				image->img->pixels[pixelindex + 3] = 0;
			// else
			// 	image->img->pixels[pixelindex + 3] = 255;
		}
	}
}

void	locuraminimap(t_cub3data *data)
{
	int	startx;
	int	starty;
	int	start;
	t_coords	p;

	starty = data->player.pos.y - data->minimapfixed.height / 2;
	startx = (data->player.pos.x - data->minimapfixed.width / 2) * 4;
	start = starty * data->minimap.rwidth + startx;
	p.y = -1;
	while (++p.y < data->minimapfixed.height)
	{
		if (start + p.y * data->minimap.rwidth > 0 && start + data->minimap.rwidth * 3 + p.y * data->minimap.rwidth < data->minimap.height * data->minimap.rwidth)
		{
			p.x = -1;
			while (++p.x < data->minimapfixed.rwidth)
			{
				if (startx + p.x > 0 && startx + p.x < data->minimap.rwidth)
					data->minimapfixed.img->pixels[p.y * data->minimapfixed.rwidth + p.x] = data->minimap.img[start + p.y * data->minimap.rwidth + p.x];
				else if (startx + p.x >= data->minimap.rwidth)
					break ;
			}
		}
		else if (start + data->minimap.rwidth * 3 + p.y * data->minimap.rwidth >= data->minimap.height * data->minimap.rwidth)
			break ;
	}
	converttocircle(&data->minimapfixed, data->minimapfixed.img->width / 2);
}

void	draw_minimapfixed(t_cub3data *data)
{
	ft_memset(data->minimapfixed.img->pixels, 200, data->minimapfixed.width * data->minimapfixed.height * sizeof(int));
	// if (mlx_image_to_window(data->mlx, data->minimapfixed.img, WIDTH - MINIMAP_WIDTH, 0) == -1)
	// {
	// 	mlx_close_window(data->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	cleaner(data);
	// 	exit(EXIT_FAILURE);
	// }
	locuraminimap(data);
	// if (mlx_image_to_window(data->mlx, data->player.img.img, WIDTH - MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2) == -1)
	// {
	// 	mlx_close_window(data->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	cleaner(data);
	// 	exit(EXIT_FAILURE);
	// }
	// converttocircle(&data->player.img, data->player.img.width / 2);
}
