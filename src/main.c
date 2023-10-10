/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:35:28 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/10 17:52:30 by javiersa         ###   ########.fr       */
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
}

void	put_rgb(uint8_t *pixels, t_pixels color)
{
	pixels[0] = color.r;
	pixels[1] = color.g;
	pixels[2] = color.b;
	pixels[3] = color.a;
}

void	drawSquare(t_cub3data *data, t_coords p, t_pixels color)
{
	int			i;
	int			j;

	p.x *= BLOCKSIZE;
	p.y *= BLOCKSIZE;
	if (p.x < 0)
		p.x = 0;
	if (p.y < 0)
		p.y = 0;
	if (p.x + BLOCKSIZE > data->map_width * BLOCKSIZE)
		p.x = data->map_width * BLOCKSIZE - BLOCKSIZE;
	if (p.y + BLOCKSIZE > data->map_height * BLOCKSIZE)
		p.y = data->map_height * BLOCKSIZE - BLOCKSIZE;
	i = p.y - 1;
	while (++i < p.y + BLOCKSIZE)
	{
		j = p.x - 1;
		while (++j < p.x + BLOCKSIZE)
			put_rgb(&(data->img->pixels[(i * data->map_width * BLOCKSIZE + j) * 4]), color);
	}
}

void	drawCircle(t_cub3data *data, t_coords center, t_pixels color)
{
	center.x += BLOCKSIZE;
	center.y += BLOCKSIZE;
	int	radius = BLOCKSIZE / 3;
	int i = center.y - radius - 2;

	while (++i <= center.y + radius)
	{
		int j = center.x - radius - 1;
		while (++j <= center.x + radius)
		{
			int dx = j - center.x;
			int dy = i - center.y;
			double distance = sqrt(dx * dx + dy * dy);
			if (distance <= radius)
			{
				int x = j / BLOCKSIZE;
				int y = i / BLOCKSIZE;
				if (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height)
					put_rgb(&(data->img->pixels[(i * data->map_width * BLOCKSIZE + j) * 4]), color);
			}
		}
    }
}


void	draw_minimap(t_cub3data	*data)
{
	t_coords	p;

	p.y = -1;
	while (data->map[++p.y])
	{
		p.x = -1;
		while (data->map[p.y][++p.x])
		{
			if (data->map[p.y][p.x] == '1')
				drawSquare(data, p, data->color1);
			else if (data->map[p.y][p.x] == '0' || data->map[p.y][p.x] == 'N' \
|| data->map[p.y][p.x] == 'S' || data->map[p.y][p.x] == 'W' || data->map[p.y][p.x] == 'E')
				drawSquare(data, p, data->color2);
		}
	}
	drawCircle(data, data->player_pos, data->color3);
}

void	init_window(t_cub3data	*data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D 42", true);
	if (!data->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}

	data->img = mlx_new_image(data->mlx, data->map_width * BLOCKSIZE, data->map_height * BLOCKSIZE);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
		exit(EXIT_FAILURE);
	}
	ft_memset(data->img->pixels, 200, data->map_width * data->map_height * BLOCKSIZE * BLOCKSIZE * sizeof(int));
	draw_minimap(data);

	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		cleaner(data);
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
	return (EXIT_SUCCESS);
}
