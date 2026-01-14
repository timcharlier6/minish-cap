#include "minishell.h"

int my_env(t_env *my_env)
{
    t_env *temp;

    temp = my_env;

    while (temp->next)
    {
        printf("%s=%s\n", temp->key, temp->value);
        temp = temp->next;
    }
    return 0;
}