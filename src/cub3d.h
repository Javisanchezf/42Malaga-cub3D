/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:36:05 by javiersa          #+#    #+#             */
/*   Updated: 2023/10/18 18:24:09 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1980
# define HEIGHT 1024
# define MINIMAP_SIZE 400
# define PLAYER_SIZE 16
# define CHEST_SIZE 60
# define BLOCKSIZE 200
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
# include <math.h>
# include <stdio.h>

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
	t_pixels	red;
}		t_colors;

typedef struct s_falseimg
{
	uint8_t		*img;
	int			width;
	int			rwidth;
	int			height;
}		t_falseimg;

typedef struct s_player
{
	t_coords			pos;
	double				orientation;
	mlx_texture_t		*texture;
	mlx_image_t			*img;
	mlx_image_t			*ray_img;
}		t_player;

typedef struct s_cub3data
{
	char			*ids[6];
	char			**map;
	int				width;
	int				height;

	t_falseimg		map_close;
	t_falseimg		map_open;
	bool			door_open;
	bool			pass_door;

	t_player		player;
	mlx_image_t		*minimap;

	mlx_image_t		*time;
	int				open_coldown;
	int				time_counter;

	mlx_image_t		*chest_i;
	mlx_image_t		*galaxy_i;
	mlx_image_t		*victory_i;

	int				*distances;

	mlx_t			*mlx;
	mlx_image_t		*full_img;

	t_colors		color;
	bool			finish;
}					t_cub3data;

/*----------------------------PARSE FUNCTIONS----------------------------*/

char		*ft_ids_parse(int fd, t_cub3data *data, char *line);
void		ft_parse_data(char *file, t_cub3data	*data);
void		ft_map_parse(t_cub3data *data);
void		map_construct(t_cub3data	*data);

/*----------------------------INIT FUNCTIONS----------------------------*/

void		init_values(t_cub3data	*data);
void		init_images(t_cub3data *data);

/*----------------------------CLEANER FUNCTIONS----------------------------*/

void		initial_cleaner(t_cub3data	*data);
void		final_cleaner(t_cub3data *data);
void		img_failure(t_cub3data *data);

/*----------------------------UTILS FUNCTIONS----------------------------*/

int			ft_iswall(t_coords p, t_cub3data *data);
void		check_collision(t_cub3data *data, t_coords pos, double x, double y);
void		put_rgbcolor(uint8_t *pixels, t_pixels color, bool random);
void		put_rgbimg(uint8_t *dest, uint8_t *or);

/*----------------------------HOOKS FUNCTIONS----------------------------*/
void		keyboard_hooks(void *param);
void		time_hook(void *param);
void		close_door_hook(void *param);
void		time_hook2(void *param);

/*----------------------------? FUNCTIONS----------------------------*/

void		draw_minimap(t_cub3data *data);
void		ufo_rays(t_cub3data *data, mlx_image_t *img, double angle);
mlx_image_t	*create_imgtext(t_cub3data *data, char *file, int x, int y);
int			ft_isabroadwall(t_coords p, int radius, t_cub3data *data);

/*------------------------RAYCASTING FUNCTIONS------------------------*/
void		raycasting(t_cub3data *data, t_coords pos);

#endif