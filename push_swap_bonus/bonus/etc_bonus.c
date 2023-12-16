/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:14:06 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/16 05:59:01 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	*bubble_sort_arr(long *arr, int n)
{
	long	*ordered_arr;
	int		i;
	int		j;
	long	temp;

	ordered_arr = (long *)malloc(sizeof(long) * n);
	i = -1;
	while (++i < n)
			ordered_arr[i] = arr[i];
	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < n - i - 1)
		{
			if (ordered_arr[j] > ordered_arr[j + 1])
			{
				temp = ordered_arr[j];
				ordered_arr[j] = ordered_arr[j + 1];
				ordered_arr[j + 1] = temp;
			}
		}
	}
	return (ordered_arr);
}

int	is_set(t_stack *a)
{
	int	i;
	int	j;

	i = -1;
	while (++i < a -> len)
	{
		j = -1;
		while (++j < i)
			if (a -> arr[i] == a -> arr[j])
				print_error(a);
	}
	return (1);
}

int	is_sorted(t_stack *a)
{
	int	i;

	i = 0;
	while (i < a -> len - 1 && a -> arr[i] < a -> arr[i + 1])
		i++;
	if (i != a -> len - 1)
		return (0);
	free(a -> arr);
	exit(1);
}

void	print_error(t_stack *a)
{
	free(a -> arr);
	write(2, "Error\n", 6);
	exit(1);
}
