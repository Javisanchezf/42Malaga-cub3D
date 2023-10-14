/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:46:49 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/14 17:31:59 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	img_failure(t_cub3data *data)
{
	mlx_close_window(data->mlx);
	puts(mlx_strerror(mlx_errno));
	initial_cleaner(data);
	exit(EXIT_FAILURE);
}

void	init_images(t_cub3data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D 42", true);
	if (!data->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		initial_cleaner(data);
		exit(EXIT_FAILURE);
	}

	data->minimap.width = data->map_width * BLOCKSIZE;
	data->minimap.rwidth = data->map_width * BLOCKSIZE * 4;
	data->minimap.height = data->map_height * BLOCKSIZE;
	data->minimap.img = ft_calloc(data->minimap.rwidth * data->minimap.height, sizeof(uint8_t));
	data->minimap_open.img = ft_calloc(data->minimap.rwidth * data->minimap.height, sizeof(uint8_t));

	data->galaxy_tex = mlx_load_png("./src/imgs/galaxy.png");
	if (!data->galaxy_tex)
		img_failure(data);
	data->galaxy_i = mlx_texture_to_image(data->mlx, data->galaxy_tex);
	if (!data->galaxy_i)
		img_failure(data);
	if (mlx_image_to_window(data->mlx, data->galaxy_i, 0, 0) == -1)
		img_failure(data);
	data->galaxy_i->enabled = 0;

	data->victory_tex = mlx_load_png("./src/imgs/victory.png");
	if (!data->galaxy_tex)
		img_failure(data);
	data->victory_i = mlx_texture_to_image(data->mlx, data->victory_tex);
	if (!data->victory_i)
		img_failure(data);
	if (mlx_image_to_window(data->mlx, data->victory_i, 0, 0) == -1)
		final_cleaner(data);
	data->victory_i->enabled = 0;

	data->minimapfixed.width = MINIMAP_WIDTH;
	data->minimapfixed.rwidth = MINIMAP_WIDTH * 4;
	data->minimapfixed.height =  MINIMAP_HEIGHT;
	data->minimapfixed.img = mlx_new_image(data->mlx, data->minimapfixed.width, data->minimapfixed.height);
	if (!data->minimapfixed.img)
		img_failure(data);
	if (mlx_image_to_window(data->mlx, data->minimapfixed.img, WIDTH - MINIMAP_WIDTH, 0) == -1)
		img_failure(data);

	data->player.ray_img.width = MINIMAP_WIDTH;
	data->player.ray_img.rwidth = MINIMAP_WIDTH * 4;
	data->player.ray_img.height = MINIMAP_WIDTH;
	data->player.ray_img.img = mlx_new_image(data->mlx, data->player.ray_img.width, data->player.ray_img.height);
	if (!data->player.ray_img.img)
		img_failure(data);
	if (mlx_image_to_window(data->mlx, data->player.ray_img.img, WIDTH - MINIMAP_WIDTH / 2 - data->player.ray_img.width / 2, MINIMAP_HEIGHT / 2 - data->player.ray_img.height / 2) == -1)
		img_failure(data);

	data->player.img.width = 50;
	data->player.img.rwidth = 50 * 4;
	data->player.img.height = 50;
	data->player.texture = mlx_load_png("./src/imgs/ufo.png");
	if (!data->player.texture)
		img_failure(data);
	data->player.img.img = mlx_texture_to_image(data->mlx, data->player.texture);
	if (!data->player.img.img)
		img_failure(data);
	if (mlx_image_to_window(data->mlx, data->player.img.img, WIDTH - MINIMAP_WIDTH / 2 - 25, MINIMAP_HEIGHT / 2 - 25) == -1)
		img_failure(data);

	data->chest_tex = mlx_load_png("./src/imgs/chest.png");
	if (!data->chest_tex)
		img_failure(data);
	data->chest_i = mlx_texture_to_image(data->mlx, data->chest_tex);
	if (!data->player.img.img)
		img_failure(data);

	data->time_counter = 0;
	data->open_coldown = -30000;
	data->time = mlx_put_string(data->mlx, "TIME: 0", WIDTH - MINIMAP_WIDTH / 2 - 100, MINIMAP_HEIGHT + 10);
}

void	init_values(t_cub3data	*data)
{
	int	i;

	i = -1;
	while (++i < 6)
		data->ids[i] = NULL;
	data->minimap.img = NULL;
	data->minimap_open.img = NULL;
	data->finish = 0;
	data->door_open = 0;
	data->pass_door = 0;
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
	data->color.green.r = 27;
	data->color.green.g = 114;
	data->color.green.b = 51;
	data->color.green.a = 255;
	data->color.red.r = 104;
	data->color.red.g = 0;
	data->color.red.b = 0;
	data->color.red.a = 255;
}
