/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:35:00 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/16 13:36:23 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	char	name;
	long	*arr;
	int		len;
	int		n;
	int		print;
}	t_stack;

# define VALUE 0
# define INDEX 1

void	parsing(t_stack *a, int argc, char **argv);
void	swap_stack(t_stack *s);
void	push_stack(t_stack *from, t_stack *to);
void	rotate_stack(t_stack *s, int dirrection);
void	radix_sort_ten(t_stack *a, t_stack *b, long digit);
void	sort_mini_stack(t_stack *s);
void	push_swap_mini(t_stack *a, t_stack *b);
int		is_set(t_stack *a);
int		is_sorted(t_stack *a, t_stack *b);
void	print_error(t_stack *a, t_stack *b);
long	*bubble_sort_arr(long *arr, int n);

#endif