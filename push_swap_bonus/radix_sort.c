/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:05:50 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/16 13:17:00 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_mini_stack(t_stack *s)
{
	if (s -> len == 2 && s -> arr[0] > s -> arr[1])
		swap_stack(s);
	else if (s -> len == 3)
	{
		if (s->arr[0] > s->arr[1] && s->arr[0] < s->arr[2])
			swap_stack(s);
		else if (s->arr[0] > s->arr[1] && s->arr[0] > s->arr[2] \
		&& s->arr[1] < s->arr[2])
			rotate_stack(s, 1);
		if (s->arr[0] < s->arr[1] && s->arr[0] > s->arr[2])
			rotate_stack(s, -1);
		else if (s->arr[0] > s->arr[1] && s->arr[0] > s->arr[\
		2] && s->arr[1] > s->arr[2])
		{
			swap_stack(s);
			rotate_stack(s, -1);
		}
		else if (s->arr[0] < s->arr[1] && \
		s->arr[1] > s->arr[2])
		{
			swap_stack(s);
			rotate_stack(s, 1);
		}
	}
}

void	push_swap_mini(t_stack *a, t_stack *b)
{
	if (a -> len == 4)
	{
		if (a -> arr[3] == 0)
			rotate_stack(a, -1);
		while (a -> arr[0] != 0)
			rotate_stack(a, 1);
		push_stack(a, b);
		sort_mini_stack(a);
		push_stack(b, a);
	}
	else if (a -> len == 5)
	{
		while (a -> arr[0] != 0 && a -> arr[0] != 1)
			rotate_stack(a, 1);
		push_stack(a, b);
		while (a -> arr[0] != 0 && a -> arr[0] != 1)
			rotate_stack(a, 1);
		push_stack(a, b);
		if (b -> arr[0] < b -> arr[1])
			swap_stack(b);
		sort_mini_stack(a);
		push_stack(b, a);
		push_stack(b, a);
	}
}

void	radix_sort_ten_1(t_stack *a, t_stack *b, long digit)
{
	int	n;

	n = a -> len;
	while (n--)
	{
		if (a -> arr[0] / digit % 10 <= 5)
			push_stack(a, b);
		else
			rotate_stack(a, 1);
		if (b -> arr[0] / digit % 10 <= 2)
			rotate_stack(b, 1);
	}
	n = b -> len;
	while (n-- && b -> arr[0] / digit % 10 > 2)
	{
		if (b -> arr[0] / digit % 10 >= 4)
			push_stack(b, a);
		else
			rotate_stack(b, 1);
		if (a -> arr[0] / digit % 10 == 5)
			rotate_stack(a, 1);
	}
}

void	radix_sort_ten_2(t_stack *a, t_stack *b, long digit)
{
	int	n;

	n = b -> len;
	while (n-- && b -> arr[0] / digit % 10 != 3)
	{
		if (b -> arr[0] / digit % 10 >= 1)
			push_stack(b, a);
		else
			rotate_stack(b, 1);
		if (a -> arr[0] / digit % 10 == 1)
			rotate_stack(a, 1);
	}
	n = a -> len;
	while (n-- && a -> arr[0] / digit % 10 != 5)
	{
		if (a -> arr[0] / digit % 10 <= 6)
			rotate_stack(a, 1);
		else
			push_stack(a, b);
		if (b -> arr[0] / digit % 10 == 7)
			rotate_stack(b, 1);
	}
}

void	radix_sort_ten(t_stack *a, t_stack *b, long digit)
{
	if (digit >= a -> n)
		return ;
	radix_sort_ten_1(a, b, digit);
	radix_sort_ten_2(a, b, digit);
	while (b -> len)
	{
		push_stack(b, a);
		if (a -> arr[0] / digit % 10 == 9)
			rotate_stack(a, 1);
	}
	radix_sort_ten(a, b, digit * 10);
}
