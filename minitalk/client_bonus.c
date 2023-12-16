/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:26:14 by haejokim          #+#    #+#             */
/*   Updated: 2023/10/20 02:22:44 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_signal_from_sever;

void	send_str(int server_pid, char *str)
{
	int	i;
	int	count;
	int	bit;

	i = -1;
	if (str[0] == 0)
		return ;
	while (++i >= 0)
	{
		count = 8;
		while (--count >= 0)
		{
			bit = (str[i] >> count) % 2;
			if (bit == 1 && kill(server_pid, SIGUSR1) == -1)
				print_error();
			else if (bit == 0 && kill(server_pid, SIGUSR2) == -1)
				print_error();
			while (g_signal_from_sever == 0)
				;
			usleep(500);
		}
		if (str[i] == 0)
			break ;
	}
}

void	ft_handler(int sig)
{
	if (sig == SIGUSR1 || sig == SIGUSR2)
		g_signal_from_sever = 1;
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 3 || argv[2] == 0)
	{
		write(2, "Wrong Argument\n", 15);
		return (0);
	}
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, ft_handler);
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 1 || server_pid > 99999)
		write(2, "Wrong PID\n", 10);
	else
		send_str(server_pid, argv[2]);
	return (0);
}
