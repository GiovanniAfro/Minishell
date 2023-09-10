/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:23:26 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/09 12:44:29 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc(char **env, size_t size)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(size);
	while (env && env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = NULL;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	return (new);
}

int	ft_setenv(char *name, char *value, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0)
		{
			free(shell->env[i]);
			tmp = ft_strjoin(name, "=");
			shell->env[i] = ft_strjoin(tmp, value);
			free(tmp);
			return (0);
		}
		i++;
	}
	while (shell->env[i])
		i++;
	shell->env = ft_realloc(shell->env, sizeof(char *) * (i + 2));
	tmp = ft_strjoin(name, "=");
	shell->env[i] = ft_strjoin(tmp, value);
	shell->env[i + 1] = NULL;
	free(tmp);
	return (0);
}

int	ft_unsetenv(char *name, t_shell *shell)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	j = 0;
	env = shell->env;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			free(env[i]);
			while (env[i + j])
			{
				env[i + j] = env[i + j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}