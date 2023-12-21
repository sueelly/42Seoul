/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:43:46 by haejokim          #+#    #+#             */
/*   Updated: 2023/10/20 01:45:59 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	custom_sigaction(int signal, siginfo_t *siginfo, void *useless)
{
	static pid_t	client_pid = 0;
	static char		alpha = 0;
	static int		bit_size = 0;

	useless = 0;
	if (client_pid == 0)
		client_pid = siginfo -> si_pid;
	alpha = alpha << 1;
	if (signal == SIGUSR1)
		alpha += 1;
	bit_size++;
	if (bit_size == 8)
	{
		if (alpha)
			write(1, &alpha, 1);
		else
		{
			write(1, "\n", 1);
			client_pid = 0;
		}
		alpha = 0;
		bit_size = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sig;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = custom_sigaction;
	if (sigemptyset(&sig.sa_mask) == -1)
		print_error();
	if (sigaddset(&sig.sa_mask, SIGUSR1) == -1)
		print_error();
	if (sigaddset(&sig.sa_mask, SIGUSR2) == -1)
		print_error();
	if (sigaction(SIGUSR1, &sig, 0) == -1)
		print_error();
	if (sigaction(SIGUSR2, &sig, 0) == -1)
		print_error();
	while (1)
		pause();
	return (0);
}
