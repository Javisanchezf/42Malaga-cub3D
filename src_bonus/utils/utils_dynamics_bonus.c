/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dynamics_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:40:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/11/08 19:52:06 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	ft_check_player_abroad(t_coords p, t_cub3data *data, bool doors)
{
	t_coords	p_abroad[4];
	int			i;
	int			value;

	p_abroad[0].x = p.x + PLAYER_SIZE;
	p_abroad[0].y = p.y;
	p_abroad[1].x = p.x - PLAYER_SIZE;
	p_abroad[1].y = p.y;
	p_abroad[2].x = p.x;
	p_abroad[2].y = p.y + PLAYER_SIZE;
	p_abroad[3].x = p.x;
	p_abroad[3].y = p.y - PLAYER_SIZE;
	i = -1;
	value = 0;
	if (!doors)
	{
		while (++i < 4 && value == 0)
			value = ft_iswall(p_abroad[i], data);
		return (value);
	}
	while ((++i < 4 && value == 0) || (i < 4 && value == 2 && data->door_open))
		value = ft_iswall(p_abroad[i], data);
	return (value);
}

void	ft_redraw(t_cub3data *data, double angle)
{
	if (angle != 0)
	{
		data->player.angle += angle;
		data->galaxy_i->instances->x -= (int)(angle * 300);
		if (data->galaxy_i->instances->x > 0)
			data->galaxy_i->instances->x = 1920 - data->galaxy_i->width;
		else if (data->galaxy_i->instances->x < (int32_t)(1920 - \
			data->galaxy_i->width))
			data->galaxy_i->instances->x = 0;
	}
	else
		ft_draw_minimap(data);
	ft_draw_ufo_rays(data, data->player.ray_img, data->player.angle);
	raycasting(data, data->player.pos);
}

static void	finish(t_cub3data *data)
{
	char		*str;

	data->pause = 1;
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

void	ft_move(t_cub3data *data, t_coords pos, double x, double y)
{
	int			j;
	int			i;

	i = 3;
	pos.x += x * i;
	pos.y += y * i;
	j = ft_check_player_abroad(pos, data, 1);
	while ((j == 0 || (j == 2 && data->door_open == 1) || \
	j == 3) && ++i < VELOCITY)
	{
		if (j == 3)
			return (finish(data));
		pos.x = data->player.pos.x + x * i;
		pos.y = data->player.pos.y + y * i;
		j = ft_check_player_abroad(pos, data, 1);
	}
	if (i <= 3)
		return ;
	data->player.pos.x = pos.x;
	data->player.pos.y = pos.y;
	ft_redraw(data, 0);
	if (j == 2)
		data->pass_door = 1;
}
