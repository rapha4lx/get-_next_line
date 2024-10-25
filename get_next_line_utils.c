
#include <stdlib.h>
#include "get_next_line.h"

int     ft_strchr(const char *str, char c)
{
    int     i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (i);
}

t_line  *t_line_new_line(void* content)
{
    t_line *new;

    new = (t_line*)malloc(sizeof(t_line) * 1);
    if (!new)
        return (NULL);
    new->content = content;
    new->next = NULL;
    return (new);
}

void    t_line_add_back(t_line **head, t_line *new)
{
    t_line *temp;

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

t_line  *t_line_get_last(t_line* head)
{
    if (!head)
        return (NULL);
    while (head->next)
        head = head->next;
    return (head);
}

void    t_line_clear(t_line **head)
{
    t_line  *temp;

    temp = (*head)->next;
    free((*head)->content);
    free((*head));
    *head = temp;
}