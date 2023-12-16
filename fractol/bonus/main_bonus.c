/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 22:20:22 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/04 18:56:22 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	init_complex_plane(\
t_complex_plane *complex_plane, int argc, char *argv[])
{
	complex_plane -> min_x = -SIZE;
	complex_plane -> x_len = 2 * SIZE;
	complex_plane -> max_y = SIZE;
	complex_plane -> y_len = 2 * SIZE;
	complex_plane -> dx = (double)SIZE * 2 / X_SIZE;
	complex_plane -> dy = (double)SIZE * 2 / Y_SIZE;
	complex_plane -> color_change = 0;
	if (argc == 2 && !ft_strcmp("burning ship", argv[1]))
			complex_plane -> set = BURNING_SHIP;
	else if (argc == 2 && !ft_strcmp("mandelbrot", argv[1]))
		complex_plane -> set = MANDELBROT;
	else if (argc == 4 && !ft_strcmp("julia", argv[1]))
	{
		complex_plane -> set = JULIA;
		complex_plane -> c[0] = ft_atod(argv[2]);
		complex_plane -> c[1] = ft_atod(argv[3]);
		if (fabs(complex_plane -> c[0]) > 2 || fabs(complex_plane -> c[1]) > 2)
			ft_error(C_RANGE);
	}
	else if (argc == 2 || argc == 4)
		ft_error(SET_ERROR);
	else
		ft_error(ARG_ERROR);
}

int	main(int argc, char **argv)
{
	t_complex_plane	complex_plane;
	t_image			image;
	t_vars			vars;

	init_complex_plane(&complex_plane, argc, argv);
	vars.complex_plane = &complex_plane;
	vars.mlx_ptr = mlx_init();
	if (!vars.mlx_ptr)
		exit(1);
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, X_SIZE, Y_SIZE, TITLE);
	if (!vars.win_ptr)
		exit(1);
	image.img_ptr = mlx_new_image(vars.mlx_ptr, X_SIZE, Y_SIZE);
	if (!image.img_ptr)
		exit(1);
	image.image = mlx_get_data_addr(\
	image.img_ptr, &image.bits_per_pixel, &image.size_line, &image.endian);
	vars.image = &image;
	image_update(&vars);
	mlx_key_hook(vars.win_ptr, key_hook, &vars);
	mlx_mouse_hook(vars.win_ptr, mouse_hook, &vars);
	mlx_hook(vars.win_ptr, XBUTTON, 0, close_window, &vars);
	write(1, FUNCTION_GUIDE, ft_strlen(FUNCTION_GUIDE));
	mlx_loop(vars.mlx_ptr);
	return (0);
}
