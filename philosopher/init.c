/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:17:09 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/21 22:26:04 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

int	parsing(t_philo *philo, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		print_error(ARGC_ERR);
		return (-1);
	}
	philo -> philosophers = ft_atoi(argv[1]);
	philo -> time[DIE] = ft_atoi(argv[2]);
	philo -> time[EAT] = ft_atoi(argv[3]);
	philo -> time[SLEEP] = ft_atoi(argv[4]);
	philo -> must_eat_count = 0;
	if (argc == 6)
		philo -> must_eat_count = ft_atoi(argv[5]);
	if (philo -> philosophers <= 0 || philo -> time[DIE] <= 0 || \
	philo -> time[EAT] <= 0 || philo -> time[SLEEP] <= 0 || \
	(argc == 6 && philo -> must_eat_count <= 0))
	{
		print_error(ARGV_ERR);
		return (-1);
	}
	return (0);
}

int	init_mutex(t_philo *philo)
{
	int	i;

	if (pthread_mutex_init(philo -> death_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(philo -> print_mutex, NULL))
		return (-1);
	i = 0;
	while (i < philo -> philosophers)
	{
		philo -> forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!philo -> forks[i])
			return (-1);
		if (pthread_mutex_init(philo -> forks[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	init_philo(t_philo *philo)
{
	philo -> thread = malloc(sizeof(pthread_t) * philo->philosophers);
	if (!philo -> thread)
		return (-1);
	philo -> hungry_time = malloc(sizeof(long) * philo->philosophers);
	if (!philo -> hungry_time)
		return (-1);
	philo -> eat_count = malloc(sizeof(int) * philo->philosophers);
	if (!philo -> eat_count)
		return (-1);
	philo -> forks = malloc(sizeof(pthread_mutex_t *) * philo->philosophers);
	if (!philo -> forks)
		return (-1);
	philo -> eat_count_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo -> eat_count_mutex)
		return (-1);
	philo -> death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo -> death_mutex)
		return (-1);
	philo -> print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo -> print_mutex)
		return (-1);
	return (0);
}

int	init(t_philo *philo)
{
	int	i;

	philo -> thread = 0;
	philo -> forks = 0;
	philo -> death = 0;
	philo -> hungry_time = 0;
	philo -> eat_count = 0;
	philo -> current_philo = 1;
	philo -> eat_count_mutex = 0;
	philo -> start_time = get_time_ms();
	philo -> death_mutex = 0;
	philo -> print_mutex = 0;
	philo -> death = 0;
	if (init_philo(philo) == -1 && print_error(ALLC_ARR))
		return (free_all_resources(philo));
	i = 0;
	while (i < philo -> philosophers)
	{
		philo -> thread[i] = 0;
		philo -> forks[i] = (pthread_mutex_t *)0;
		philo -> hungry_time[i] = 0;
		philo -> eat_count[i++] = 0;
	}	
	if (init_mutex(philo) == -1 && print_error(ALLC_ARR))
		return (free_all_resources(philo));
	return (0);
}

int	free_all_resources(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo -> philosophers)
	{
		if (philo -> thread[i])
			pthread_join(philo -> thread[i], NULL);
		if (philo -> forks[i])
		{
			pthread_mutex_destroy(philo -> forks[i]);
			free(philo -> forks[i]);
		}
	}
	if (philo -> death_mutex)
	{
		pthread_mutex_destroy(philo -> death_mutex);
		free(philo -> death_mutex);
	}
	if (philo -> print_mutex)
	{
		pthread_mutex_destroy(philo -> print_mutex);
		free(philo -> print_mutex);
	}
	if (philo -> eat_count_mutex)
	{
		pthread_mutex_destroy(philo -> eat_count_mutex);
		free(philo -> eat_count_mutex);
	}
	free(philo -> thread);
	if (philo -> hungry_time)
		free(philo -> hungry_time);
	if (philo -> eat_count)
		free(philo -> eat_count);
	if (philo -> forks)
		free(philo -> forks);
	return (-1);
}
