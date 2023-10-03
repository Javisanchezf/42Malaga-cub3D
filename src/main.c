/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/03 21:36:19 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	init(int narg, char	**argv)
// {
	
// }

void	cleaner(t_cub3data	*data)
{
	int	i;

	i = -1;
	while (++i < 5)
		ft_free_and_null((void **)&data->ids[i]);
}

int32_t	main(int narg, char **argv)
{
	t_cub3data	data;

	if (narg != 2 || !argv[1])
		ft_error ("Error\nInvalid number of arguments", 0);
	// ft_map_construct(argv[1], &fdf);
	ft_map_construct(argv[1], &data);
	ft_printf("%s", &(HEADER));
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
	cleaner(&data);
	return (EXIT_SUCCESS);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// static mlx_image_t* image;

// // -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (int32_t i = 0; i < (int32_t)image->width; ++i)
// 	{
// 		for (int32_t y = 0; y < (int32_t)image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	(void)param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

// // -----------------------------------------------------------------------------

// int32_t	main()
// {
// 	mlx_t* mlx;

// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
	
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }