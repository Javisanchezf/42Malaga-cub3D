/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:12:59 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/11 11:32:09 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_rgb(uint8_t *pixels, t_pixels color)
{
	pixels[0] = color.r;
	pixels[1] = color.g;
	pixels[2] = color.b;
	pixels[3] = color.a;
}

void	drawsquare(t_cub3data *data, t_coords p, t_pixels color)
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
			put_rgb(&(data->minimap.img->pixels[(i * data->minimap.width + j) * 4]), color);
	}
}

void	drawcircle(t_cub3data *data, t_coords center, t_pixels color)
{
	int	radius = BLOCKSIZE / 3;
	int i = center.y - radius - 2;

	while (++i <= center.y + radius)
	{
		int j = center.x - radius - 1;
		while (++j <= center.x + radius)
		{
			int dx = j - center.x;
			int dy = i - center.y;
			double distance = sqrt(dx * dx + dy * dy);
			if (distance <= radius)
			{
				int x = j / BLOCKSIZE;
				int y = i / BLOCKSIZE;
				if (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height)
					put_rgb(&(data->minimap.img->pixels[(i * data->minimap.width + j) * 4]), color);
			}
		}
    }
}

void	draw_minimap(t_cub3data	*data)
{
	t_coords	p;

	p.y = -1;
	while (data->map[++p.y])
	{
		p.x = -1;
		while (data->map[p.y][++p.x])
		{
			if (data->map[p.y][p.x] == '1')
				drawsquare(data, p, data->color1);
			else if (data->map[p.y][p.x] == '0' || data->map[p.y][p.x] == 'N' \
|| data->map[p.y][p.x] == 'S' || data->map[p.y][p.x] == 'W' || data->map[p.y][p.x] == 'E')
				drawsquare(data, p, data->color2);
		}
	}
	drawcircle(data, data->player_pos, data->color3);
}

void convertToCircle(t_img *image, int radius)
{
	int centerX = image->width / 2;
	int centerY = image->height / 2;

	for (int y = 0; y < image->height; y++)
	{
		for (int x = 0; x < image->width; x++)
		{
			int distance = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
			int pixelIndex = (y * image->width + x) * 4;
			if (distance > radius * radius)
				image->img->pixels[pixelIndex + 3] = 0;
			else
				image->img->pixels[pixelIndex + 3] = 255;
		}
	}
}

void	locuraminimap(t_cub3data *data)
{
	int	startx;
	int	starty;
	int	start;
	t_coords	p;

	starty = data->player_pos.y - data->minimapfixed.height / 2;
	startx = (data->player_pos.x - data->minimapfixed.width / 2) * 4;
	start = starty * data->minimap.rwidth + startx;
	p.y = -1;
	while (++p.y < data->minimapfixed.height)
	{
		if (start + p.y * data->minimap.rwidth > 0 && start + data->minimap.rwidth * 2 + p.y * data->minimap.rwidth < data->minimap.height * data->minimap.rwidth)
		{
			p.x = -1;
			while (++p.x < data->minimapfixed.rwidth)
			{
				if (startx + p.x > 0 && startx + p.x < data->minimap.rwidth)
					data->minimapfixed.img->pixels[p.y * data->minimapfixed.rwidth + p.x] = data->minimap.img->pixels[start + p.y * data->minimap.rwidth + p.x];
				else if (startx + p.x >= data->minimap.rwidth)
					break ;
			}
		}
		else if (start + data->minimap.rwidth * 2 + p.y * data->minimap.rwidth >= data->minimap.height * data->minimap.rwidth)
			break ;
	}
	convertToCircle(&data->minimapfixed, data->minimapfixed.img->width / 2);
}

void	draw_minimapfixed(t_cub3data *data)
{
	data->minimapfixed.width = MINIMAP_WIDTH;
	data->minimapfixed.rwidth = MINIMAP_WIDTH * 4;
	data->minimapfixed.height =  MINIMAP_HEIGHT;
	data->minimapfixed.img = mlx_new_image(data->mlx, data->minimapfixed.width, data->minimapfixed.height);
	if (!data->minimapfixed.img)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}
	ft_memset(data->minimapfixed.img->pixels, 200, data->minimapfixed.width * data->minimapfixed.height * sizeof(int));
	if (mlx_image_to_window(data->mlx, data->minimapfixed.img, WIDTH - MINIMAP_WIDTH, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}
	locuraminimap(data);
}

void	minimap(t_cub3data	*data)
{
	data->minimap.width = data->map_width * BLOCKSIZE;
	data->minimap.rwidth = data->map_width * BLOCKSIZE * 4;
	data->minimap.height = data->map_height * BLOCKSIZE;
	data->minimap.img = mlx_new_image(data->mlx, data->minimap.width, data->minimap.height);
	if (!data->minimap.img)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}
	ft_memset(data->minimap.img->pixels, 200, data->minimap.width * data->minimap.height * sizeof(int));
	draw_minimap(data);
	if (mlx_image_to_window(data->mlx, data->minimap.img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}
	
	draw_minimapfixed(data);
}
