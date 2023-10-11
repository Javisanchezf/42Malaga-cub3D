/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:12:59 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/11 20:48:06 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_rgb(uint8_t *pixels, t_pixels color)
{
	pixels[0] = color.r;
	pixels[1] = color.g;
	pixels[2] = color.b;
	pixels[3] = color.a;
}

static void	drawsquare(t_cub3data *data, t_coords p, t_pixels color)
{
	int			i;
	int			j;

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
			put_rgb(&(data->minimap.img->pixels[(i * \
			data->minimap.width + j) * 4]), color);
	}
}

// static void	drawcircle(t_cub3data *data, t_coords center, t_pixels color)
// {
// 	int	radius = BLOCKSIZE / 3;
// 	int i = center.y - radius - 2;

// 	while (++i <= center.y + radius)
// 	{
// 		int j = center.x - radius - 1;
// 		while (++j <= center.x + radius)
// 		{
// 			int dx = j - center.x;
// 			int dy = i - center.y;
// 			double distance = sqrt(dx * dx + dy * dy);
// 			if (distance <= radius)
// 			{
// 				int x = j / BLOCKSIZE;
// 				int y = i / BLOCKSIZE;
// 				if (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height)
// 					put_rgb(&(data->minimap.img->pixels[(i * data->minimap.width + j) * 4]), color);
// 			}
// 		}
//     }
// }

static void	draw_minimap(t_cub3data	*data)
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
			else if (data->map[p.y][p.x] == '0' || \
data->map[p.y][p.x] == 'N' || data->map[p.y][p.x] == 'S' || \
data->map[p.y][p.x] == 'W' || data->map[p.y][p.x] == 'E')
				drawsquare(data, p, data->color.blue);
		}
	}
	// drawcircle(data, data->player.pos, data->color.golden);
}

void	minimap(t_cub3data	*data)
{
	ft_memset(data->minimap.img->pixels, 200, data->minimap.width * data->minimap.height * sizeof(int));
	draw_minimap(data);
	// if (mlx_image_to_window(data->mlx, data->minimap.img, 0, 0) == -1)
	// {
	// 	mlx_close_window(data->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	cleaner(data);
	// 	exit(EXIT_FAILURE);
	// }
	draw_minimapfixed(data);
}
