/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids_parse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:37:43 by javiersa          #+#    #+#             */
/*   Updated: 2023/11/08 19:50:44 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	ft_extract_color_with_alpha(char **aux, t_pixels *color)
{
	t_coords	p;

	if (!aux || ft_split_size(aux) != 4)
		return (ft_split_free(aux), 0);
	p.y = -1;
	while (++p.y < 4)
	{
		p.x = -1;
		while (aux[p.y][++p.x])
			if (!ft_isdigit(aux[p.y][p.x]) || p.x > 2)
				return (ft_split_free(aux), 0);
	}
	if (ft_atoi(aux[0]) > 255 || ft_atoi(aux[1]) > 255 || \
	ft_atoi(aux[2]) > 255 || ft_atoi(aux[3]) > 255)
		return (ft_split_free(aux), 0);
	color->r = ft_atoi(aux[0]);
	color->g = ft_atoi(aux[1]);
	color->b = ft_atoi(aux[2]);
	color->a = ft_atoi(aux[3]);
	ft_split_free(aux);
	return (1);
}

static bool	ft_extract_color(char *color_str, t_pixels *color)
{
	t_coords	p;
	char		**aux;

	p.x = -1;
	while (ft_isspace(color_str[++p.x]))
		;
	aux = ft_split(&color_str[p.x], ',');
	if (!aux || ft_split_size(aux) != 3)
		return (ft_extract_color_with_alpha(aux, color));
	p.y = -1;
	while (++p.y < 3)
	{
		p.x = -1;
		while (aux[p.y][++p.x])
			if (!ft_isdigit(aux[p.y][p.x]) || p.x > 2)
				return (ft_split_free(aux), 0);
	}
	if (ft_atoi(aux[0]) > 255 || ft_atoi(aux[1]) > 255 || ft_atoi(aux[2]) > 255)
		return (ft_split_free(aux), 0);
	color->r = ft_atoi(aux[0]);
	color->g = ft_atoi(aux[1]);
	color->b = ft_atoi(aux[2]);
	color->a = 255;
	ft_split_free(aux);
	return (1);
}

static int	ft_extract_ids_aux(char *line, t_cub3data *data, int *j)
{
	*j = 0;
	while (line[*j] == ' ')
		(*j)++;
	if (line[0] == '\n')
		return (-1);
	else if (ft_strncmp("NO ", &line[*j], 3) == 0 && !data->ids[0])
		return (0);
	else if (ft_strncmp("SO ", &line[*j], 3) == 0 && !data->ids[1])
		return (1);
	else if (ft_strncmp("WE ", &line[*j], 3) == 0 && !data->ids[2])
		return (2);
	else if (ft_strncmp("EA ", &line[*j], 3) == 0 && !data->ids[3])
		return (3);
	else if (ft_strncmp("F ", &line[*j], 2) == 0 && !data->ids[4])
		return (4);
	else if (ft_strncmp("C ", &line[*j], 2) == 0 && !data->ids[5])
		return (5);
	ft_error("Error\nRepeated parameters or incorrect lines\n", 7, line, \
data->ids[0], data->ids[1], data->ids[2], data->ids[3], data->ids[4], \
data->ids[5]);
	return (-2);
}

char	*ft_ids_parse(int fd, t_cub3data *data, char *line)
{
	int		pos;
	int		i;
	int		j;

	i = 0;
	while (line && i < 6)
	{
		pos = ft_extract_ids_aux(line, data, &j);
		if (pos >= 0 && pos <= 5)
		{
			j += 2;
			while (line[j] == ' ')
				j++;
			data->ids[pos] = ft_substr(line + j, 0, ft_strlen(line + j) - 1);
			i++;
		}
		ft_free_and_null((void **)&line);
		line = get_next_line(fd);
	}
	if (!line || !ft_extract_color(data->ids[4], &data->color.floor) || \
	!ft_extract_color(data->ids[5], &data->color.ceiling))
		ft_error("Error\nFile doesn't contain valid map\n", 7, line, \
data->ids[0], data->ids[1], data->ids[2], data->ids[3], data->ids[4], \
data->ids[5]);
	return (line);
}
