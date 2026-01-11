/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 14:19:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	get_env_index(char *key, char **envp)
{
	int		i;
	int		len;

	len = ft_strlen(key);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static int	is_valid_ident(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_set_env(char *key, char *value, char ***envp)
{
	char	*new_entry;
	int		idx;
	int		count;
	char	**new_env;
	int		i;

	if (!key || !envp || !*envp)
		return (1);
	new_entry = ft_strjoin(key, "=");
	if (value)
	{
		char *tmp = new_entry;
		new_entry = ft_strjoin(new_entry, value);
		free(tmp);
	}
	idx = get_env_index(key, *envp);
	if (idx != -1)
	{
		free((*envp)[idx]);
		(*envp)[idx] = new_entry;
	}
	else
	{
		count = 0;
		while ((*envp)[count]) count++;
		new_env = ft_calloc(count + 2, sizeof(char *));
		i = -1;
		while (++i < count) new_env[i] = (*envp)[i];
		new_env[count] = new_entry;
		free(*envp);
		*envp = new_env;
	}
	return (0);
}

static void	print_sorted_env(char **envp)
{
	int		count;
	char	**sorted;
	int		i;
	int		j;
	char	*tmp;
	char	*eq;

	count = 0;
	while (envp[count])
		count++;
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return ;
	i = -1;
	while (++i < count)
		sorted[i] = envp[i];
	sorted[count] = NULL;
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(sorted[j], sorted[j + 1], ft_strlen(sorted[j]) + ft_strlen(sorted[j + 1])) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		if (ft_strncmp(sorted[i], "_=", 2) != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			eq = ft_strchr(sorted[i], '=');
			if (eq)
			{
				write(1, sorted[i], eq - sorted[i]);
				write(1, "=\"", 2);
				ft_putstr_fd(eq + 1, 1);
				write(1, "\"\n", 2);
			}
			else
				ft_putendl_fd(sorted[i], 1);
		}
		i++;
	}
	free(sorted);
}

int	ft_export(char **args, char ***envp)
{
	char	*key;
	int		idx;
	char	*new_entry;
	int		count;
	char	**new_env;
	char	*eq;
	int		i;
	int		ret;
	int		arg_idx;

	if (!args[1])
	{
		print_sorted_env(*envp);
		return (0);
	}
	ret = 0;
	arg_idx = 1;
	while (args[arg_idx])
	{
		if (args[arg_idx][0] == '-')
		{
			ft_putstr_fd("minishell: export: ", 2);
			if (args[arg_idx][1] && args[arg_idx][1] != '-')
			{
				write(2, "-", 1);
				write(2, &args[arg_idx][1], 1);
			}
			else
				ft_putstr_fd(args[arg_idx], 2);
			ft_putendl_fd(": invalid option", 2);
			ft_putendl_fd("export: usage: export [name[=value] ...] or export -p", 2);
			return (2);
		}
		eq = ft_strchr(args[arg_idx], '=');
		int append = 0;
		if (eq)
		{
			if (eq > args[arg_idx] && *(eq - 1) == '+')
			{
				append = 1;
				key = ft_substr(args[arg_idx], 0, eq - args[arg_idx] - 1);
			}
			else
				key = ft_substr(args[arg_idx], 0, eq - args[arg_idx]);
			new_entry = ft_strdup(args[arg_idx]);
		}
		else
		{
			key = ft_strdup(args[arg_idx]);
			new_entry = NULL; 
		}

		if (!is_valid_ident(key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[arg_idx], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			free(key);
			if (new_entry) free(new_entry);
			ret = 1;
			arg_idx++;
			continue ;
		}

		idx = get_env_index(key, *envp);
		if (idx != -1)
		{
			if (eq) 
			{
				if (append)
				{
					char *joined = ft_strjoin((*envp)[idx], eq + 1);
					free((*envp)[idx]);
					(*envp)[idx] = joined;
					free(new_entry);
				}
				else
				{
					free((*envp)[idx]);
					(*envp)[idx] = new_entry;
				}
			}
			else
				if (new_entry) free(new_entry);
		}
		else
		{
			if (append && eq)
			{
				char *real_entry = ft_strjoin(key, "=");
				char *tmp = real_entry;
				real_entry = ft_strjoin(real_entry, eq + 1);
				free(tmp);
				free(new_entry);
				new_entry = real_entry;
			}
			count = 0;
			while ((*envp)[count]) count++;
			new_env = ft_calloc(count + 2, sizeof(char *));
			i = -1;
			while (++i < count) new_env[i] = (*envp)[i];
			new_env[count] = new_entry;
			free(*envp);
			*envp = new_env;
		}
		free(key);
		arg_idx++;
	}
	return (ret);
}

int	ft_unset(char **args, char ***envp)
{
	int		idx;
	int		count;
	char	**new_env;
	int		i;
	int		j;
	int		arg_idx;
	int		ret;

	if (!args[1])
		return (0);
	ret = 0;
	arg_idx = 1;
	while (args[arg_idx])
	{
		if (args[arg_idx][0] == '-')
		{
			ft_putstr_fd("minishell: unset: ", 2);
			write(2, args[arg_idx], 2);
			ft_putendl_fd(": invalid option", 2);
			ft_putendl_fd("unset: usage: unset [-f] [-v] [-n] [name ...]", 2);
			return (2);
		}
		if (!is_valid_ident(args[arg_idx]) || ft_strchr(args[arg_idx], '='))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[arg_idx], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 0;
			arg_idx++;
			continue ;
		}
		idx = get_env_index(args[arg_idx], *envp);
		if (idx != -1)
		{
			count = 0;
			while ((*envp)[count]) count++;
			new_env = ft_calloc(count, sizeof(char *));
			i = 0;
			j = 0;
			while (i < count)
			{
				if (i != idx)
					new_env[j++] = (*envp)[i];
				else
					free((*envp)[i]);
				i++;
			}
			free(*envp);
			*envp = new_env;
		}
		arg_idx++;
	}
	return (ret);
}
