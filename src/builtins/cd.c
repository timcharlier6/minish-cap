#include "minishell.h"

static void	cd_error(const char *arg)
{
	fprintf(stderr, "minishell: cd: %s: %s\n", arg, strerror(errno));
}

static char	*get_env(t_env *my_env, char *key)
{
	t_env	*temp;

	temp = my_env;
	while (temp->next)
	{
		if (!ft_strncmp(temp->key, key, ft_strlen(key)))
			return (temp->value);
		temp = temp->next;
	}
	return NULL;
}

static int	set_env(t_env *my_env, char *key, char *value)
{
	t_env	*temp;

	temp = my_env;
	while (temp->next)
	{
		if (!ft_strncmp(temp->key, key, ft_strlen(key)))
		{
			free(temp->value);
			temp->value = ft_calloc(ft_strlen(value), sizeof(char));
			ft_strncpy(value, temp->value, ft_strlen(value));
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	cd(t_cmd_table *cmd, t_env *my_env)
{
	char *path;
	char oldpwd[PATH_MAX];
	char newpwd[PATH_MAX];

	getcwd(oldpwd, sizeof(oldpwd));
	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "--"))
	{
		path = get_env(my_env, "HOME");
		if (!path)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else if (!ft_strcmp(cmd->args[1] , "-"))
    {
        path = get_env(my_env, "OLDPWD");
        if (!path)
        {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            return 1;
        }
        printf("%s\n", path);
    }
    else if (cmd->args[1][0] == '\0')
    {
        path = ".";
        ft_putendl_fd("", 1);
		return 0;
    }
    else 
        path = cmd->args[1];

    if (chdir(path))
    {
        cd_error(path);
        return 1;
    }
    if (oldpwd[0])
        set_env(my_env, "OLDPWD", oldpwd);
    if (getcwd(newpwd, sizeof(newpwd)))
        set_env(my_env, "PWD", newpwd);
    else
        set_env(my_env, "PWD", path);
    return 0;

}