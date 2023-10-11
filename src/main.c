/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/11 21:22:07 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleaner(t_cub3data	*data)
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

void	keyboard_hooks(void *param)
{
	t_cub3data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->player.pos.y--;
		draw_minimapfixed(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player.pos.y++;
		draw_minimapfixed(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player.pos.x--;
		draw_minimapfixed(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player.pos.x++;
		draw_minimapfixed(data);
	}
}

int32_t	main(int narg, char **argv)
{
	t_cub3data	data;

	atexit(ft_leaks);
	ft_printf("%s", &(HEADER));
	if (narg != 2 || !argv[1])
		ft_error ("Error: Invalid number of arguments", 0);
	init_values(&data);
	ft_parse_data(argv[1], &data);
	init_images(&data);
	minimap(&data);

	mlx_loop_hook(data.mlx, &keyboard_hooks, (void *)&data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.minimap.img);
	mlx_terminate(data.mlx);

	cleaner(&data);
	return (EXIT_SUCCESS);
}
