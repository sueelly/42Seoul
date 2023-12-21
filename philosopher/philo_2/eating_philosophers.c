/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:28:25 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/22 08:23:13 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_pass_time(t_philo *philo, long time)
{
	long int	start;
	long int	now;
	int			death;

	start = get_time_ms();
	death = 0;
	while (!death)
	{
		now = get_time_ms();
		if ((now - start) >= time)
			break ;
		usleep(500); // 너무 많은 자원 소모 안하도록(while 자제) & 순서 겹치지 않도록
		pthread_mutex_lock(philo->death_mutex);
		death = philo->death;
		pthread_mutex_unlock(philo->death_mutex);
	}
}

void	eat_record_update(t_philo *philo, int philo_n)
{
	pthread_mutex_lock(philo->eat_record_mutex);
	philo->hungry_time[philo_n - 1] = get_time_ms();
	pthread_mutex_unlock(philo->eat_record_mutex);
	if (philo->eat_count[philo_n - 1] >= philo->full_eat_count)
	{
		pthread_mutex_unlock(philo->eat_record_mutex);
		return ;
	}
	if (philo->full_eat_count == 0)
		return ;
	philo->eat_count[philo_n - 1]++;
	pthread_mutex_unlock(philo->eat_record_mutex);
	if (philo->eat_count[philo_n - 1] >= philo->full_eat_count)
		philo->full_count++;
	if (philo->full_count >= philo->n)
	{
		pthread_mutex_lock(philo->death_mutex);
		philo->death = 1;
	}
}

int	eat(t_philo *philo, int philo_n)
{
	int	left;
	int	right;

	printf("eat entering: %d %ld\n", philo_n, get_time_ms() - philo->start_time);
	left = philo_n % philo->n;
	right = (philo_n + 1) % philo->n;
	// if (philo_n % 2 == 0 || \
	// (philo->n % 2 == 1 && philo_n == philo->n))
	//  	ft_swap(&left, &right);
	pthread_mutex_lock(philo->forks[left]);
	if (!print_log(philo, philo_n, FORK_MSG))
	{
		pthread_mutex_unlock(philo->forks[left]);
		return (0);
	}
	pthread_mutex_lock(philo->forks[right]);
	if (!print_log(philo, philo_n, FORK_MSG))
		return (0);
	if (!print_log(philo, philo_n, EAT_MSG))
	{
		pthread_mutex_unlock(philo->forks[right]);
		return (0);
	}
	eat_record_update(philo, philo_n);
	//usleep(1000 * philo->time[EAT]);
	ft_pass_time(philo, philo->time[EAT]);
	pthread_mutex_unlock(philo->forks[right]);
	pthread_mutex_unlock(philo->forks[left]);
	return (1);
}

int	ft_sleep(t_philo *philo, int philo_n)
{
	int	n;

	n = print_log(philo, philo_n, SLEEP_MSG);
	//usleep(1000 * philo->time[SLEEP]);
	ft_pass_time(philo, philo->time[SLEEP]);
	return (n);
}

int	think(t_philo *philo, int philo_n)
{
	return (print_log(philo, philo_n, THINK_MSG));
}

void	*eating_philosophers(t_philo *philo)
{
	int	philo_n;

	philo_n = philo->current_philo;
	printf("eating_phil entered: %d %ld\n", philo_n, get_time_ms() - philo->start_time);
	if (philo_n == philo->n || philo_n % 2 == 0)
		usleep(800 * philo->time[EAT]);
	printf("eating start: %d\n", philo_n);
	while (1)
	{
		printf("%d %d\n", philo_n, __LINE__);
		if (!eat(philo, philo_n))
			return (0);
		printf("%d %d\n", philo_n, __LINE__);
		if (!ft_sleep(philo, philo_n))
			return (0);
		printf("%d %d\n", philo_n, __LINE__);
		if (!think(philo, philo_n))
			return (0);
	}
	return (0);
}
