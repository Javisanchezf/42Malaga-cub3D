/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:40:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/16 19:46:43 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_iswall(t_coords p, t_cub3data *data)
{
	t_coords	pcasted;

	pcasted.x = p.x / BLOCKSIZE;
	pcasted.y = p.y / BLOCKSIZE;
	if (pcasted.x > data->width || pcasted.y > data->height)
		return (0);
	else if (data->map[pcasted.y][pcasted.x] == '1')
		return (1);
	else if (data->map[pcasted.y][pcasted.x] == '2')
		return (2);
	else if (data->map[pcasted.y][pcasted.x] == 'F')
		if (p.x % BLOCKSIZE >= ft_abs(CHEST_SIZE - BLOCKSIZE) / 2 && p.x % BLOCKSIZE <= (BLOCKSIZE - CHEST_SIZE))
			if (p.y % BLOCKSIZE >= ft_abs(CHEST_SIZE - BLOCKSIZE) / 2 && p.y % BLOCKSIZE <= (BLOCKSIZE - CHEST_SIZE))
				return (3);
	return (0);
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

void	check_collision(t_cub3data *data, double x, double y)
{
	int			i;
	int			j;
	t_coords	player_abroad[4];

	player_abroad[0].x = data->player.pos.x + PLAYER_SIZE + x * PLAYER_SIZE / 2;
	player_abroad[0].y = data->player.pos.y + y * PLAYER_SIZE / 2;
	player_abroad[1].x = data->player.pos.x - PLAYER_SIZE + x * PLAYER_SIZE / 2;
	player_abroad[1].y = data->player.pos.y + y * PLAYER_SIZE / 2;
	player_abroad[2].x = data->player.pos.x + x * PLAYER_SIZE / 2;
	player_abroad[2].y = data->player.pos.y + PLAYER_SIZE + y * PLAYER_SIZE / 2;
	player_abroad[3].x = data->player.pos.x + x * PLAYER_SIZE / 2;
	player_abroad[3].y = data->player.pos.y - PLAYER_SIZE + y * PLAYER_SIZE / 2;
	i = -1;
	while (++i < 4)
	{
		j = ft_iswall(player_abroad[i], data);
		if (j == 1 || (j == 2 && data->door_open == 0))
			return;
		else if (j == 3)
			return (finish(data));
	}
	data->player.pos.x += x * PLAYER_SIZE / 2;
	data->player.pos.y += y * PLAYER_SIZE / 2;
	draw_minimap(data);
	ufo_rays(data, data->player.ray_img, data->player.orientation, data->color.golden);
	if (j == 2)
		data->pass_door = 1;
}

mlx_image_t	*create_imgtext(t_cub3data *data, char *file, int x, int y)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(file);
	if (!texture)
		img_failure(data);
	img = mlx_texture_to_image(data->mlx, texture);
	if (mlx_image_to_window(data->mlx, img, x, y) == -1)
		img_failure(data);
	mlx_delete_texture(texture);
	return (img);
}
