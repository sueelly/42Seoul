/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 22:35:41 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/04 18:45:24 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_n(double z[2], double c[2], int burning_ship)
{
	int		n;
	double	temp;

	n = -1;
	while (z[0] * z[0] + z[1] * z[1] < 4 && ++n < LIMIT)
	{
		temp = z[0] * z[0] - z[1] * z[1] + c[0];
		if (!burning_ship)
			z[1] = 2.0 * z[0] * z[1] + c[1];
		else
			z[1] = 2.0 * fabs(z[0] * z[1]) + c[1];
		z[0] = temp;
	}
	return (n);
}

void	mandelbrot(t_complex_plane *plane)
{
	int		x;
	int		y;
	double	z[2];

	y = -1;
	while (++y < Y_SIZE)
	{
		x = -1;
		while (++x < X_SIZE)
		{
			plane -> c[0] = plane -> min_x + x * plane -> dx;
			plane -> c[1] = plane -> max_y - y * plane -> dy;
			z[0] = 0;
			z[1] = 0;
			plane -> plane[y][x] = get_n(z, plane -> c, 0);
		}
	}
}

void	julia(t_complex_plane *plane)
{
	int		x;
	int		y;
	double	z[2];

	y = -1;
	while (++y < Y_SIZE)
	{
		x = -1;
		while (++x < X_SIZE)
		{
			z[0] = plane -> min_x + x * plane -> dx;
			z[1] = plane -> max_y - y * plane -> dy;
			plane -> plane[y][x] = get_n(z, plane -> c, 0);
		}
	}
}

void	burning_ship(t_complex_plane *plane)
{
	int		x;
	int		y;
	double	z[2];

	y = -1;
	while (++y < Y_SIZE)
	{
		x = -1;
		while (++x < X_SIZE)
		{
			plane -> c[0] = plane -> min_x + x * plane -> dx;
			plane -> c[1] = plane -> max_y - y * plane -> dy;
			z[0] = 0;
			z[1] = 0;
			plane -> plane[y][x] = get_n(z, plane -> c, 1);
		}
	}
}
