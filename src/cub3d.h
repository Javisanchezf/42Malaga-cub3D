/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:36:05 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/14 12:25:00 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1920
# define HEIGHT 1024
# define MINIMAP_WIDTH 400
# define MINIMAP_HEIGHT 400
# define PLAYER_SIZE 16
# define CHEST_SIZE 60
# define BLOCKSIZE 130
# define PI 3.141592653589793

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

typedef struct s_coords
{
	int	x;
	int	y;
}		t_coords;

typedef struct s_pixels
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
}		t_pixels;

typedef struct s_colors
{
	t_pixels	white;
	t_pixels	gray;
	t_pixels	blue;
	t_pixels	green;
	t_pixels	golden;
}		t_colors;

typedef struct s_img
{
	mlx_image_t	*img;
	int			width;
	int			rwidth;
	int			height;
}		t_img;

typedef struct s_falseimg
{
	uint8_t		*img;
	int			width;
	int			rwidth;
	int			height;
}		t_falseimg;

typedef struct s_player
{
	t_coords		pos;
	double			orientation;
	mlx_texture_t	*texture;
	t_img			img;
	t_img			ray_img;
}		t_player;

typedef struct s_cub3data
{
	char			*ids[6];
	int				map_width;
	int				map_height;
	char			**map;
	mlx_t			*mlx;
	t_player		player;
	t_colors		color;
	t_falseimg		minimap;
	t_img			minimapfixed;
	mlx_image_t		*time;
	mlx_texture_t	*chest_tex;
	mlx_image_t		*chest_i;
	int				time_counter;

	mlx_texture_t	*galaxy_tex;
	mlx_image_t		*galaxy_i;
	mlx_texture_t	*victory_tex;
	mlx_image_t		*victory_i;
	bool			finish;

}					t_cub3data;

char	*ft_ids_parse(int fd, t_cub3data *data, char *line);
void	ft_parse_data(char *file, t_cub3data	*data);
void	ft_map_parse(t_cub3data *data);
void	initial_cleaner(t_cub3data	*data);
void	minimap(t_cub3data	*data);
void	draw_minimapfixed(t_cub3data *data);
void	init_values(t_cub3data	*data);
void	init_images(t_cub3data *data);
void	converttocircle(t_img *image, int radius);
void	draw_minimapfixed(t_cub3data *data);
void	ufo_rays(t_cub3data *data, t_img *img, double angle, t_pixels color);
int		ft_iswall(t_coords p, t_cub3data *data);
void	final_cleaner(t_cub3data *data);

#endif