/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:09:48 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/22 08:16:18 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

# define DIE 0
# define EAT 1
# define SLEEP 2

# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIED_MSG "died"
# define FORK_MSG "has taken a fork"
# define ARGC_ERR "Wrong argument count\n"
# define ARGV_ERR "Wrong argument value\n"
# define ALLC_ARR "Allocation error\n"
# define TRD_ERR "Thread error\n"

typedef struct s_philo
{
	int				n;
	int				current_philo;
	pthread_t		*thread;
	int				time[3];
	int				full_eat_count;
	long			start_time;
	int				death;
	int				full_count;
	long			*hungry_time;
	int				*eat_count;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*eat_record_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*print_mutex;
}	t_philo;

void	ft_swap(int *a, int *b);
void	init_fork(t_philo *philo);
long	get_time_ms(void);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
int		print_error(char *msg);
int		print_log(t_philo *philo, int philo_n, char *msg);
int		parsing(t_philo *philo, int argc, char **argv);
int		init(t_philo *philo);
int		free_all_resources(t_philo *philo);
void	*eating_philosophers(t_philo *philo);

// void
// _(){
// 	printf("%s %d\n", __FILE__, __LINE__);
// }

#endif