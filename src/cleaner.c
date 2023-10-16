/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:41:54 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/16 19:30:54 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initial_cleaner(t_cub3data *data)
{
	int	i;

	i = -1;
	while (++i < 6)
		ft_free_and_null((void **)&data->ids[i]);
	ft_split_free(data->map);
	ft_free_and_null((void **)&data->minimap.img);
	ft_free_and_null((void **)&data->minimap_open.img);
}

void	img_failure(t_cub3data *data)
{
	mlx_close_window(data->mlx);
	puts(mlx_strerror(mlx_errno));
	initial_cleaner(data);
	exit(EXIT_FAILURE);
}

void	final_cleaner(t_cub3data *data)
{
	initial_cleaner(data);
	mlx_delete_image(data->mlx, data->player.img);
	mlx_delete_image(data->mlx, data->galaxy_i);
	mlx_delete_image(data->mlx, data->chest_i);
	mlx_delete_image(data->mlx, data->victory_i);
	mlx_delete_image(data->mlx, data->minimapfixed);
	mlx_delete_image(data->mlx, data->time);
	mlx_delete_image(data->mlx, data->player.ray_img);
	mlx_terminate(data->mlx);
}
