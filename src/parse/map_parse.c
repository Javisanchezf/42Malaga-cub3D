/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:45:00 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/11 20:33:40 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_vertical(t_cub3data data, int i, int j, int i1)
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

static int	ft_horiz(t_cub3data data, int i, int j, int j1)
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

static int	check_enviroment(t_cub3data data, int i, int j)
{
	if (ft_vertical(data, i, j, i))
		return (1);
	if (ft_horiz(data, i, j, j))
		return (1);
	return (0);
}

static void	ft_extract_player_position(t_cub3data *data)
{
	t_coords	p;

	p.y = -1;
	while (data->map[++p.y])
	{
		p.x = -1;
		while (data->map[p.y][++p.x])
		{
			if (data->map[p.y][p.x] == 'N' || data->map[p.y][p.x] == 'S' || \
			data->map[p.y][p.x] == 'W' || data->map[p.y][p.x] == 'E')
			{
				data->player.pos.x = p.x * BLOCKSIZE + BLOCKSIZE / 2;
				data->player.pos.y = p.y * BLOCKSIZE + BLOCKSIZE / 2;
				if (data->map[p.y][p.x] == 'N')
					data->player.orientation = 90;
				else if (data->map[p.y][p.x] == 'S')
					data->player.orientation = 270;
				else if (data->map[p.y][p.x] == 'W')
					data->player.orientation = 180;
				else
					data->player.orientation = 0;
				return ;
			}
		}
	}
}

void	ft_map_parse(t_cub3data *data)
{
	int	i;
	int	j;
	int	error;

	i = -1;
	j = -1;
	error = 0;
	while (++i < data->map_height && !error)
	{
		while (++j < data->map_width && !error)
		{
			if (data->map[i][j] == ' ')
				error = check_enviroment(*data, i, j);
		}
		j = -1;
	}
	if (error)
	{
		cleaner(data);
		ft_error("ERROR\n This map is not valid\n", 0);
	}
	ft_extract_player_position(data);
}
