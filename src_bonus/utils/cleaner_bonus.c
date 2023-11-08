/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:41:54 by javiersa          #+#    #+#             */
/*   Updated: 2023/11/08 19:51:44 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_initial_cleaner(t_cub3data *data)
{
	int	i;

	i = -1;
	while (++i < 6)
		ft_free_and_null((void **)&data->ids[i]);
	ft_split_free(data->map);
	ft_free_and_null((void **)&data->map_close.img);
	ft_free_and_null((void **)&data->map_open.img);
}

void	ft_img_failure(t_cub3data *data)
{
	mlx_close_window(data->mlx);
	ft_error("Error\nImage/Texture failure", 0);
	ft_initial_cleaner(data);
	exit(EXIT_FAILURE);
}

void	ft_final_cleaner(t_cub3data *data)
{
	ft_initial_cleaner(data);
	mlx_delete_image(data->mlx, data->player.img);
	mlx_delete_image(data->mlx, data->galaxy_i);
	mlx_delete_image(data->mlx, data->chest_i);
	mlx_delete_image(data->mlx, data->victory_i);
	mlx_delete_image(data->mlx, data->minimap);
	mlx_delete_image(data->mlx, data->time);
	mlx_delete_image(data->mlx, data->player.ray_img);
	mlx_delete_image(data->mlx, data->full_img);
	mlx_delete_image(data->mlx, data->wall.n);
	mlx_delete_image(data->mlx, data->wall.s);
	mlx_delete_image(data->mlx, data->wall.w);
	mlx_delete_image(data->mlx, data->wall.e);
	mlx_terminate(data->mlx);
}
