/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:05:58 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/18 18:06:08 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*create_imgtext(t_cub3data *data, char *file, int x, int y)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(file);
	if (!texture)
		img_failure(data);
	img = mlx_texture_to_image(data->mlx, texture);
	if (mlx_image_to_window(data->mlx, img, x, y) == -1)
		img_failure(data);
	mlx_delete_texture(texture);
	return (img);
}

void	put_rgbcolor(uint8_t *pixels, t_pixels color, bool random)
{
	pixels[0] = color.r;
	pixels[1] = color.g;
	pixels[2] = color.b;
	pixels[3] = color.a;
	if (random)
		pixels[3] = rand() % 106 + 150;
}

void	put_rgbimg(uint8_t *dest, uint8_t *or)
{
	dest[0] = or[0];
	dest[1] = or[1];
	dest[2] = or[2];
	dest[3] = or[3];
}