/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:51:08 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/22 08:35:39 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	monitor_thread(t_philo *philo)
{
	int	death;
	int	i;

	death = 0;
	while (!death)
	{
		i = 0;
		usleep(100);
		while (++i <= philo->n)
		{
			pthread_mutex_lock(philo->eat_record_mutex);
			if (get_time_ms() - philo->hungry_time[i - 1] >= philo->time[DIE])
			{
				pthread_mutex_unlock(philo->eat_record_mutex);
				printf("%ld-%ld == %ld >= %d\n", get_time_ms(), philo->hungry_time[i - 1], get_time_ms() - philo->hungry_time[i - 1], philo->time[DIE]);
				pthread_mutex_lock(philo->death_mutex);
				philo->death = 1;
				pthread_mutex_unlock(philo->death_mutex);
				print_log(philo, i, DIED_MSG);
				init_fork(philo);
				break ;
			}
			pthread_mutex_unlock(philo->eat_record_mutex);
		}
		pthread_mutex_lock(philo->death_mutex);
		death = philo->death;
		pthread_mutex_unlock(philo->death_mutex);
	}
	usleep(1000000);
}

// void	leak_check(void)
// {
// 	system("leaks philo");
// }

int	main(int argc, char **argv)
{
	//atexit(leak_check);
	t_philo	philo;

	if (!parsing(&philo, argc, argv) || !init(&philo))
		return (print_error(ALLC_ARR) * free_all_resources(&philo));
	else if (philo.n == 1)
	{
		usleep(philo.time[DIE] * 1000);	
		print_log(&philo, 1, DIED_MSG);
		free_all_resources(&philo);
	}
	else
	{
		while (philo.current_philo <= philo.n)
		{	
			printf("thread creating: %d %ld\n", philo.current_philo, get_time_ms() - philo.start_time);
			//if (pthread_create(&philo.thread[philo.current_philo - 1], \
			//NULL, (void *)eating_philosophers, &philo))
			//	print_error(TRD_ERR);
			//printf("after creating: %d %ld\n", philo.current_philo, get_time_ms() - philo.start_time);
			usleep(10);
			philo.current_philo++;
		}
		monitor_thread(&philo);
		free_all_resources(&philo);
	}
	return (0);
}
