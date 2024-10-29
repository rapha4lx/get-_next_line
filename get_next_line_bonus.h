/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferro-d <rferro-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:15:16 by rferro-d          #+#    #+#             */
/*   Updated: 2024/10/29 19:34:37 by rferro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_line
{
	char			*content;
	struct s_line	*next;
}					t_line;

char				*get_next_line(int fd);

int					ft_strchr(const char *str, char c);
t_line				*t_line_new_line(const char *str, int size);
void				t_line_add_back(t_line **head, t_line *new);
t_line				*t_line_get_last(t_line *head);
void				t_line_clear(t_line **head);

#endif
