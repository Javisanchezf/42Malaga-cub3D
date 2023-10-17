/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:46:49 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/17 17:34:54 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_images(t_cub3data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D 42", true);
	if (!data->mlx)
	{
		ft_error("Error\nMLX init failure", 0);
		initial_cleaner(data);
		exit(EXIT_FAILURE);
	}

	data->map_close.width = data->width * BLOCKSIZE;
	data->map_close.rwidth = data->width * BLOCKSIZE * 4;
	data->map_close.height = data->height * BLOCKSIZE;
	data->map_close.img = ft_calloc(data->map_close.rwidth * data->map_close.height, sizeof(uint8_t));
	data->map_open.img = ft_calloc(data->map_close.rwidth * data->map_close.height, sizeof(uint8_t));

	data->galaxy_i = create_imgtext(data, "./src/imgs/galaxy.png", 0, 0);

	data->victory_i = create_imgtext(data, "./src/imgs/victory.png", 0, 0);
	data->victory_i->enabled = 0;

	data->minimap = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!data->minimap)
		img_failure(data);
	if (mlx_image_to_window(data->mlx, data->minimap, WIDTH - MINIMAP_SIZE, 0) == -1)
		img_failure(data);

	
	data->player.ray_img = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!data->player.ray_img)
		img_failure(data);
	if (mlx_image_to_window(data->mlx, data->player.ray_img, WIDTH - MINIMAP_SIZE / 2 - data->player.ray_img->width / 2, MINIMAP_SIZE / 2 - data->player.ray_img->height / 2) == -1)
		img_failure(data);

	data->player.img = create_imgtext(data, "./src/imgs/ufo.png", WIDTH - MINIMAP_SIZE / 2 - 25, MINIMAP_SIZE / 2 - 25);
	data->chest_i = create_imgtext(data, "./src/imgs/chest.png", 0, 0);
	data->chest_i->enabled = 0;

	data->time_counter = 0;
	data->open_coldown = -30000;
	data->time = mlx_put_string(data->mlx, "TIME: 0", WIDTH - MINIMAP_SIZE / 2 - 100, MINIMAP_SIZE + 10);
}

void	init_values(t_cub3data	*data)
{
	int	i;

	i = -1;
	while (++i < 6)
		data->ids[i] = NULL;
	data->map_close.img = NULL;
	data->map_open.img = NULL;
	data->finish = 0;
	data->door_open = 0;
	data->pass_door = 0;
	data->width = 0;
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
	data->color.green.r = 27;
	data->color.green.g = 114;
	data->color.green.b = 51;
	data->color.green.a = 255;
	data->color.red.r = 104;
	data->color.red.g = 0;
	data->color.red.b = 0;
	data->color.red.a = 255;
}
