/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:13:53 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/04 17:27:26 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (!s1[i])
		return (0);
	return (1);
}

int	ft_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_error(const char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
	exit(1);
}

double	ft_atod(char *str)
{
	int		i;
	int		sign;
	double	n;

	if (!*str)
		ft_error(SET_ERROR);
	i = 0;
	sign = 1;
	n = 0;
	if (str[i] == '-' && ++i)
		sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + str[i++] - '0';
	if (!str[i])
		return (n);
	if (str[i] != '.')
		ft_error(SET_ERROR);
	str = &str[i + 1];
	i = 1;
	while (*str >= '0' && *str <= '9')
		n += (*(str++) - '0') * pow(0.1, i++);
	if (*str)
		ft_error(ARG_ERROR);
	return (sign * n);
}
