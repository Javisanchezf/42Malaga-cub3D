/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ufo_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:09:33 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/26 12:09:36 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw_ufo_rays(t_cub3data *data, mlx_image_t *img, double angle)
{
	t_coords	p;
	double		i;
	int			t;

	ft_memset(img->pixels, 0, img->width * 4 * img->height);
	i = 175;
	while (i < 185)
	{
		t = 1;
		p.x = img->width / 2 + t * cos(angle + i * PI / 180);
		p.y = img->height / 2 + t * sin(angle + i * PI / 180);
		while (p.x >= 0 && p.y >= 0 && p.x < (int) img->width && p.y < \
		(int)img->height && ++t)
		{
			if (data->minimap->pixels[p.y * img->width * 4 + p.x * 4] != \
27 || data->minimap->pixels[p.y * img->width * 4 + p.x * 4 + 3] == 0)
				break ;
			put_rgbcolor(&img->pixels[p.y * img->width * 4 + p.x * 4], \
data->color.golden, 0);
			p.x = img->width / 2 + t * cos(angle + i * PI / 180);
			p.y = img->height / 2 + t * sin(angle + i * PI / 180);
		}
		i += 0.2;
	}
}
