/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:07:49 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/15 21:38:21 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_extract_ids(int fd, t_cub3data *data, char *line)
{
	while (line)
	{
		if (data->ids.no && data->ids.so && data->ids.we \
		&& data->ids.ea && data->ids.f && data->ids.c)
			break ;
		else if (ft_strncmp("NO ", line, 3) == 0)
			data->ids.no = ft_strdup(line);
		else if (ft_strncmp("SO ", line, 3) == 0)
			data->ids.so = ft_strdup(line);
		else if (ft_strncmp("WE ", line, 3) == 0)
			data->ids.we = ft_strdup(line);
		else if (ft_strncmp("EA ", line, 3) == 0)
			data->ids.ea = ft_strdup(line);
		else if (ft_strncmp("F ", line, 2) == 0)
			data->ids.f = ft_strdup(line);
		else if (ft_strncmp("C", line, 2) == 0)
			data->ids.c = ft_strdup(line);
		ft_free_and_null((void **)&line);
		line = get_next_line(fd);
	}
	if (!line)
		ft_error ("Error\nThe file doesn't contain valid map", 6, data->ids.no, \
		data->ids.so, data->ids.we, data->ids.ea, data->ids.f, data->ids.c);
	return (line);
}

void	ft_readmap(int fd, t_cub3data *data)
{
	char	*line;

	data->map_height = 0;
	line = ft_extract_ids(fd, data, get_next_line(fd));
	data->map_width = ft_count_words(line);
	while (line && ++data->map_height)
	{
		if (data->map_width != ft_count_words(line) || data->map_width == 0)
			ft_error("The file does not contain a valid map.", 2, aux, line);
		aux = ft_freeandjoin(aux, line);
		line = get_next_line(fd);
	}
	// ft_extract_colorandz(aux, data);
	ft_multiple_free(2, aux, line);
}

void	ft_map_construct(char *file, t_cub3data	*data)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nCould not read the file", 0);
	ft_readmap(fd, data);
	// ft_views(data);
	close(fd);
}
