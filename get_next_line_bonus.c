/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferro-d <rferro-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:04:53 by rferro-d          #+#    #+#             */
/*   Updated: 2024/10/29 19:29:44 by rferro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_sz;
	int		s2_sz;
	int		i;
	char	*buff;

	s1_sz = ft_strlen(s1);
	s2_sz = ft_strlen(s2);
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (s1_sz + s2_sz + 1));
	if (!buff)
		return (NULL);
	while (s1_sz > i || s2_sz > i)
	{
		if (s1_sz > i)
			buff[i] = s1[i];
		if (s2_sz > i)
			buff[s1_sz + i] = s2[i];
		i++;
	}
	buff[s1_sz + s2_sz] = '\0';
	return (buff);
}

static int	process_line(int fd, char *buff, t_line **head)
{
	int	n_count;
	int	b_len;

	if (read(fd, buff, BUFFER_SIZE) <= 0)
		return (0);
	b_len = ft_strlen(buff);
	n_count = ft_strchr(buff, '\n');
	if (n_count < b_len)
	{
		while (buff && n_count < b_len)
		{
			if (n_count == 0)
				n_count++;
			t_line_add_back(head, t_line_new_line(buff, n_count));
			buff += n_count;
			n_count = ft_strchr(buff, '\n');
			b_len = ft_strlen(buff);
		}
		if (b_len)
			t_line_add_back(head, t_line_new_line(buff, b_len));
		return (0);
	}
	t_line_add_back(head, t_line_new_line(buff, b_len));
	return (1);
}

static char	*get_line(t_line **head, char **line)
{
	char	*temp_buff;
	t_line	*temp;

	while (*head)
	{
		if (line && *line && (*line)[ft_strchr(*line, '\n')] == '\n')
			return (*line);
		temp = (*head)->next;
		temp_buff = *line;
		*line = ft_strjoin(*line, (char *)(*head)->content);
		if (temp_buff)
			free(temp_buff);
		t_line_clear(head);
		*head = temp;
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE + 1];
	char			*line;
	int				i;
	static t_line	*head[FD_MAX] = {NULL};

	i = -1;
	line = NULL;
	while (BUFFER_SIZE >= ++i)
		buff[i] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	if (head[fd])
	{
		line = get_line(&head[fd], &line);
		if (ft_strchr(line, '\n') < ft_strlen(line))
			return (line);
	}
	while (process_line(fd, buff, &head[fd]))
	{
		i = -1;
		while (BUFFER_SIZE >= ++i)
			buff[i] = '\0';
	}
	line = get_line(&head[fd], &line);
	return (line);
}
