/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:45:00 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/24 00:23:36 by javiersa         ###   ########.fr       */
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
	while (++i < data.height)
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
	while (++j < (data.width))
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
					data->player.angle = 90 * PI / 180;
				else if (data->map[p.y][p.x] == 'S')
					data->player.angle = 270 * PI / 180;
				else if (data->map[p.y][p.x] == 'W')
					data->player.angle = 180 * PI / 180;
				else
					data->player.angle = 0;
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
	while (++i < data->height && !error)
	{
		while (++j < data->width && !error)
		{
			if (data->map[i][j] == ' ')
				error = check_enviroment(*data, i, j);
		}
		j = -1;
	}
	if (error)
	{
		initial_cleaner(data);
		ft_error("ERROR\n This map is not valid\n", 0);
	}
	ft_extract_player_position(data);
}
