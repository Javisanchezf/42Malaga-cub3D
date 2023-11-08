/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_hooks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:16:21 by javiersa          #+#    #+#             */
/*   Updated: 2023/11/08 19:50:22 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_time_hook(void *param)
{
	t_cub3data	*data;
	char		*str;
	int			i;

	data = param;
	if (data->pause == 1)
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
