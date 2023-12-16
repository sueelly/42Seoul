/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:46:58 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/04 18:44:53 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"

# define SET_ERROR "Only can use Julia, Mandelbrot and burning ship.\n"
# define ARG_ERROR "Wrong number of argument.\n"
# define C_RANGE "-2 <= c && c <= 2"
# define FUNCTION_GUIDE "You can move screen with arrow keys,\n\
change color with R, G, B,\n\
exit program with ESC,\n\
and zoom screen with mouse scroll.\n"

# define SIZE 2
# define X_SIZE 1000
# define Y_SIZE 1000

# define MANDELBROT 'm'
# define JULIA 'j'
# define BURNING_SHIP 'b'

# define TITLE "fractol"

# define RANGE1 33
# define RANGE2 66
# define LIMIT 100

# define COLOR1 0x00111133
# define COLOR2 0x00336666
# define COLOR3 0x00991129
# define WHITE 0x00000000
# define COLOR_NOISE 10

# define ZOOM 0.1
# define ZOOM_IN 4
# define ZOOM_OUT 5

# define MOVE 50

# define XBUTTON 17
# define RED 15
# define GREEN 5
# define BLUE 11
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126

typedef struct s_complex_plane
{
	int		plane[X_SIZE][Y_SIZE];
	char	set;
	double	c[2];
	double	min_x;
	double	x_len;
	double	max_y;
	double	y_len;
	double	dx;
	double	dy;
	int		color_change;
}		t_complex_plane;

typedef struct s_image
{
	void	*img_ptr;
	char	*image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_vars
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_image			*image;
	t_complex_plane	*complex_plane;
}		t_vars;

void	image_update(t_vars *vars);
void	mandelbrot(t_complex_plane *plane);
void	julia(t_complex_plane *plane);
void	burning_ship(t_complex_plane *plane);
int		key_hook(int keycode, void *param);
int		mouse_hook(int button, int x, int y, void *param);
int		close_window(t_vars *vars);
int		ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
void	ft_error(const char *error_msg);
double	ft_atod(char *str);

#endif