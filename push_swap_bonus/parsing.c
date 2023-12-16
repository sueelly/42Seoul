/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:01:43 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/16 09:11:53 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_do_split(char *str, char **strs, int *len)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (len)
			len[count] = 0;
		j = 0;
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
		{
			if (len)
				len[count]++;
			if (strs)
				strs[count][j++] = str[i];
			if (str[i + 1] == ' ' || str[i + 1] == 0)
				count++;
			i++;
		}
	}
	return (count);
}

char	**ft_split(char *str, int word)
{
	int		*len;
	char	**strs;

	len = 0;
	strs = 0;
	len = (int *)malloc(sizeof(int) * (word + 1));
	if (!len)
		exit(1);
	len[word] = word;
	ft_do_split(str, strs, len);
	strs = (char **)malloc(sizeof(char *) * (word + 1));
	if (!strs)
		exit(1);
	strs[word] = 0;
	while (word--)
	{
		strs[word] = (char *)malloc(len[word] + 1);
		if (!str[word])
			exit(1);
		strs[word][len[word]] = 0;
	}
	ft_do_split(str, strs, len);
	free(len);
	return (strs);
}

int	ft_atoi(char *str, t_stack *s)
{
	int		i;
	int		flag;
	int		sign;
	long	n;
	char	last;

	i = 0;
	flag = 0;
	sign = 1;
	if (str[i] == '-' && ++i)
		sign = -1;
	else if (str[i] == '+')
		i++;
	n = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9' && n >= 0 && ++flag)
		n = n * 10 + str[i++] - '0';
	last = str[i];
	free(str);
	if (last != 0 || n < 0 || flag == 0 || \
	n * sign >= 2147483648 || n * sign <= -2147483649)
		print_error(s, 0);
	return (n * sign);
}

void	parsing(t_stack *a, int argc, char **argv)
{
	int		i;
	int		j;
	int		k;
	char	**arg;

	i = 1;
	while (i < argc && ft_do_split(argv[i], 0, 0))
		a -> len += ft_do_split(argv[i++], 0, 0);
	if (i != argc)
		print_error(a, 0);
	a -> arr = (long *)malloc(sizeof(long) * (a -> len));
	if (!a -> arr)
		exit(1);
	i = 0;
	j = 0;
	while (++i < argc)
	{
		k = -1;
		arg = ft_split(argv[i], ft_do_split(argv[i], 0, 0));
		while (arg[++k])
			a -> arr[j++] = ft_atoi(arg[k], a);
		free(arg);
	}
	is_sorted(a, 0);
	is_set(a);
}
