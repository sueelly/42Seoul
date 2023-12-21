/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:24:10 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/22 03:10:27 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_fork(t_philo *philo)
{
	int	i;
	
	i = -1;
	while (++i < philo -> philosophers)
		pthread_mutex_unlock(philo -> forks[i]);
}

void	monitor_thread(t_philo *philo)
{
	int	i;
	int	full;

	while (!philo -> death)
	{
		i = 0;
		full = 0;
		pthread_mutex_lock(philo -> eat_count_mutex);
		while (++i <= philo -> philosophers)
		{
			if (philo -> must_eat_count && philo->eat_count[i - 1] >= philo\
			->must_eat_count)
				full++;
			if (full == philo->philosophers || (philo->hungry_time[i - 1] && get_time_ms() - \
			philo->hungry_time[i - 1] >= philo->time[DIE]))
			{
				pthread_mutex_lock(philo -> death_mutex);
				philo -> death = 1;
				pthread_mutex_unlock(philo -> death_mutex);
				init_fork(philo);
			}
			if (philo->hungry_time[i - 1] && get_time_ms() - \
			philo->hungry_time[i - 1] >= philo->time[DIE])
				print_log(philo, i, DIED_MSG);
		}
		pthread_mutex_unlock(philo -> eat_count_mutex);
		usleep(5000);
	}
}

void	eat(t_philo *philo, int philo_n)
{
	int	left;
	int	right;

	left = (philo_n - 1 + philo->philosophers) % philo->philosophers;
	right = (philo_n + 1) % philo->philosophers;
	if (philo->philosophers % 2 == 1 && philo_n % 2 == 0)
	{
		left = (philo_n + 1) % philo->philosophers;
		right = (philo_n - 1 + philo->philosophers) % philo->philosophers;
	}
	pthread_mutex_lock(philo -> forks[left]);
	if (print_log(philo, philo_n, FORK_MSG) == -1)
	{
		pthread_mutex_unlock(philo -> forks[left]);
		return ;
	}
	pthread_mutex_lock(philo -> forks[right]);
	if (print_log(philo, philo_n, FORK_MSG) == -1)
	{
		pthread_mutex_unlock(philo->forks[right]);
		return ;
	}
	print_log(philo, philo_n, EAT_MSG);
	usleep(philo -> time[EAT] * 1000);
	pthread_mutex_unlock(philo -> forks[left]);
	pthread_mutex_unlock(philo->forks[right]);
	pthread_mutex_lock(philo -> eat_count_mutex);
	philo -> hungry_time[philo_n - 1] = get_time_ms();
	if (philo -> must_eat_count)
		philo -> eat_count[philo_n - 1]++;
	pthread_mutex_unlock(philo -> eat_count_mutex);
}

void	*eating_philosophers(t_philo *philo)
{
	int	philo_n;

	philo_n = philo -> current_philo;
	if (philo_n == philo->philosophers || philo_n % 2 == 0)
		usleep(philo->time[EAT] * 100);
	pthread_mutex_lock(philo -> death_mutex);
	while (!philo -> death)
	{
		pthread_mutex_unlock(philo -> death_mutex);
		eat(philo, philo_n);
		if (print_log(philo, philo_n, SLEEP_MSG) == -1)
			return (0);
		usleep(philo -> time[SLEEP] * 1000);
		if (print_log(philo, philo_n, THINK_MSG) == -1)
			return (0);
		pthread_mutex_lock(philo -> death_mutex);
	}
	pthread_mutex_unlock(philo -> death_mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (parsing(&philo, argc, argv) == -1 || init(&philo) == -1)
		return (0);
	else if (philo.philosophers == 1)
	{
		usleep(philo.time[DIE] * 1000);
		print_log(&philo, 1, DIED_MSG);
	}
	else
	{
		while (philo.current_philo <= philo.philosophers)
		{
			if (pthread_create(&philo.thread[philo.current_philo - 1], \
			NULL, (void *)eating_philosophers, &philo))
				print_error(TRD_ERR);
			usleep(10); // 값 변경동안 데이터레이스 없도록
			philo.current_philo++;
		}
		monitor_thread(&philo);
		free_all_resources(&philo);
	}
	return (0);
}
