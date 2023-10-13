/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/13 14:06:33 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleaner(t_cub3data *data)
{
	int	i;

	i = -1;
	while (++i < 6)
		ft_free_and_null((void **)&data->ids[i]);
	ft_split_free(data->map);
}

void	ft_leaks(void)
{
	system("leaks -q cub3D");
}

void	check_collision(t_cub3data *data, double x, double y)
{
	int			vx;
	int			vy;
	int			index;
	bool		flag;
	int			i;
	t_coords	player_abroad[4];

	flag = 1;
	player_abroad[0].x = data->player.pos.x + PLAYER_SIZE;
	player_abroad[0].y = data->player.pos.y;
	player_abroad[1].x = data->player.pos.x - PLAYER_SIZE;
	player_abroad[1].y = data->player.pos.y;
	player_abroad[2].x = data->player.pos.x;
	player_abroad[2].y = data->player.pos.y + PLAYER_SIZE;
	player_abroad[3].x = data->player.pos.x;
	player_abroad[3].y = data->player.pos.y - PLAYER_SIZE;
	vx = x * PLAYER_SIZE / 2;
	vy = y * PLAYER_SIZE / 2;
	i = -1;
	while (++i < 4)
	{
		index = ((player_abroad[i].y + vy) * data->minimap.rwidth
				+ (player_abroad[i].x + vx) * 4);
		if (index < 0 || index > data->minimap.height * data->minimap.rwidth)
			return ;
		if (data->minimap.img[index] == 255)
			flag = 0;
	}
	if (flag == 1)
	{
		data->player.pos.x += vx;
		data->player.pos.y += vy;
		draw_minimapfixed(data);
		ufo_rays(data, &data->player.ray_img, data->player.orientation, data->color.golden);
	}
}

void	keyboard_hooks(void *param)
{
	t_cub3data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
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
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.orientation += 10 * 0.01745;
		ufo_rays(data, &data->player.ray_img, data->player.orientation, data->color.golden);
	}
}

void	time_hook(void *param)
{
	t_cub3data	*data;
	char		*str;

	data = param;
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
	mlx_delete_image(data.mlx, data.minimapfixed.img);
	mlx_delete_image(data.mlx, data.time);
	mlx_terminate(data.mlx);
	mlx_delete_texture(data.player.texture);
	ft_free_and_null((void **)&data.minimap.img);
	cleaner(&data);
	return (EXIT_SUCCESS);
}
