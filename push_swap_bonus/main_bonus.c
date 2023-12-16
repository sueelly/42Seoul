/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:50:02 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/16 15:18:32 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	init_stacks(t_stack *a, t_stack *b, int argc, char **argv)
{
	a -> len = 0;
	a -> name = 'a';
	a -> print = 0;
	parsing(a, argc, argv);
	a -> n = a -> len;
	b -> arr = (long *)malloc(sizeof(long) * a -> len);
	if (!b -> arr)
		exit(1);
	b -> len = 0;
	b -> name = 'b';
	b -> n = a -> len;
	b -> print = 0;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	do_command(char *command, t_stack *a, t_stack *b)
{
	if (!ft_strcmp(command, "ra\n"))
		rotate_stack(a, 1);
	else if (!ft_strcmp(command, "rb\n"))
		rotate_stack(b, 1);
	else if (!ft_strcmp(command, "rra\n"))
		rotate_stack(a, -1);
	else if (!ft_strcmp(command, "rrb\n"))
		rotate_stack(b, -1);
	else if (!ft_strcmp(command, "pa\n"))
		push_stack(a, b);
	else if (!ft_strcmp(command, "pb\n"))
		push_stack(b, a);
	else if (!ft_strcmp(command, "sa\n"))
		swap_stack(a);
	else if (!ft_strcmp(command, "sb\n"))
		swap_stack(b);
	else if (!ft_strcmp(command, "ss\n"))
	{
		swap_stack(a);
		swap_stack(b);
	}
	else
		print_error(a , b);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
	int		i;
	char	command[5];
	char	c;

	if (argc == 1)
		return (0);
	init_stacks(&a, &b, argc, argv);
	i = 0;
	command[3] = 0;
	command[4] = 0;
	while (1)
	{
		read(0, &c, 1);
		if (c == EOF && b.len == 0 && !is_sorted(&a, &b))
		{		
			free(a.arr);
			free(b.arr);
			write(1, "KO\n", 3);
			return (0);
		}			
		command[i++] = c;
		if (c == '\n')
		{
			do_command(command, &a, &b);
			i = 0;
			command[3] = 0;
			command[4] = 0;
		}
	}
	return (0);
}


// int	main(int argc, char **argv)
// {
// 	t_stack	a;
// 	t_stack	b;
// 	char	*command;

// 	if (argc == 1)
// 		return (0);
// 	init_stacks(&a, &b, argc, argv);
// 	while (1)
// 	{
// 		command = get_next_line(0);
// 		if (command == 0 && b.len == 0 && is_sorted(&a, &b))
// 			return (0);
// 		else if (command == 0)
// 		{
// 			printf("%d\n", b.len);
// 			free(a.arr);
// 			free(b.arr);
// 			write(1, "KO\n", 3);
// 			return (0);
// 		}
// 		else
// 			do_command(command, &a, &b);
// 		free(command);
// 		if (b.len == 0 && is_sorted(&a, &b))
// 			return (0);
// 	}
// 	free(a.arr);
// 	free(b.arr);
// 	return (0);
// }
