/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:38:47 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/25 21:25:55 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cursor_hook(double x2, double y2, void *param)
{
	t_cub3data		*data;
	static double	y1 = 0;
	static double	x1 = 0;
	static int		i = 0;

	data = param;
	i++;
	if (!data->cursor_hook || i < 2)
		return ;
	i = 0;
	data->player.angle += ((x2 - x1) / 10) * 0.01745;
	ufo_rays(data, data->player.ray_img, data->player.angle);
	data->galaxy_i->instances->x += 50;
	if (data->galaxy_i->instances->x > 0)
		data->galaxy_i->instances->x = 1920 - data->galaxy_i->width;
	raycasting(data, data->player.pos);
	x1 = x2;
	(void)y1;
	(void)y2;
}
