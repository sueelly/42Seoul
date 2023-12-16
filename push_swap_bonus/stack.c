/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:27:42 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/16 08:31:10 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_stack(t_stack *s)
{
	int	temp;

	if (s -> len < 2)
		return ;
	temp = s -> arr[0];
	s -> arr[0] = s -> arr[1];
	s -> arr[1] = temp;
	if (!s -> print)
		return ;
	write(1, "s", 1);
	write(1, &s -> name, 1);
	write(1, "\n", 1);
}

void	push_stack(t_stack *from, t_stack *to)
{
	int	i;
	int	temp;

	if (from -> len == 0)
		return ;
	from -> len--;
	to -> len++;
	if (to -> len > 1)
	{
		i = to -> len;
		temp = from -> arr[0];
		while (--i > 0)
			to -> arr[i] = to -> arr[i - 1];
		to -> arr[i] = temp;
	}
	else
		to -> arr[0] = from -> arr[0];
	i = -1;
	while (++i < from -> len)
		from -> arr[i] = from -> arr[i + 1];
	if (!to -> print)
		return ;
	write(1, "p", 1);
	write(1, &to -> name, 1);
	write(1, "\n", 1);
}

void	rotate_stack(t_stack *s, int dirrection)
{
	int	i;
	int	temp;

	if (s -> len <= 1)
		return ;
	if (dirrection == -1)
	{
		write(1, "r", 1);
		i = s -> len;
		temp = s -> arr[s -> len - 1];
		while (--i > 0)
			s -> arr[i] = s -> arr[i - 1];
	}
	else
	{
		i = -1;
		temp = s -> arr[0];
		while (++i < s -> len - 1)
			s -> arr[i] = s -> arr[i + 1];
	}
	s -> arr[i] = temp;
	if (s -> print && write(1, "r", 1) && write(1, &s -> name, 1) && \
	write(1, "\n", 1))
		return ;
}
