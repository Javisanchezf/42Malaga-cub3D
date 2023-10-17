/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:40:45 by antdelga          #+#    #+#             */
/*   Updated: 2023/10/17 21:28:13 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_array(int	*array)
{
	int	i;

	i = 0;
	while (i < 66*5)
	{
		ft_printf("%d\n", array[i]);
		i++;
	}
	ft_printf("\n");
}

void	picasso(int t, int col, t_cub3data *data)
{
	int	i;
	t_coords	p;

	i = -1;
	col *= (int)round(WIDTH / 512);
	while (++i < HEIGHT)
	{
		if (i < HEIGHT / 2 - t / 2)
			put_rgbcolor(&(data->full_img->pixels[(i * data->full_img->width + col) * 4]), data->color.blue, 0);
		else if (i < HEIGHT / 2 + t / 2)
			put_rgbcolor(&(data->full_img->pixels[(i * data->full_img->width + col) * 4]), data->color.green, 0);
		else
			put_rgbcolor(&(data->full_img->pixels[(i * data->full_img->width + col) * 4]), data->color.red, 0);
	}
	p.y = 0;
	while (++p.y < (int)round(WIDTH / 512) )
	{
		p.x = -1;
		while (++p.x < HEIGHT)
			put_rgbimg(&data->full_img->pixels[(p.x * data->full_img->width + col + p.y) * 4], &data->full_img->pixels[(p.x * data->full_img->width + col) * 4]);
	}
}

void	raycasting(t_cub3data *data, mlx_image_t *img, double angle)
{
	t_coords	p;
	double		iter;
	int			t;

	iter = 0;
	ft_memset(img->pixels, 0, img->width * 4 * img->height);
	while (iter < 64)
	{
		t = 1;
		
		p.x = img->width / 2 + t * cos(angle + (iter + 147) * PI / 180);
		p.y = img->height / 2 + t * sin(angle + (iter + 147) * PI / 180);
		while (p.x >= 0 && p.y >= 0 && p.x < (int) img->width && p.y < (int) img->height && ++t)
		{
			if ((ft_iswall(p, data) == 2 && data->door_open == 0) || ft_iswall(p, data) == 1)
				break;
			p.x = img->width / 2 + t * cos(angle + (iter + 147) * PI / 180);
			p.y = img->height / 2 + t * sin(angle + (iter + 147) * PI / 180);
		}
		picasso(t, (int)round(iter * 8), data);
		iter += 0.125;
	}
}
