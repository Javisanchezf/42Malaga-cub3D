/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/14 12:13:26 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_leaks(void)
{
	system("leaks -q cub3D");
}

void	finish(t_cub3data *data)
{
	data->finish = 1;
	data->player.img.img->enabled = 0;
	data->galaxy_i->enabled = 0;
	data->chest_i->enabled = 0;
	data->minimapfixed.img->enabled = 0;
	data->player.ray_img.img->enabled = 0;
	data->time->instances->x = WIDTH / 2 - 30;
	data->time->instances->y = HEIGHT / 2;
	data->victory_i->enabled = 1;
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
		if (j == 1)
			return;
		else if (j == 3)
			return (finish(data));
	}
	data->player.pos.x += x * PLAYER_SIZE / 2;
	data->player.pos.y += y * PLAYER_SIZE / 2;
	draw_minimapfixed(data);
	ufo_rays(data, &data->player.ray_img, data->player.orientation, data->color.golden);
}

void	keyboard_hooks(void *param)
{
	t_cub3data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (data->finish == 1)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		check_collision(data, cos(data->player.orientation + PI),
				sin(data->player.orientation + PI));
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		check_collision(data, cos(data->player.orientation),
				sin(data->player.orientation));
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		check_collision(data, sin(data->player.orientation + PI),
				-cos(data->player.orientation + PI));
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		check_collision(data, sin(data->player.orientation),
				-cos(data->player.orientation));
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.orientation -= 10 * 0.01745;
		ufo_rays(data, &data->player.ray_img, data->player.orientation, data->color.golden);
		data->galaxy_i->instances->x-=50;
		if (data->galaxy_i->instances->x < (int32_t)(1920 - data->galaxy_i->width))
			data->galaxy_i->instances->x = 0;

	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.orientation += 10 * 0.01745;
		ufo_rays(data, &data->player.ray_img, data->player.orientation, data->color.golden);
		data->galaxy_i->instances->x+=50;
		if (data->galaxy_i->instances->x > 0)
			data->galaxy_i->instances->x = 1920 - data->galaxy_i->width;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_0))
	{
		if (data->galaxy_i->enabled == 0)
			data->galaxy_i->enabled = 1;
		else if (data->galaxy_i->enabled == 1)
			data->galaxy_i->enabled = 0;
	}
}

void	time_hook(void *param)
{
	t_cub3data	*data;
	char		*str;

	data = param;
	if (data->finish == 1)
		return ;
	data->time_counter++;
	mlx_delete_image(data->mlx, data->time);
	str = ft_freeandjoin(ft_strdup("TIME: "), ft_itoa(data->time_counter
				/ 100));
	str = ft_freeandjoin(str, ft_strdup("."));
	str = ft_freeandjoin(str, ft_itoa(data->time_counter % 100));
	data->time = mlx_put_string(data->mlx, str, WIDTH - MINIMAP_WIDTH / 2 - 40,
			MINIMAP_HEIGHT + 10);
	ft_free_and_null((void **)&str);
}

int32_t	main(int narg, char **argv)
{
	t_cub3data	data;

	atexit(ft_leaks);
	ft_printf("%s", &(HEADER));
	if (narg != 2 || !argv[1])
		ft_error("Error: Invalid number of arguments", 0);
	init_values(&data);
	ft_parse_data(argv[1], &data);
	init_images(&data);
	minimap(&data);
	mlx_loop_hook(data.mlx, &keyboard_hooks, (void *)&data);
	mlx_loop_hook(data.mlx, &time_hook, (void *)&data);
	mlx_loop(data.mlx);
	final_cleaner(&data);
	return (EXIT_SUCCESS);
}
