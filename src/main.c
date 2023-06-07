/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/07 20:51:27 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	main(int narg, char **argv)
{
	t_cub3data	data;

	if (narg != 2 || !argv[1])
		return (1);
	ft_printf("%s", &(HEADER));
	// ft_map_construct(argv[1], &fdf);
	data.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D - javiersa", true);
	// if (!data.mlx)
	// 	ft_error("MLX INIT FAIL.", 1, data.map);
	// fdf.img = mlx_new_image(fdf.mlx, fdf.window_width, fdf.window_height);
	// if (!fdf.img)
	// 	ft_error("MLX NEW IMAGE FAIL.", 1, fdf.map);
	// ft_picasso(&fdf);
	// if (mlx_image_to_window(fdf.mlx, fdf.img, 
	// ft_w_center(WIDTH, fdf.img->width), ft_w_center(HEIGHT, fdf.img->height)))
	// 	ft_error("MLX IMAGE TO WINDOW FAIL.", 1, fdf.map);
	// ft_menu(&fdf);
	// mlx_loop_hook(fdf.mlx, &keyboard_hooks, (void *)&fdf);
	// mlx_scroll_hook(fdf.mlx, &scroll_hook, (void *)&fdf);
	// mlx_cursor_hook(fdf.mlx, &cursor_hook, (void *)&fdf);
	// mlx_loop(fdf.mlx);
	// ft_multiple_free(1, fdf.map);
	// mlx_delete_image(fdf.mlx, fdf.img);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
