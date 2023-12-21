/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:11:33 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/22 08:14:22 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_mutex(t_philo *philo)
{
	int	i;

	if (philo->eat_record_mutex)
	{
		pthread_mutex_destroy(philo->eat_record_mutex);
		free(philo->eat_record_mutex);
	}
	if (philo->death_mutex)
	{
		pthread_mutex_destroy(philo->death_mutex);
		free(philo->death_mutex);
	}
	if (philo->print_mutex)
	{
		pthread_mutex_destroy(philo->death_mutex);
		free(philo->print_mutex);
	}
	i = -1;
	while (philo->forks && ++i < philo->n && philo->forks[i])
	{
		pthread_mutex_destroy(philo->forks[i]);
		free(philo->forks[i]);
	}
	if (philo->forks)
		free(philo->forks);
}

int	free_all_resources(t_philo *philo)
{
	int	i;

	if (philo->thread)	
	{
		i = -1;
		while (++i < philo->n)
			pthread_join(philo->thread[i], 0);
			//pthread_detach(philo->thread[i]);
		free(philo->thread);
	}
	if (philo->hungry_time)
		free(philo->hungry_time);
	if (philo->eat_count)
		free(philo->eat_count);
	free_mutex(philo);
	return (0);
}
