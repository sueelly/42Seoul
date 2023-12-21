/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:52:40 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/21 22:55:56 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

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

int	print_error(char *msg)
{
	return (write(2, msg, ft_strlen(msg)));
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	print_log(t_philo *philo, int philo_n, char *msg)
{
	long			current_time;

	current_time = get_time_ms() - philo -> start_time;
	pthread_mutex_lock(philo -> death_mutex);
	if (philo -> death)
	{
		pthread_mutex_unlock(philo -> death_mutex);
		if (ft_strlen(msg) == 4)
			printf("%ld %d %s\n", current_time, philo_n, msg);
		return (-1);
	}
	pthread_mutex_unlock(philo -> death_mutex);
	pthread_mutex_lock(philo -> print_mutex);
	printf("%ld %d %s\n", current_time, philo_n, msg);
	pthread_mutex_unlock(philo -> print_mutex);
	return (0);
}
