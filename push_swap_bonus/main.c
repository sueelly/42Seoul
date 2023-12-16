/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:50:02 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/16 13:49:46 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stacks(t_stack *a, t_stack *b, int argc, char **argv)
{
	a -> len = 0;
	a -> name = 'a';
	a -> print = 1;
	parsing(a, argc, argv);
	a -> n = a -> len;
	b -> arr = (long *)malloc(sizeof(long) * a -> len);
	if (!b -> arr)
		exit(1);
	b -> len = 0;
	b -> name = 'b';
	b -> n = a -> len;
	b -> print = 1;
}

void	order_indexing(long *arr, t_stack *s, int flag)
{
	int	i;
	int	j;

	i = -1;
	while (++i < s -> len)
	{
		j = 0;
		while (arr[j] != s -> arr[i])
			j++;
		if (flag == VALUE)
			s -> arr[i] = j + 1;
		if (flag == INDEX)
			s -> arr[i] = j;
	}
}

void	radix_indexing(t_stack *s1, t_stack *s2)
{
	int	i;
	int	j;

	i = -1;
	while (++i < s1 -> len)
	{
		j = 0;
		while (j != s2 -> arr[i])
			j++;
		s2 -> arr[i] = s1 -> arr[j];
	}
}

void	change_value_for_radix(t_stack *a, int argc, char **argv)
{
	t_stack	a_test;
	t_stack	b_test;
	long	*arr;

	arr = bubble_sort_arr(a -> arr, a -> len);
	order_indexing(arr, a, INDEX);
	if (a -> n <= 5)
	{
		free(arr);
		return ;
	}
	init_stacks(&a_test, &b_test, argc, argv);
	order_indexing(arr, &a_test, VALUE);
	free(arr);
	a_test.print = 0;
	b_test.print = 0;
	radix_sort_ten(&a_test, &b_test, 1);
	radix_indexing(&a_test, a);
	free(a_test.arr);
	free(b_test.arr);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc == 1)
		return (0);
	init_stacks(&a, &b, argc, argv);
	change_value_for_radix(&a, argc, argv);
	if (a.len <= 3)
		sort_mini_stack(&a);
	else if (a.len <= 5)
		push_swap_mini(&a, &b);
	else
		radix_sort_ten(&a, &b, 1);
	free(a.arr);
	free(b.arr);
	return (0);
}
