/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:36:05 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/05 22:06:23 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1920
# define HEIGHT 1024
# define MINIMAP_WIDTH 300
# define MINIMAP_HEIGHT 300
# define BLOCKSIZE 60

/*----------------------------HEADER----------------------------*/

# define HEADER ("\n\033[34;1m\
		 ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ \n\
		██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n\
		██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n\
		██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n\
		╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n\
		 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ \n\
\n\
		 A simple FPS project implemented in C\n\
		                 By\n\
		        --- javiersa && ?? ---\n\
\n\033[0m")

/*----------------------------COLORS----------------------------*/
# define BOLD		"\033[1m"
# define BLACK		"\033[30;1m"
# define RED		"\033[31;1m"
# define GREEN		"\033[32;1m"
# define YELLOW		"\033[33;1m"
# define BLUE		"\033[34;1m"
# define MAGENTA	"\033[35;1m"
# define CYAN		"\033[36;1m"
# define WHITE		"\033[37;1m"
# define DEFAULT	"\033[0m"

/*----------------------------LIBRARIES----------------------------*/
# include "../libftplus/libftplus.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <math.h>

/*----------------------------STRUCTS----------------------------*/

typedef struct s_cub3data
{
	char		*ids[6];
	int			map_width;
	int			map_height;
	char		**map;
	mlx_t		*mlx;
	int			x_person;
	int			y_person;

	mlx_image_t	*img;
	mlx_image_t	*menu;
	int			window_width;
	int			window_height;
	int			z_max;
	int			zoom;
	float		z_zoom;
	float		x_zoom;
	double		radians;
	double		radians2;
	char		view;
}					t_cub3data;

char	*ft_ids_parse(int fd, t_cub3data *data, char *line);
void	ft_parse_data(char *file, t_cub3data	*data);
void	ft_map_parse(t_cub3data *data);
void	cleaner(t_cub3data	*data);


#endif