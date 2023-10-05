/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:37:43 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/05 21:10:27 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_access_directions(char *line, t_cub3data *data)
{
	int		i;
	int		fd;
	char	*aux;

	i = -1;
	while (++i < 4)
	{
		if (ft_strlen(data->ids[i]) - 3 <= 0)
			ft_error("Error\nFile doesn't contain valid map\n", 7, line, \
data->ids[0], data->ids[1], data->ids[2], data->ids[3], data->ids[4], \
data->ids[5]);
		aux = ft_substr(data->ids[i], 2, ft_strlen(data->ids[i]) - 3);
		ft_printf("Data %d: %s, tam: %d\n", i, aux, ft_strlen(data->ids[i]) - 2);
		fd = open(aux, O_RDONLY);
		if (fd == -1)
			ft_error("Error\nFile doesn't contain valid map\n", 8, line, \
data->ids[0], data->ids[1], data->ids[2], data->ids[3], data->ids[4], \
data->ids[5], aux);
		ft_free_and_null((void **)&aux);
	}
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
			data->ids[pos] = ft_strdup(line + j);
			i++;
		}
		ft_free_and_null((void **)&line);
		line = get_next_line(fd);
	}
	if (!line)
		ft_error("Error\nFile doesn't contain valid map\n", 7, line, \
data->ids[0], data->ids[1], data->ids[2], data->ids[3], data->ids[4], \
data->ids[5]);
	ft_access_directions(line, data);
	return (line);
}
