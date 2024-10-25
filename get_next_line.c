
#include "get_next_line.h"

int     ft_strlen(const char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    while (*str++)
        i++;
    return (i);
}

// char    *ft_strdup(const char *str, int start, int size)
// {
//     char    *buff;
//     int     b_s;

//     b_s = ft_strlen(str);
//     buff = (char*)malloc(sizeof(char) * (b_s + 1));
//     if (!b_s);
//         return (0);
//     while (buff[b_s])
//     {
//         buff[b_s] = str[b_s];
//         b_s++;
//     }
//     buff[b_s] = '\0';
//     return (buff);
// }

char    *ft_strdup(const char *str, int start, int size)
{
    char    *buff;
    int     i;

    buff = (char*)malloc(sizeof(char) * (size + 1));
    if (!buff)
        return (NULL);
    i = 0;
    while (str[start + i] && i < size)
    {
        buff[i] = str[start + i];
        i++;
    }
    buff[i] = '\0';
    return (buff);
}

char  *ft_strjoin(char *s1, char *s2)
{
    int s1_sz;
    int s2_sz;
    int     i;
    char    *buff;

    s1_sz = ft_strlen(s1);
    s2_sz = ft_strlen(s2);
    i = 0;
    if (!s1)
        return (ft_strdup(s2, 0, s2_sz));
    if (!s2)
        return (ft_strdup(s1, 0, s1_sz));
    buff = (char*)malloc(sizeof(char) * (s1_sz + s2_sz + 1));
    if (!buff)
        return (NULL);
    while (s1[i] || s2[i])
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

int     process_line(int fd, char *buff, t_line **head)
{
    int i;

    if (!read(fd, buff, BUFFER_SIZE))
        return (0);
    i = ft_strchr(buff, '\n');
    if (i >= BUFFER_SIZE)
    {
        t_line_add_back(head, t_line_new_line(ft_strdup(buff, 0, BUFFER_SIZE)));
        return (1);
    }
    else if (i > 0)
    {
        t_line_add_back(head, t_line_new_line(ft_strdup(buff, 0, i + 1)));
        buff += i + 2;
        i = ft_strchr(buff, '\n') + 1;
        t_line_add_back(head, t_line_new_line(ft_strdup(buff, 0, i)));
    }
    return (0);
}

char    *get_line(t_line **head)
{
    char    *buff;
    char    *temp_buff;
    t_line  *temp;

    buff = NULL;
    while (*head)
    {
        // if (ft_strchr(buff, '\n'))
        //     return (buff);
        temp = (*head)->next;
        temp_buff = buff;
        buff = ft_strjoin(buff, (char*)(*head)->content);
        if (temp_buff)
            free(temp_buff);
        t_line_clear(head);
        *head = temp;
    }
    return (buff);
}

char *get_next_line(int fd)
{
    static t_line *head = NULL;
    char    buff[BUFFER_SIZE];

    if (head)
        return (get_line(&head));
    while (process_line(fd, buff, &head))
    {
        // return 
    }
    return (get_line(&head));
}