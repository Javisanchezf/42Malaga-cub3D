/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:43:40 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/09 19:20:16 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

static void	ft_check_map(char *m, t_cub3data *data)
{
	int				i;
	int				j;
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
		ft_error("Error\nInvalid map\n", 7, m, data->ids[0], \
data->ids[1], data->ids[2], data->ids[3], data->ids[4], data->ids[5]);
}

static void	ft_map_normalize(char *m, t_cub3data *data)
{
	int		i;
	int		j;
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

static void	ft_readmap(int fd, t_cub3data *data)
{
	char	*line;
	char	*aux;

	line = ft_ids_parse(fd, data, get_next_line(fd));
	while (line && line[0] == '\n')
	{
		ft_free_and_null((void **)&line);
		line = get_next_line(fd);
	}
	if (!line)
		ft_error("Error\nFile doesn't contain valid map\n", 7, line, \
data->ids[0], data->ids[1], data->ids[2], data->ids[3], data->ids[4], \
data->ids[5]);
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

void	ft_parse_data(char *file, t_cub3data	*data)
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
		ft_error("Error\nCould not read the file\n", 0);
	ft_readmap(fd, data);
	close(fd);
	ft_map_parse(data);
}
