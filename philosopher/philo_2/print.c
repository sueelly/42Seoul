/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:29:06 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/22 06:58:18 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	print_log(t_philo *philo, int philo_n, char *msg)
{
	long	current_time;
	int		print;

	print = 1;
	current_time = get_time_ms() - philo->start_time;
	pthread_mutex_lock(philo->death_mutex);
	if (philo->death && ft_strlen(msg) != 4)
		print = 0;
	pthread_mutex_unlock(philo->death_mutex);
	pthread_mutex_lock(philo->print_mutex);
	if (print)
		printf("%ld %d %s\n", current_time, philo_n, msg);
	pthread_mutex_unlock(philo->print_mutex);
	if (philo->death)
		return (0);
	return (1);
}

int	print_error(char *msg)
{
	return (write(2, msg, ft_strlen(msg)));
}
