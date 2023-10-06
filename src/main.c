/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/06 20:13:16 by javiersa         ###   ########.fr       */
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

void	init(t_cub3data	*data)
{
	int	i;

	i = -1;
	while (++i < 6)
		data->ids[i] = NULL;
	data->map_width = 0;
	data->color1.r = 255;
	data->color1.g = 255;
	data->color1.b = 255;
	data->color1.a = 255;
	data->color2.r = 125;
	data->color2.g = 125;
	data->color2.b = 125;
	data->color2.a = 255;
}

void	printfdata(t_cub3data	*data)
{
	int	i;

	i = -1;
	while (++i < 6)
		ft_printf("ID Nº%d: %s", i, data->ids[i]);
	ft_printf("\nWidth of map: %d | Height of map: %d | Position person: %d,%d\n\n", data->map_width, data->map_height,data->person_pos.x, data->person_pos.y);
	i = -1;
	while (data->map[++i])
		ft_printf("Line %d (Size %d) : %s\n", i, ft_strlen(data->map[i]), data->map[i]);
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
}

void	put_rgb(uint8_t *pixels, t_pixels color)
{
	pixels[0] = color.r;
	pixels[1] = color.g;
	pixels[2] = color.b;
	pixels[3] = color.a;
}

void	drawSquare(uint8_t *pixels, int x, int y, t_pixels color)
{
	int	startx;
	int	starty;
	int	index;
	int	i;
	int	j;

	startx = x - BLOCKSIZE / 2;
	starty = y - BLOCKSIZE / 2;
	if (startx < 0)
		startx = 0;
	if (starty < 0)
		starty = 0;
	if (startx + BLOCKSIZE > MINIMAP_WIDTH)
		startx = WIDTH - BLOCKSIZE;
	if (starty + BLOCKSIZE > MINIMAP_HEIGHT)
		starty = MINIMAP_HEIGHT - BLOCKSIZE;
	i = starty - 1;
	while (++i < starty + BLOCKSIZE)
	{
		j = startx - 1;
		while (++j < startx + BLOCKSIZE)
		{
			index = (i * MINIMAP_WIDTH + j) * 4;
			put_rgb(&pixels[index], color);
		}
	}
}

// void	draw_minimap(t_cub3data	*data)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	data->minimap = ft_calloc(4 * data->map_width * data->map_height * BLOCKSIZE);
// 	while (data->map[++i])
// 	{
// 		j = -1;
// 		while (data->map[i][++j])
// 		{
// 			if (data->map[i][j] == '1')
// 				drawSquare(data->minimap);
// 			else if (data->map[i][j] == '0')
// 				put_rgb(data->minimap[4 * i * j], 125, 125, 125);
// 		}
// 	}
// }

void	init_window(t_cub3data	*data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D 42", true);
	if (!data->mlx)
	{
		cleaner(data);
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	data->img = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}
	ft_memset(data->img->pixels, 142, MINIMAP_WIDTH * MINIMAP_HEIGHT * sizeof(int));
	drawSquare(data->img->pixels, MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2, data->color1);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	mlx_loop_hook(data->mlx, &keyboard_hooks, (void *)data);
	mlx_loop(data->mlx);
}

int32_t	main(int narg, char **argv)
{
	t_cub3data	data;

	if (narg != 2 || !argv[1])
		ft_error ("Error: Invalid number of arguments", 0);
	atexit(ft_leaks);
	init(&data);
	ft_parse_data(argv[1], &data);
	ft_printf("%s", &(HEADER));
	printfdata(&data);

	init_window(&data);

	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx);

	cleaner(&data);
	// ft_free_and_null((void **)&data.minimap);
	return (EXIT_SUCCESS);
}
