/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hooks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:38:47 by javiersa          #+#    #+#             */
/*   Updated: 2023/11/08 19:50:10 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_cursor_hook(double x2, double y2, void *param)
{
	t_cub3data		*data;
	static double	x1 = 0;
	static int		i = 0;

	data = param;
	i++;
	if (!data->cursor_hook || i < 2 || data->pause == 1)
		return ;
	i = 0;
	ft_redraw(data, (x2 - x1) * 0.001745);
	x1 = x2;
	(void)y2;
}
