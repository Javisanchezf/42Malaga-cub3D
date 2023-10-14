/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:40:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/14 12:14:06 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_iswall(t_coords p, t_cub3data *data)
{
	t_coords	pcasted;

	pcasted.x = p.x / BLOCKSIZE;
	pcasted.y = p.y / BLOCKSIZE;
	if (pcasted.x > data->map_width || pcasted.y > data->map_height)
		return (0);
	else if (data->map[pcasted.y][pcasted.x] == '1')
		return (1);
	else if (data->map[pcasted.y][pcasted.x] == '2')
		return (2);
	else if (data->map[pcasted.y][pcasted.x] == 'F')
		if (p.x % BLOCKSIZE >= ft_abs(CHEST_SIZE - BLOCKSIZE) / 2 && p.x % BLOCKSIZE <= (BLOCKSIZE - CHEST_SIZE))
			if (p.y % BLOCKSIZE >= ft_abs(CHEST_SIZE - BLOCKSIZE) / 2 && p.y % BLOCKSIZE <= (BLOCKSIZE - CHEST_SIZE))
				return (3);
	return (0);
}
