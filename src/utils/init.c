/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:46:49 by javiersa          #+#    #+#             */
/*   Updated: 2023/11/07 20:51:39 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ids_imgs(t_cub3data *data)
{
	data->wall.n = ft_img_by_text(data, data->ids[0], 0, 0);
	data->wall.s = ft_img_by_text(data, data->ids[1], 0, 0);
	data->wall.w = ft_img_by_text(data, data->ids[2], 0, 0);
	data->wall.e = ft_img_by_text(data, data->ids[3], 0, 0);
	data->wall.n->enabled = 0;
	data->wall.s->enabled = 0;
	data->wall.w->enabled = 0;
	data->wall.e->enabled = 0;
	data->wall.door = ft_img_by_text(data, "./src/imgs/i.png", 0, 0);
	data->wall.door->enabled = 0;
}

void	init_images_aux(t_cub3data *data)
{
	data->galaxy_i = ft_img_by_text(data, "./src/imgs/galaxy.png", 0, 0);
	data->full_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->full_img)
		ft_img_failure(data);
	if (mlx_image_to_window(data->mlx, data->full_img, 0, 0) == -1)
		ft_img_failure(data);
	init_ids_imgs(data);
	data->victory_i = ft_img_by_text(data, "./src/imgs/victory.png", 0, 0);
	data->victory_i->enabled = 0;
	data->minimap = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!data->minimap)
		ft_img_failure(data);
	if (mlx_image_to_window(data->mlx, data->minimap, WIDTH - MINIMAP_SIZE, \
	0) == -1)
		ft_img_failure(data);
	data->player.ray_img = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!data->player.ray_img)
		ft_img_failure(data);
	if (mlx_image_to_window(data->mlx, data->player.ray_img, WIDTH - \
MINIMAP_SIZE / 2 - data->player.ray_img->width / 2, MINIMAP_SIZE / 2 - \
data->player.ray_img->height / 2) == -1)
		ft_img_failure(data);
	data->player.img = ft_img_by_text(data, "./src/imgs/ufo.png", WIDTH - \
	MINIMAP_SIZE / 2 - 25, MINIMAP_SIZE / 2 - 25);
	data->chest_i = ft_img_by_text(data, "./src/imgs/chest.png", 0, 0);
}

void	init_images(t_cub3data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D 42", false);
	if (!data->mlx)
	{
		ft_error("Error\nMLX init failure", 0);
		ft_initial_cleaner(data);
		exit(EXIT_FAILURE);
	}
	data->map_close.width = data->width * BLOCKSIZE;
	data->map_close.rwidth = data->width * BLOCKSIZE * 4;
	data->map_close.height = data->height * BLOCKSIZE;
	data->map_close.img = ft_calloc(data->map_close.rwidth * \
	data->map_close.height, sizeof(uint8_t));
	data->map_open.img = ft_calloc(data->map_close.rwidth * \
	data->map_close.height, sizeof(uint8_t));
	init_images_aux(data);
	data->chest_i->enabled = 0;
	data->time_counter = 0;
	data->open_coldown = -30000;
	data->time = mlx_put_string(data->mlx, "TIME: 0", WIDTH - \
	MINIMAP_SIZE / 2 - 100, MINIMAP_SIZE + 10);
}

static void	init_colors(t_cub3data	*data)
{
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

void	init_values(t_cub3data	*data)
{
	int	i;

	i = -1;
	while (++i < 6)
		data->ids[i] = NULL;
	data->map_close.img = NULL;
	data->map_open.img = NULL;
	data->pause = 0;
	data->door_open = 0;
	data->pass_door = 0;
	data->width = 0;
	data->cursor_hook = 0;
	init_colors(data);
}
