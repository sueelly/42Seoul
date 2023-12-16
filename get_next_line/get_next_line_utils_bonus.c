/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:51:31 by haejokim          #+#    #+#             */
/*   Updated: 2023/06/29 22:30:28 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free_storages(t_storages *S, int fd)
{
	t_storage	*p;
	t_storage	*temp;

	p = S -> head;
	if (p -> fd == fd)
	{
		ft_free_buffer(p, 0);
		temp = p;
		S -> head = p -> next;
		free(temp);
		return (FAIL);
	}
	while (p && p -> next && p -> next -> fd != fd)
		p = p -> next;
	ft_free_buffer(p -> next, 0);
	temp = p -> next;
	p -> next = p -> next -> next;
	free(temp);
	return (FAIL);
}

char	*ft_free_buffer(t_storage *S, int only_head_next)
{
	t_buffer	*p;
	t_buffer	*temp;

	if (only_head_next)
	{
		temp = S -> buffer_head;
		S -> buffer_head = S -> buffer_head -> next;
		free(temp);
		return (FAIL);
	}
	if (!S -> buffer_head)
		return (FAIL);
	p = S -> buffer_head;
	while (p)
	{
		temp = p;
		p = p -> next;
		free(temp);
	}
	S -> buffer_head = 0;
	return (FAIL);
}

void	ft_set_null(char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		str[i++] = 0;
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dest, char *src, size_t n)
{
	size_t	len;

	len = ft_strlen(src);
	if (n == 0)
		return (len);
	while ((n-- > 1) && *src)
		*dest++ = *src++;
	*dest = '\0';
	return (len);
}
