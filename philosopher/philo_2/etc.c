/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:29:43 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/22 03:02:38 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	init_fork(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n)
		pthread_mutex_unlock(philo->forks[i]);
}

int	ft_atoi(const char *str)
{
	long long	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str == '\t') || (*str == '\n') || (*str == '\v')
		|| (*str == '\f') || (*str == '\r') || (*str == ' '))
		str++;
	if ((*str == '+') || (*str == '-'))
		if (*str++ == '-')
			sign *= -1;
	if ((*str < '0') || (*str > '9'))
		return (0);
	while ((*str >= '0') && (*str <= '9'))
		n = n * 10 + *str++ - '0';
	while ((*str == '\t') || (*str == '\n') || (*str == '\v')
		|| (*str == '\f') || (*str == '\r') || (*str == ' '))
		str++;
	if (*str)
		return (0);
	return (n * sign);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
