/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/11/08 19:52:51 by antdelga         ###   ########.fr       */
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

	ft_printf("%s", &(HEADER));
	if (narg != 2 || !argv[1])
		ft_error("Error: Invalid number of arguments", 0);
	init_values(&data);
	ft_parse_data(argv[1], &data);
	init_images(&data);
	map_construct(&data);
	mlx_loop_hook(data.mlx, &ft_keyboard_hooks, (void *)&data);
	mlx_loop_hook(data.mlx, &ft_time_hook, (void *)&data);
	mlx_cursor_hook(data.mlx, &ft_cursor_hook, (void *)&data);
	mlx_loop(data.mlx);
	ft_final_cleaner(&data);
	return (EXIT_SUCCESS);
}
