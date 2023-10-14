/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:43:40 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/14 12:14:29 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

static void	ft_check_map(char *m, t_cub3data *data)
{
	t_coords		p;
	short int		flag;
	short int		final_flag;

	p.x = -1;
	p.y = 0;
	flag = 0;
	final_flag = 0;
	while (m[++p.x] && flag <= 1 && final_flag < 2 )
	{
		if (m[p.x] == 'N' || m[p.x] == 'S' || m[p.x] == 'W' || m[p.x] == 'E')
			flag++;
		else if (m[p.x] == 'F')
			final_flag++;
		else if (m[p.x] == '\n')
		{
			if (p.x - p.y + 1 > data->map_width)
				data->map_width = p.x - p.y + 1;
			p.y = p.x;
		}
		else if (m[p.x] != '0' && m[p.x] != '1' && m[p.x] != ' ' && m[p.x] != '2')
			flag = 2;
	}
	if (flag != 1 || final_flag > 1)
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
