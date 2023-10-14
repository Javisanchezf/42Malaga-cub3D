/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:55:21 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/14 12:55:42 by javiersa         ###   ########.fr       */
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
	{
		if (data->galaxy_i->enabled == 0)
			data->galaxy_i->enabled = 1;
		else if (data->galaxy_i->enabled == 1)
			data->galaxy_i->enabled = 0;
	}
}

void	time_hook(void *param)
{
	t_cub3data	*data;
	char		*str;

	data = param;
	if (data->finish == 1)
		return ;
	data->time_counter++;
	mlx_delete_image(data->mlx, data->time);
	str = ft_freeandjoin(ft_strdup("TIME: "), ft_itoa(data->time_counter
				/ 100));
	str = ft_freeandjoin(str, ft_strdup("."));
	str = ft_freeandjoin(str, ft_itoa(data->time_counter % 100));
	data->time = mlx_put_string(data->mlx, str, WIDTH - MINIMAP_WIDTH / 2 - 40,
			MINIMAP_HEIGHT + 10);
	ft_free_and_null((void **)&str);
}
