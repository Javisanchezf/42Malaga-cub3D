/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:55:21 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/14 17:46:59 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keyboard_hooks(void *param)
{
	t_cub3data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (data->finish == 1)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		check_collision(data, cos(data->player.orientation + PI),
				sin(data->player.orientation + PI));
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		check_collision(data, cos(data->player.orientation),
				sin(data->player.orientation));
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		check_collision(data, sin(data->player.orientation + PI),
				-cos(data->player.orientation + PI));
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		check_collision(data, sin(data->player.orientation),
				-cos(data->player.orientation));
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.orientation -= 10 * 0.01745;
		ufo_rays(data, &data->player.ray_img, data->player.orientation, data->color.golden);
		data->galaxy_i->instances->x-=50;
		if (data->galaxy_i->instances->x < (int32_t)(1920 - data->galaxy_i->width))
			data->galaxy_i->instances->x = 0;

	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.orientation += 10 * 0.01745;
		ufo_rays(data, &data->player.ray_img, data->player.orientation, data->color.golden);
		data->galaxy_i->instances->x+=50;
		if (data->galaxy_i->instances->x > 0)
			data->galaxy_i->instances->x = 1920 - data->galaxy_i->width;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_0))
		data->galaxy_i->enabled = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_1))
		data->galaxy_i->enabled = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		if (data->door_open == 0 && data->open_coldown <= 0)
		{
			uint8_t *temp_img = data->minimap.img;
			data->minimap.img = data->minimap_open.img;
			data->minimap_open.img = temp_img;
			check_collision(data, 0, 0);
			data->door_open = 1;
			data->open_coldown = data->time_counter + 300;
		}
	}
}

void	close_door_hook(void *param)
{
	t_cub3data	*data;

	data = param;
	if (data->finish == 1)
		return ;
	if (data->door_open == 1 && (data->pass_door == 1 || data->open_coldown == 0))
	{
		int			i;
		t_coords	player_abroad[4];

		player_abroad[0].x = data->player.pos.x + PLAYER_SIZE;
		player_abroad[0].y = data->player.pos.y;
		player_abroad[1].x = data->player.pos.x - PLAYER_SIZE;
		player_abroad[1].y = data->player.pos.y;
		player_abroad[2].x = data->player.pos.x;
		player_abroad[2].y = data->player.pos.y + PLAYER_SIZE;
		player_abroad[3].x = data->player.pos.x;
		player_abroad[3].y = data->player.pos.y - PLAYER_SIZE;
		i = -1;
		while (++i < 4)
		{
			if (ft_iswall(player_abroad[i], data) != 0)
				return ;
		}
		data->door_open = 0;
		data->pass_door = 0;
		uint8_t *temp_img = data->minimap.img;
		data->minimap.img = data->minimap_open.img;
		data->minimap_open.img = temp_img;
		check_collision(data, 0, 0);
	}
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
	str = ft_freeandjoin(ft_strdup("TIME: "), ft_itoa(data->time_counter
				/ 100));
	str = ft_freeandjoin(str, ft_strdup("."));
	str = ft_freeandjoin(str, ft_itoa(data->time_counter % 100));
	str = ft_freeandjoin(str, ft_strdup(" | COOLDOWN: "));
	i = data->open_coldown - data->time_counter;
	if ( i < 0)
	{
		i = 0;
		data->open_coldown = 0;
	}
	str = ft_freeandjoin(str, ft_itoa(i / 100));
	str = ft_freeandjoin(str, ft_strdup("."));
	str = ft_freeandjoin(str, ft_itoa(i % 100));
	data->time = mlx_put_string(data->mlx, str, WIDTH - MINIMAP_WIDTH / 2 - 100,
			MINIMAP_HEIGHT + 10);
	ft_free_and_null((void **)&str);
}
