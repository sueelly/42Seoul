/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:09:55 by haejokim          #+#    #+#             */
/*   Updated: 2023/10/20 00:46:18 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	ft_atoi(const char *str)
{
	long long	n;
	int			sign;
	int			i;

	n = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	if ((str[i] < '0') || (str[i] > '9'))
		return (0);
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n * sign);
}

void	ft_putnbr_fd_recursive(long long n, int fd)
{
	char	c;

	if (n / 10)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd_recursive((long long)n * -1, fd);
	}
	else
		ft_putnbr_fd_recursive(n, fd);
}
