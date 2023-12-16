/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 22:36:15 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/04 18:56:17 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	fill_pixels(t_image *image, t_complex_plane *plane)
{
	int		x;
	int		y;
	int		n;
	int		color;

	y = -1;
	while (++y < Y_SIZE)
	{
		x = -1;
		while (++x < X_SIZE)
		{
			n = plane -> plane[y][x];
			if (plane -> plane[y][x] < RANGE1)
				color = COLOR1 + n * COLOR_NOISE + plane -> color_change;
			else if (plane -> plane[y][x] < RANGE2)
				color = COLOR2 + n * COLOR_NOISE + plane -> color_change;
			else if (plane -> plane[y][x] < LIMIT)
				color = COLOR3 + n * COLOR_NOISE + plane -> color_change;
			else
				color = WHITE;
			*((unsigned int *)(image->image + y * image->size_line + \
			x * image->bits_per_pixel / 8)) = (unsigned int)color;
		}
	}
}

void	image_update(t_vars *vars)
{
	t_complex_plane	*plane;

	plane = vars -> complex_plane;
	if (plane -> set == JULIA)
		julia(plane);
	else if (plane -> set == MANDELBROT)
		mandelbrot(plane);
	else
		burning_ship(plane);
	fill_pixels(vars -> image, plane);
	mlx_put_image_to_window(\
	vars -> mlx_ptr, vars -> win_ptr, vars -> image -> img_ptr, 0, 0);
}
