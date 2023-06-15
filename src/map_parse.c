/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:07:49 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/15 21:13:21 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	ft_check_all_data_extract(t_cub3data *data)
// {
// 	return (!data->ids.no || !data->ids.so || !data->ids.we || !data->ids.ea || !data->ids.f || !data->ids.c);
// }

void	ft_extract_ids_aux()
{
	
}

char	*ft_extract_ids(int fd, char *aux, t_cub3data *data)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		ft_error("Error\nThe file does not contain a valid map.", 1, aux);
	while (line)
	{
		if (data->ids.no && data->ids.so && data->ids.we \
		&& data->ids.ea && data->ids.f && data->ids.c)
			break ;
		if ()
	}
}

void	ft_readmap(int fd, t_cub3data *data)
{
	char	*line;
	char	*aux;

	data->map_height = 0;
	aux = ft_calloc(1, 1);
	if (!aux)
		ft_error("Error\nProblem allocating memory, try freeing up space.", 0);
	line = ft_extract_ids();
	// line = get_next_line(fd);
	// if (!line)
	// 	ft_error("Error\nThe file does not contain a valid map.", 1, aux);
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
