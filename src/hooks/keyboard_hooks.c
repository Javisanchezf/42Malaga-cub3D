/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:55:21 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/26 11:15:54 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_vision_hooks(t_cub3data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		ft_redraw(data, -0.1745);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		ft_redraw(data, 0.1745);
	if (mlx_is_key_down(data->mlx, MLX_KEY_0) && !data->cursor_hook)
	{
		data->cursor_hook = 1;
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_1) && data->cursor_hook)
	{
		data->cursor_hook = 0;
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	}
}

static void	ft_movement_hooks(t_cub3data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		ft_move(data, data->player.pos, \
cos(data->player.angle + PI), sin(data->player.angle + PI));
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		ft_move(data, data->player.pos, \
cos(data->player.angle), sin(data->player.angle));
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		ft_move(data, data->player.pos, \
sin(data->player.angle + PI), -cos(data->player.angle + PI));
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		ft_move(data, data->player.pos, \
sin(data->player.angle), -cos(data->player.angle));
}

static void	ft_doors_hooks(t_cub3data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		if (data->door_open == 0 && data->open_coldown <= 0)
		{
			ft_swap(&data->map_close.img, &data->map_open.img, \
			sizeof(uint8_t *));
			data->door_open = 1;
			ft_move(data, data->player.pos, 0, 0);
			data->open_coldown = data->time_counter + COLDOWN * 100;
		}
	}
	if (data->door_open == 1 && (data->pass_door == 1 || \
	data->open_coldown == 0))
	{
		if (ft_check_player_abroad(data->player.pos, data, 0) != 0)
			return ;
		data->door_open = 0;
		data->pass_door = 0;
		ft_swap(&data->map_close.img, &data->map_open.img, sizeof(uint8_t *));
		ft_move(data, data->player.pos, 0, 0);
	}
}

void	ft_keyboard_hooks(void *param)
{
	t_cub3data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (data->pause == 1)
		return ;
	ft_movement_hooks(data);
	ft_vision_hooks(data);
	ft_doors_hooks(data);
}
