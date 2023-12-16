/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:21:21 by haejokim          #+#    #+#             */
/*   Updated: 2023/12/16 08:46:45 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_is_done(t_storage *S)
{
	t_buffer	*p;
	size_t		line_len;
	size_t		i;

	line_len = 0;
	p = S -> buffer_head;
	while (p)
	{
		i = 0;
		while (p -> buffer[i])
			if (++line_len && p -> buffer[i++] == '\n')
				return (line_len);
		p = p -> next;
	}
	if (S -> read_len != BUFFER_SIZE)
		return (line_len);
	return (FAIL);
}

int	ft_update_buffer(t_storage *S, char *buffer)
{
	t_buffer	*new_buffer;
	t_buffer	*p;

	if (!S -> read_len)
		return (DONE);
	new_buffer = (t_buffer *)malloc(sizeof(t_buffer));
	if (!new_buffer)
		return (FAIL);
	new_buffer -> next = NULL;
	ft_strlcpy(new_buffer -> buffer, buffer, S -> read_len + 1);
	if (!S -> buffer_head)
	{
		S -> buffer_head = new_buffer;
		return (SUCCESS);
	}
	p = S -> buffer_head;
	while (p -> next)
		p = p -> next;
	p -> next = new_buffer;
	return (SUCCESS);
}

char	*ft_extract_line(t_storage *S)
{
	char		*line;
	size_t		i;
	size_t		j;

	line = (char *)malloc(sizeof(char) * (S -> line_len + 1));
	if (!line)
		return (ft_free_buffer(S, 0));
	i = 0;
	j = 0;
	line[S -> line_len] = 0;
	while (S -> line_len--)
	{
		if (S -> buffer_head -> buffer[i])
			line[j++] = S -> buffer_head -> buffer[i++];
		else
		{
			ft_free_buffer(S, 1);
			i = 0;
			S -> line_len++;
		}
	}
	ft_strlcpy(S -> buffer_head -> buffer, \
		&S -> buffer_head -> buffer[i], BUFFER_SIZE - (i % BUFFER_SIZE) + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_storage	storage;
	char				buffer[BUFFER_SIZE + 1];

	if (BUFFER_SIZE < 0 || fd < 0)
		return (FAIL);
	while (1)
	{
		storage.line_len = ft_is_done(&storage);
		if (storage.line_len)
			return (ft_extract_line(&storage));
		ft_set_null(buffer, BUFFER_SIZE + 1);
		storage.read_len = read(fd, buffer, BUFFER_SIZE);
		if (storage.read_len < 0 || (storage.read_len == 0 && \
			!ft_is_done(&storage)) || !ft_update_buffer(&storage, buffer))
			return (ft_free_buffer(&storage, 0));
	}
	return (0);
}
