/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferro-d <rferro-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:05:03 by rferro-d          #+#    #+#             */
/*   Updated: 2024/10/29 19:22:21 by rferro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr(const char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

t_line	*t_line_new_line(const char *str, int size)
{
	t_line	*new;
	char	*buff;
	int		i;

	buff = (char *)malloc(sizeof(char) * (size + 1));
	if (!buff)
		return (NULL);
	i = 0;
	while (str[i] && i < size)
	{
		buff[i] = str[i];
		i++;
	}
	buff[i] = '\0';
	new = (t_line *)malloc(sizeof(t_line) * 1);
	if (!new)
		return (NULL);
	new->content = (void *)buff;
	new->next = NULL;
	return (new);
}

void	t_line_add_back(t_line **head, t_line *new)
{
	t_line	*temp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}

t_line	*t_line_get_last(t_line *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	t_line_clear(t_line **head)
{
	t_line	*temp;

	temp = (*head)->next;
	free((*head)->content);
	free((*head));
	*head = temp;
}
