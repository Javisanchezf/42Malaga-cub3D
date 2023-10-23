/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:55:21 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/23 14:43:55 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_vision_hooks(t_cub3data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.orientation -= 10 * 0.01745;
		ufo_rays(data, data->player.ray_img, data->player.orientation);
		data->galaxy_i->instances->x -= 50;
		if (data->galaxy_i->instances->x < (int32_t)(1920 - \
		data->galaxy_i->width))
			data->galaxy_i->instances->x = 0;
		raycasting(data, data->player.pos);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.orientation += 10 * 0.01745;
		ufo_rays(data, data->player.ray_img, data->player.orientation);
		data->galaxy_i->instances->x += 50;
		if (data->galaxy_i->instances->x > 0)
			data->galaxy_i->instances->x = 1920 - data->galaxy_i->width;
		raycasting(data, data->player.pos);
	}
}

void	ft_movement_hooks(t_cub3data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		check_collision(data, data->player.pos, \
cos(data->player.orientation + PI), sin(data->player.orientation + PI));
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		check_collision(data, data->player.pos, \
cos(data->player.orientation), sin(data->player.orientation));
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		check_collision(data, data->player.pos, \
sin(data->player.orientation + PI), -cos(data->player.orientation + PI));
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		check_collision(data, data->player.pos, \
sin(data->player.orientation), -cos(data->player.orientation));
}

void	ft_doors_hooks(t_cub3data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		if (data->door_open == 0 && data->open_coldown <= 0)
		{
			ft_swap(&data->map_close.img, &data->map_open.img, \
			sizeof(uint8_t *));
			data->door_open = 1;
			check_collision(data, data->player.pos, 0, 0);
			data->open_coldown = data->time_counter + 300;
		}
	}
	if (data->door_open == 1 && (data->pass_door == 1 || \
	data->open_coldown == 0))
	{
		if (ft_isabroadwall(data->player.pos, PLAYER_SIZE, data) != 0)
			return ;
		data->door_open = 0;
		data->pass_door = 0;
		ft_swap(&data->map_close.img, &data->map_open.img, sizeof(uint8_t *));
		check_collision(data, data->player.pos, 0, 0);
	}
}

void	keyboard_hooks(void *param)
{
	t_cub3data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (data->finish == 1)
		return ;
	ft_movement_hooks(data);
	ft_vision_hooks(data);
	ft_doors_hooks(data);
}

void	time_hook(void *param)
{
	t_cub3data	*data;
	char		*str;
	int			i;

	data = param;
	if (data->finish == 1)
		return ;
	data->time_counter++;
	mlx_delete_image(data->mlx, data->time);
	str = ft_freeandjoin(ft_strdup("TIME:"), ft_itoa(data->time_counter / 100));
	str = ft_freeandjoin(str, ft_strdup("."));
	str = ft_freeandjoin(str, ft_itoa(data->time_counter % 100));
	str = ft_freeandjoin(str, ft_strdup(" | COOLDOWN: "));
	i = data->open_coldown - data->time_counter;
	if (i < 0)
	{
		i = 0;
		data->open_coldown = 0;
	}
	str = ft_freeandjoin(str, ft_itoa(i / 100));
	str = ft_freeandjoin(str, ft_strdup("."));
	str = ft_freeandjoin(str, ft_itoa(i % 100));
	data->time = mlx_put_string(data->mlx, str, WIDTH - MINIMAP_SIZE / 2 - 100,
			MINIMAP_SIZE + 10);
	ft_free_and_null((void **)&str);
}
