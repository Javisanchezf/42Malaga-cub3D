/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:07:49 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/04 21:27:19 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_extract_ids_aux(char *line, t_cub3data *data)
{
	if (line[0] == '\n')
		return (-1);
	else if (ft_strncmp("NO ", line, 3) == 0 && !data->ids[0])
		return (0);
	else if (ft_strncmp("SO ", line, 3) == 0 && !data->ids[1])
		return (1);
	else if (ft_strncmp("WE ", line, 3) == 0 && !data->ids[2])
		return (2);
	else if (ft_strncmp("EA ", line, 3) == 0 && !data->ids[3])
		return (3);
	else if (ft_strncmp("F ", line, 2) == 0 && !data->ids[4])
		return (4);
	else if (ft_strncmp("C ", line, 2) == 0 && !data->ids[5])
		return (5);
	ft_error("Error\nRepeated parameters or incorrect lines", 7, line, \
data->ids[0], data->ids[1], data->ids[2], data->ids[3], data->ids[4], \
data->ids[5]);
	return (-2);
}

char	*ft_extract_ids(int fd, t_cub3data *data, char *line)
{
	int		pos;
	int		i;
	int		j;

	i = 0;
	while (line && i < 6)
	{
		pos = ft_extract_ids_aux(line, data);
		if (pos >= 0 && pos <= 5)
		{
			j = 2;
			while (line[j] == ' ')
				j++;
			data->ids[pos] = ft_strdup(line + j);
			i++;
		}
		ft_free_and_null((void **)&line);
		line = get_next_line(fd);
	}
	if (!line)
		ft_error("Error\nFile doesn't contain valid map", 7, line, \
data->ids[0], data->ids[1], data->ids[2], data->ids[3], data->ids[4], \
data->ids[5]);
	return (line);
}

void	ft_check_map(char *m, t_cub3data *data)
{
	size_t			i;
	size_t			j;
	short int		flag;

	i = 0;
	j = 0;
	flag = 0;
	while (m[i] && flag <= 1)
	{
		if (m[i] == 'N' || m[i] == 'S' || m[i] == 'W' || m[i] == 'E')
			flag++;
		else if (m[i] == '\n')
		{
			if (i - j + 1 > data->map_width)
				data->map_width = i - j + 1;
			j = i;
		}
		else if (m[i] != '0' && m[i] != '1' && m[i] != ' ')
			flag = 2;
		i++;
	}
	if (flag != 1)
		ft_error("Error\nInvalid map", 7, m, data->ids[0], \
data->ids[1], data->ids[2], data->ids[3], data->ids[4], data->ids[5]);
}

void	ft_map_normalize(char *m, t_cub3data *data)
{
	size_t	i;
	size_t	j;
	char	*aux;

	data->map = ft_split(m, '\n');
	data->map_height = ft_split_size(data->map);
	i = 0;
	while (data->map[i])
	{
		aux = ft_calloc(data->map_width + 1, sizeof(char));
		aux[0] = ' ';
		ft_strlcpy(&aux[1], data->map[i], data->map_width);
		j = ft_strlen(data->map[i]);
		while (++j < data->map_width)
			aux[j] = ' ';
		ft_free_and_null((void **)&data->map[i]);
		data->map[i] = aux;
		i++;
	}
}

void	ft_readmap(int fd, t_cub3data *data)
{
	char	*line;
	char	*aux;

	line = ft_extract_ids(fd, data, get_next_line(fd));
	while (line && line[0] == '\n')
	{
		ft_free_and_null((void **)&line);
		line = get_next_line(fd);
	}
	if (!line)
		ft_error("Error\nFile doesn't contain valid map", 7, line, data->ids[0], \
data->ids[1], data->ids[2], data->ids[3], data->ids[4], data->ids[5]);
	aux = ft_strdup(" \n");
	while (line)
	{
		if (line[0] == '\n')
			break ;
		aux = ft_freeandjoin(aux, line);
		line = get_next_line(fd);
	}
	aux = ft_freeandjoin(aux, ft_strdup("\n "));
	ft_check_map(aux, data);
	ft_map_normalize(aux, data);
	ft_multiple_free(2, aux, line);
}

void	ft_map_construct(char *file, t_cub3data	*data)
{
	int		fd;
	int		i;

	i = 0;
	while (file[i])
		i++;
	if (i < 5 || ft_strncmp(".cub", &file[i - 4], 4) != 0)
		ft_error("Error\nInvalid extension.", 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nCould not read the file", 0);
	ft_readmap(fd, data);
	close(fd);
}
