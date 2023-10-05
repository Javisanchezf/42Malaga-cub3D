/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:34:03 by antdelga          #+#    #+#             */
/*   Updated: 2023/10/05 19:16:13 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_vertical(t_cub3data data, int i, int j, int i1)
{
	while (--i >= 0)
	{
		if (!(data.map[i][j] == ' '))
		{
			if (data.map[i][j] == '1')
				break ;
			else
				return (1);
		}
	}
	i = i1;
	while (++i < data.map_height)
	{
		if (!(data.map[i][j] == ' '))
		{
			if (data.map[i][j] == '1')
				break ;
			else
				return (1);
		}
	}
	return (0);
}

int	ft_horiz(t_cub3data data, int i, int j, int j1)
{
	while (--j >= 0)
	{
		if (!(data.map[i][j] == ' '))
		{
			if (data.map[i][j] == '1')
				break ;
			else
				return (1);
		}
	}
	j = j1;
	while (++j < (data.map_width))
	{
		if (!(data.map[i][j] == ' '))
		{
			if (data.map[i][j] == '1')
				break ;
			else
				return (1);
		}
	}
	return (0);
}

int	check_enviroment(t_cub3data data, int i, int j)
{
	int	j1;

	j1 = j;
	if (ft_vertical(data, i, j, i))
		return (1);
	if (ft_horiz(data, i, j, j))
		return (1);
	return (0);
}

void ft_check_wall(t_cub3data data)
{
	int	i;
	int	j;
	int	error;

	i = -1;
	j = -1;
	error = 0;

	while (++i < data.map_height && !error)
	{
		while (++j < data.map_width && !error)
		{
			if (data.map[i][j] == ' ')
				error = check_enviroment(data, i, j);
		}
		j = -1;
	}
	if (error)
	{
		cleaner(&data);
		ft_error("ERROR\n This map is not valid\n", 0);
	}
}
