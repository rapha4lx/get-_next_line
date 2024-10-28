
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


typedef struct s_line
{
    char    *content;
    struct  s_line *next; 
} t_line;

int     ft_strlen(const char *str);
char  *ft_strjoin(char *s1, char *s2);
// char    *ft_strdup(const char *str);
char    *ft_strdup(const char *str, int start, int size);


int     ft_strchr(const char *str, char c);
t_line  *t_line_new_line(void* content);
void    t_line_add_back(t_line **head, t_line *new);
t_line  *t_line_get_last(t_line* head);
void    t_line_clear(t_line **head);
char    *get_next_line(int fd);

#endif