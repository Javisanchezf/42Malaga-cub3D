/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:40:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/24 21:46:14 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_iswall(t_coords p, t_cub3data *data)
{
	t_coords	pcasted;

	pcasted.x = p.x / BLOCKSIZE;
	pcasted.y = p.y / BLOCKSIZE;
	if (pcasted.x >= data->width || pcasted.y >= data->height || \
	pcasted.x < 0 || pcasted.y < 0)
		return (1);
	else if (data->map[pcasted.y][pcasted.x] == '1')
		return (1);
	else if (data->map[pcasted.y][pcasted.x] == '2')
		return (2);
	else if (data->map[pcasted.y][pcasted.x] == 'F')
		if (p.x % BLOCKSIZE >= ft_abs(data->chest_i->width - BLOCKSIZE) / 2 && \
		p.x % BLOCKSIZE <= (BLOCKSIZE - (int)data->chest_i->width))
			if (p.y % BLOCKSIZE >= ft_abs(data->chest_i->width - BLOCKSIZE) / \
		2 && p.y % BLOCKSIZE <= (BLOCKSIZE - (int)data->chest_i->width))
				return (3);
	return (0);
}

int	ft_isabroadwall(t_coords p, int radius, t_cub3data *data)
{
	t_coords	p_abroad[4];
	int			i;
	int			value;

	p_abroad[0].x = p.x + radius;
	p_abroad[0].y = p.y;
	p_abroad[1].x = p.x - radius;
	p_abroad[1].y = p.y;
	p_abroad[2].x = p.x;
	p_abroad[2].y = p.y + radius;
	p_abroad[3].x = p.x;
	p_abroad[3].y = p.y - radius;
	i = -1;
	value = 0;
	while (++i < 4 && value == 0)
		value = ft_iswall(p_abroad[i], data);
	return (value);
}

int	ft_isabroadwall2(t_coords p, int radius, t_cub3data *data)
{
	t_coords	p_abroad[4];
	int			i;
	int			value;

	p_abroad[0].x = p.x + radius;
	p_abroad[0].y = p.y;
	p_abroad[1].x = p.x - radius;
	p_abroad[1].y = p.y;
	p_abroad[2].x = p.x;
	p_abroad[2].y = p.y + radius;
	p_abroad[3].x = p.x;
	p_abroad[3].y = p.y - radius;
	i = -1;
	value = 0;
	while ((++i < 4 && value == 0) || (i < 4 && value == 2 && data->door_open))
		value = ft_iswall(p_abroad[i], data);
	return (value);
}

void	finish(t_cub3data *data)
{
	char		*str;

	data->finish = 1;
	data->player.img->enabled = 0;
	data->galaxy_i->enabled = 0;
	data->chest_i->enabled = 0;
	data->minimap->enabled = 0;
	data->player.ray_img->enabled = 0;
	data->time->instances->x = WIDTH / 2 - 30;
	data->time->instances->y = HEIGHT / 2;
	data->victory_i->enabled = 1;
	mlx_delete_image(data->mlx, data->time);
	str = ft_freeandjoin(ft_strdup("TIME: "), ft_itoa(data->time_counter
				/ 100));
	str = ft_freeandjoin(str, ft_strdup("."));
	str = ft_freeandjoin(str, ft_itoa(data->time_counter % 100));
	data->time = mlx_put_string(data->mlx, str, WIDTH / 2 - 30, HEIGHT / 2);
	ft_free_and_null((void **)&str);
}

void	check_collision(t_cub3data *data, t_coords pos, double x, double y)
{
	int			j;

	pos.x += x * PLAYER_SIZE / 2;
	pos.y += y * PLAYER_SIZE / 2;
	j = ft_isabroadwall2(pos, PLAYER_SIZE, data);
	if (j == 1 || (j == 2 && data->door_open == 0))
		return ;
	else if (j == 3)
		return (finish(data));
	data->player.pos.x = pos.x;
	data->player.pos.y = pos.y;
	draw_minimap(data);
	ufo_rays(data, data->player.ray_img, data->player.angle);
	raycasting(data, data->player.pos);
	if (j == 2)
		data->pass_door = 1;
}
