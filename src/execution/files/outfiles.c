/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:32:29 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/26 15:44:12 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	is_outfile_open(t_exec *data)
{
	if (data->outfile > 2)
		close(data->outfile);
}

static	int	manage_outfile(int type, char *outfile, t_exec *data)
{
	is_outfile_open(data);
	if (type == OUTFILE)
		data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		data->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	data->out_dir++;
	if (data->outfile == -1)
	{	
		ft_close(data->infile);
		ft_close(data->new_fd[0]);
		ft_close(data->new_fd[1]);
		perror("Open outfile issu");
		return (-1);
	}
	return (0);
}

int	loop_for_outfile(t_list *list, t_exec *data)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == OUTFILE || list->type == APPEND)
		{
			if (manage_outfile(list->type, list->data[0], data) == -1)
				return (-1);
		}
		list = list->next;
	}
	return (0);
}
