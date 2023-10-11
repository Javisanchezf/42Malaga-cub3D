/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/11 13:52:30 by javiersa         ###   ########.fr       */
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
	data->color3.r = 212;
	data->color3.g = 175;
	data->color3.b = 55;
	data->color3.a = 255;
}

void	printfdata(t_cub3data	*data)
{
	int	i;

	i = -1;
	while (++i < 6)
		ft_printf("ID Nº%d: %s", i, data->ids[i]);
	ft_printf("\nWidth of map: %d | Height of map: %d | Position person: %d,%d\n\n", data->map_width, data->map_height,data->player_pos.x, data->player_pos.y);
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		;
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
	data.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D 42", true);
	if (!data.mlx)
	{
		puts(mlx_strerror(mlx_errno));
		cleaner(&data);
		exit(EXIT_FAILURE);
	}
	minimap(&data);

	mlx_loop_hook(data.mlx, &keyboard_hooks, (void *)&data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.minimap.img);
	mlx_terminate(data.mlx);

	cleaner(&data);
	return (EXIT_SUCCESS);
}
