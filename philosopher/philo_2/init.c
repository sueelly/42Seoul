/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:38:20 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/22 06:51:33 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	parsing(t_philo *philo, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		print_error(ARGC_ERR);
		return (-1);
	}
	philo->n = ft_atoi(argv[1]);
	philo->time[DIE] = ft_atoi(argv[2]);
	philo->time[EAT] = ft_atoi(argv[3]);
	philo->time[SLEEP] = ft_atoi(argv[4]);
	philo->full_eat_count = 0;
	if (argc == 6)
		philo->full_eat_count = ft_atoi(argv[5]);
	if (philo->n <= 0 || philo->time[DIE] <= 0 || \
	philo->time[EAT] <= 0 || philo->time[SLEEP] <= 0 || \
	(argc == 6 && philo->full_eat_count <= 0))
	{
		print_error(ARGV_ERR);
		return (0);
	}
	printf("philo->n:%d\n", philo->n);
	return (1);
}

void	init_zero(t_philo *philo)
{
	philo->current_philo = 1;
	philo->thread = 0;
	philo->start_time = get_time_ms();
	philo->death = 0;
	philo->full_count = 0;
	philo->hungry_time = 0;
	philo->eat_count = 0;
	philo->forks = 0;
	philo->eat_record_mutex = 0;
	philo->death_mutex = 0;
	philo->print_mutex = 0;
}

int	init_mutex(t_philo *philo)
{
	int	i;

	philo->eat_record_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->eat_record_mutex || \
	pthread_mutex_init(philo->eat_record_mutex, 0))
		return (0);
	philo->death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->death_mutex || pthread_mutex_init(philo->death_mutex, 0))
		return (0);
	philo->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->print_mutex || pthread_mutex_init(philo->print_mutex, 0))
		return (0);
	i = -1;
	while (++i < philo->n)
	{
		philo->hungry_time[i] = get_time_ms();
		philo->eat_count[i] = 0;
		philo->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!philo->forks[i] || pthread_mutex_init(philo->forks[i], 0))
			return (0);
	}
	return (1);
}

int	init(t_philo *philo)
{
	int	i;

	init_zero(philo);
	philo->thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->n);
	if (!philo->thread)
		return (0);
	philo->hungry_time = (long *)malloc(sizeof(long) * philo->n);
	if (!philo->hungry_time)
		return (0);
	philo->eat_count = (int *)malloc(sizeof(int) * philo->n);
	if (!philo->eat_count)
		return (0);
	philo->forks = malloc(sizeof(pthread_mutex_t *) * philo->n);
	if (!philo->forks)
		return (0);
	i = -1;
	while (++i < philo->n)
	{
		philo->hungry_time[i] = 0;
		philo->eat_count[i] = 0;
		philo->forks[i] = 0;
	}
	if (!init_mutex(philo))
		return (0);
	printf("die %d eat %d sleep %d\n", philo->time[DIE], philo->time[EAT], philo->time[SLEEP]);
	return (1);
}
