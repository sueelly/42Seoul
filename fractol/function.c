/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:56:46 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/04 17:49:09 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_vars *vars)
{
	mlx_clear_window(vars -> mlx_ptr, vars -> win_ptr);
	mlx_destroy_window(vars -> mlx_ptr, vars -> win_ptr);
	exit (0);
	return (0);
}

void	move_screen(int keycode, t_complex_plane *complex_plane)
{
	if (keycode == UP)
		complex_plane -> max_y += complex_plane -> dy * MOVE;
	else if (keycode == DOWN)
		complex_plane -> max_y -= complex_plane -> dy * MOVE;
	else if (keycode == LEFT)
		complex_plane -> min_x -= complex_plane -> dx * MOVE;
	else
		complex_plane -> min_x += complex_plane -> dx * MOVE;
}

void	color_change(int keycode, t_complex_plane *complex_plane)
{
	if (keycode == RED)
		complex_plane -> color_change += 0x10 << 16;
	else if (keycode == GREEN)
		complex_plane -> color_change += 0x10 << 8;
	else
		complex_plane -> color_change += 0x10;
}

int	key_hook(int keycode, void *param)
{
	if (keycode == ESC)
		close_window(param);
	else if (keycode >= LEFT && keycode <= UP)
		move_screen(keycode, ((t_vars *)param)-> complex_plane);
	else if (keycode == RED || keycode == GREEN || keycode == BLUE)
		color_change(keycode, ((t_vars *)param)-> complex_plane);
	image_update(param);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	int				sign;
	t_complex_plane	*plane;

	if (button != ZOOM_IN && button != ZOOM_OUT)
		return (-1);
	if (button == ZOOM_IN)
		sign = 1;
	else
		sign = -1;
	plane = ((t_vars *)param)-> complex_plane;
	plane -> min_x -= sign * plane -> dx * ZOOM * x;
	plane -> x_len *= 1 + sign * ZOOM;
	plane -> dx *= 1 + sign * ZOOM;
	plane -> max_y += sign * plane -> dy * ZOOM * y;
	plane -> y_len *= 1 + sign * ZOOM;
	plane -> dy *= 1 + sign * ZOOM;
	image_update(param);
	return (0);
}
