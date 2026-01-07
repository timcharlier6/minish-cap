
#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	len;
	int		i;

	s = NULL;
	len = ft_strlen(s1) + ft_strlen(s2);
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	len = 0;
	while (s1 && s1[len])
	{
		s[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		s[len + i] = s2[i];
		i++;
	}
	return (s);
}
