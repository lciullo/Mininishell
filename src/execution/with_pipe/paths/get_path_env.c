/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:21:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/31 14:37:12 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char **env)
{
	char	*path;
	int		row;

	path = NULL;
	row = 0;
	while (env[row])
	{
		if (ft_strncmp("PATH=", env[row], 5) == 0)
			path = env[row];
		row++;
	}
	if (!path)
		return (NULL);
	path += 5;
	return (path);
}

char	*check_cmd_acess(char **paths, char *cmd)
{
	char	*join_slash;
	char	*cmd_with_path;
	int		row;

	row = 0;
	join_slash = NULL;
	cmd_with_path = NULL;
	if (cmd != NULL && access(cmd, X_OK | F_OK) == 0) //appeler acess dans une autre fonction
		return (cmd);
	while (paths[row])
	{
		join_slash = ft_strjoin(paths[row], "/");
		if (!join_slash)
			return (NULL);
		cmd_with_path = ft_strjoin(join_slash, cmd);
		if (!cmd_with_path)
			return (free(join_slash), NULL);
		free(join_slash);
		if (access(cmd_with_path, X_OK) == 0)
			return (cmd_with_path); //rappeler
		free(cmd_with_path);
		row++;
	}
	return (NULL);
}
/*Voir si on doit free ca
static void	env_paths_issue(t_exec *data)
{
	if (data->pids)
		free(data->pids);
	if (data->pids)
		free(data->fd_heredoc);
}*/

int	get_path_env(t_exec *data, char **env)
{
	data->paths = find_path(env);
	if (!data->paths)
	{
		//doit on le free ?
		perror("Environment path not found");
		return (-1);
	}
	data->env_path = ft_split(data->paths, ':');
	if (!data->env_path)
	{
		//doit on le free ?
		perror("issue in split to find environnement");
		return (-1);
	}
	return (0);
}
