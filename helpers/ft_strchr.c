#include "minishell.h"

int ft_strchr(char *s, int c)
{
    int i = 0;
    if (!s)
        return -1;
    while (s[i])
    {
        if (s[i] == (char)c)
            return i;
        else 
         i++;
    }
    if (c == '\0')
        return i;
    return -1;
}