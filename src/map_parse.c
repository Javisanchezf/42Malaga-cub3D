/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:07:49 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/03 21:51:57 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char	*ft_extract_ids_aux(int i)
// {
// 	if (i == 0)
// 		return ("NO ");
// 	else if (i == 1)
// 		return ("SO ");
// 	else if (i == 2)
// 		return ("WE ");
// 	else if (i == 3)
// 		return ("EA ");
// 	else if (i == 4)
// 		return ("F ");
// 	else if (i == 5)
// 		return ("C ");
// 	return ("");
// }

char	*ft_extract_ids(int fd, t_cub3data *data, char *line)
{
	char	*ids[] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	int		i;
	int		j;

	i = 0;
	while (line && i < 6)
	{
		if (ft_strncmp(ids[i], line, 2) == 0)
		{
			j = 2;
			while (line[j] == ' ')
				j++;
			data->ids[i] = ft_strdup(line + j);
			ft_printf("%s\n", data->ids[i]);
			i++;
		}
		ft_free_and_null((void **)&line);
		line = get_next_line(fd);
	}
	if (!line)
		ft_error("Error\nFile doesn't contain valid map", i + 1, line, \
data->ids[0], data->ids[1], data->ids[2], data->ids[3], data->ids[4], \
data->ids[5]);
	return (line);
}
// char	**ft_extract_map(char *m, t_cub3data *data)
// {
// 	int		i;
// 	int		j;
// 	bool	flag;

// 	i = -1;
// 	j = 0;
// 	flag = 0;
// 	while (m[++i])
// 	{
// 		if (m[++i] == 'N' || m[++i] == 'S' || m[++i] == 'W' || m[++i] == 'E')
// 		{
// 			if (flag == 1)
// 				ft_error("Error\nInvalid number of players", 7, m, data->ids[0], \
// data->ids[1], data->ids[2], data->ids[3], data->ids[4], data->ids[5]);
// 			else if (flag == 0)
// 				flag = 1;
// 		}
// 	}
// 	if (flag == 0)
// 		ft_error("Error\nInvalid number of players", 7, m, data->ids[0], \
// data->ids[1], data->ids[2], data->ids[3], data->ids[4], data->ids[5]);
// }


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
	aux = ft_calloc(1, 1);
	while (line)
	{
		aux = ft_freeandjoin(aux, line);
		line = get_next_line(fd);
	}
	ft_printf("%s", aux);
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
