/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:04:09 by haejokim          #+#    #+#             */
/*   Updated: 2023/07/18 21:26:26 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# define FAIL 0
# define SUCCESS -1
# define DONE -2

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	char			buffer[BUFFER_SIZE + 1];
	size_t			buffer_len;
	struct s_buffer	*next;
}	t_buffer;

typedef struct s_storage
{
	int					fd;
	ssize_t				line_len;
	ssize_t				read_len;
	t_buffer			*buffer_head;
	struct s_storage	*next;
}	t_storage;

typedef struct s_storages
{
	t_storage	*head;
}	t_storages;

char	*ft_free_storages(t_storages *S, int fd);
char	*ft_free_buffer(t_storage *S, int only_head_next);
void	ft_set_null(char *str, size_t n);
size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char *dest, char *src, size_t n);
int		ft_is_done(t_storage *S);
int		ft_update_buffer(t_storage *S, char *buffer);
char	*ft_extract_line(t_storage *S, t_storages *t_storages);
char	*get_next_line(int fd);

#endif