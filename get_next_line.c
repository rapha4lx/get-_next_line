
#include "get_next_line.h"

int     ft_strlen(const char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i] != '\0')
        i++;
    return (i);
}

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
    int n_count;
    int b_len;
    if (!read(fd, buff, BUFFER_SIZE))
        return (0);
    n_count = ft_strchr(buff, '\n');
    b_len = ft_strlen(buff);
    if (n_count < b_len)
    {
        while (n_count <= b_len)
        {
            t_line_add_back(head, t_line_new_line(ft_strdup(buff, 0, n_count)));            
            buff += n_count;
            n_count = ft_strchr(buff, '\n');
            if (n_count == 0)
                n_count++;
            b_len = ft_strlen(buff);
        }
        // t_line_add_back(head, t_line_new_line(ft_strdup(buff, n_count + 1, b_len - n_count)));
        return (0);
    }
    t_line_add_back(head, t_line_new_line(ft_strdup(buff, 0, b_len)));    
    return (1);
}

char    *get_line(t_line **head, char **line)
{
    char    *temp_buff;
    t_line  *temp;

    while (*head)
    {
        if (line && *line && (*line)[ft_strchr(*line, '\n')] == '\n')
            return (*line);
        temp = (*head)->next;
        temp_buff = *line;
        *line = ft_strjoin(*line, (char*)(*head)->content);
        if (temp_buff)
            free(temp_buff);
        t_line_clear(head);
        *head = temp;
    }
    return (*line);
}

char *get_next_line(int fd)
{
    static t_line *head = NULL;
    char    buff[BUFFER_SIZE];
    char    *line;

    line = NULL;
    if (head)
    {
        line = get_line(&head, &line);
        if (ft_strchr(line, '\n') < ft_strlen(line))
            return (line);
    }
    while (process_line(fd, buff, &head))
    {
        // return 
    }
    line = get_line(&head, &line);
    return (line);
}