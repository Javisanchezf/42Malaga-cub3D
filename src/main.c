/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/17 17:58:49 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_leaks(void)
{
	system("leaks -q cub3D");
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
	map_construct(&data);
	mlx_loop_hook(data.mlx, &keyboard_hooks, (void *)&data);
	mlx_loop_hook(data.mlx, &time_hook, (void *)&data);
	// mlx_loop_hook(data.mlx, &close_door_hook, (void *)&data);
	mlx_loop(data.mlx);
	final_cleaner(&data);
	return (EXIT_SUCCESS);
}
