/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:46:49 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/12 16:18:59 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	img_failure(t_cub3data *data)
{
	mlx_close_window(data->mlx);
	puts(mlx_strerror(mlx_errno));
	cleaner(data);
	exit(EXIT_FAILURE);
}

void	init_images(t_cub3data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D 42", true);
	if (!data->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}
	data->minimap.width = data->map_width * BLOCKSIZE;
	data->minimap.rwidth = data->map_width * BLOCKSIZE * 4;
	data->minimap.height = data->map_height * BLOCKSIZE;
	data->minimap.img = mlx_new_image(data->mlx, data->minimap.width, data->minimap.height);
	if (!data->minimap.img)
		img_failure(data);
	data->minimapfixed.width = MINIMAP_WIDTH;
	data->minimapfixed.rwidth = MINIMAP_WIDTH * 4;
	data->minimapfixed.height =  MINIMAP_HEIGHT;
	data->minimapfixed.img = mlx_new_image(data->mlx, data->minimapfixed.width, data->minimapfixed.height);
	if (!data->minimapfixed.img)
		img_failure(data);
	data->player.img.width = PLAYER_SIZE;
	data->player.img.rwidth = PLAYER_SIZE * 4;
	data->player.img.height =  PLAYER_SIZE;
	data->player.img.img = mlx_new_image(data->mlx, data->player.img.width, data->player.img.height);
	if (!data->player.img.img)
		img_failure(data);

	if (mlx_image_to_window(data->mlx, data->minimapfixed.img, WIDTH - MINIMAP_WIDTH, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}
	ft_memset(data->player.img.img->pixels, 255, data->player.img.width * data->player.img.height * sizeof(int));
	converttocircle(&data->player.img, data->player.img.width / 2);
	if (mlx_image_to_window(data->mlx, data->player.img.img, WIDTH - MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}
	data->time_counter = 0;
	data->time = mlx_put_string(data->mlx, "TIME: 0", WIDTH - MINIMAP_WIDTH / 2 - 40, MINIMAP_HEIGHT + 10);
	// if (mlx_image_to_window(data->mlx, data->minimap.img, 0, 0) == -1)
	// {
	// 	mlx_close_window(data->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	cleaner(data);
	// 	exit(EXIT_FAILURE);
	// }
}

void	init_values(t_cub3data	*data)
{
	int	i;

	i = -1;
	while (++i < 6)
		data->ids[i] = NULL;
	data->map_width = 0;
	data->color.white.r = 255;
	data->color.white.g = 255;
	data->color.white.b = 255;
	data->color.white.a = 255;
	data->color.gray.r = 125;
	data->color.gray.g = 125;
	data->color.gray.b = 125;
	data->color.gray.a = 255;
	data->color.golden.r = 212;
	data->color.golden.g = 175;
	data->color.golden.b = 55;
	data->color.golden.a = 255;
	data->color.blue.r = 27;
	data->color.blue.g = 32;
	data->color.blue.b = 73;
	data->color.blue.a = 255;
	data->color.black.r = 0;
	data->color.black.g = 0;
	data->color.black.b = 0;
	data->color.black.a = 0;
}
