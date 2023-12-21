/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:24:10 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/22 08:08:27 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	monitor_thread(t_philo *philo)
{
	int	i;
	int	full;

	while (!philo -> death)
	{
		i = 0;
		full = 0;
		pthread_mutex_lock(philo -> eat_record_mutex);
		while (++i <= philo -> n)
		{
			if (philo -> full_eat_count && philo->eat_count[i - 1] >= philo\
			->full_eat_count)
				full++;
			if (full == philo->n || (philo->hungry_time[i - 1] && get_time_ms() - \
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
		pthread_mutex_unlock(philo -> eat_record_mutex);
		usleep(5000);
	}
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (parsing(&philo, argc, argv) == -1 || init(&philo) == -1)
		return (0);
	else if (philo.n == 1)
	{
		usleep(philo.time[DIE] * 1000);
		print_log(&philo, 1, DIED_MSG);
	}
	else
	{
		while (philo.current_philo <= philo.n)
		{
			if (pthread_create(&philo.thread[philo.current_philo - 1], \
			NULL, (void *)eating_philosophers, &philo))
				print_error(TRD_ERR);
			usleep(10); // 값 변경동안 데이터레이스 없도록
			philo.current_philo++;
		}
		monitor_thread(&philo);
	}
	free_all_resources(&philo);
	return (0);
}
