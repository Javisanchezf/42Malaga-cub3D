/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:38:47 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/25 21:59:02 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_cursor_hook(double x2, double y2, void *param)
{
	t_cub3data		*data;
	static double	x1 = 0;
	static int		i = 0;
	double			change_angle;

	data = param;
	i++;
	if (!data->cursor_hook || i < 2)
		return ;
	i = 0;
	change_angle = (x2 - x1) * (0.01745 / 10);
	data->player.angle += change_angle;
	ufo_rays(data, data->player.ray_img, data->player.angle);
	if (change_angle > 0)
		data->galaxy_i->instances->x -= 50;
	else
		data->galaxy_i->instances->x += 50;
	if (data->galaxy_i->instances->x > 0)
		data->galaxy_i->instances->x = 1920 - data->galaxy_i->width;
	else if (data->galaxy_i->instances->x < (int32_t)(1920 - \
		data->galaxy_i->width))
		data->galaxy_i->instances->x = 0;
	raycasting(data, data->player.pos);
	x1 = x2;
	(void)y2;
}
