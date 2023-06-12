/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:20:07 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/12 14:27:45 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_double_quotes(t_expand *utils, int *i, int *start);
static void	handle_single_quote(t_expand *utils, int *i);
static int	handle_dollar_sign(t_expand *utils, int *i, int *start);
static char	*get_var(t_expand *utils, int *i);

char	*expand(char *line, t_env *lst_env)
{
	int			i;
	int			start;
	t_expand	utils;

	i = 0;
	start = 0;
	utils.line = line;
	utils.env = lst_env;
	utils.new_line = ft_calloc(1, 1);
	if (!(utils.new_line))
		return (free(line), NULL);
	while (line[i])
	{
		if (utils.line[i] == '\"')
		{
			if (handle_double_quotes(&utils, &i, &start) == FAILURE)
				return (NULL);
		}
		else if (line[i] == '\'')
			handle_single_quote(&utils, &i);
		else if (line[i] == '$' && (ft_isalnum(line[i + 1]) == true || \
		line[i + 1] == '_' || line[i + 1] == '?' || line[i + 1] == '\'' \
		|| line[i + 1] == '\"'))
		{
			if (handle_dollar_sign(&utils, &i, &start) == FAILURE)
				return (NULL);
		}
		else if (line[i])
			i++;
	}
	if (line[start])
		utils.new_line = ft_strjoin_b(utils.new_line, line, start, i);
	return (free(line), utils.new_line);
}

static int	handle_double_quotes(t_expand *utils, int *i, int *start)
{
	if (utils->line[*i] == '\"')
		*i = *i + 1;
	while (utils->line[*i])
	{	
		if (utils->line[*i] == '\"')
			break ;
		if (utils->line[*i] == '$' && \
		(ft_isalnum(utils->line[*i + 1]) == true || \
		utils->line[*i + 1] == '_' || utils->line[*i + 1] == '?'))
		{
			if (handle_dollar_sign(utils, i, start) == FAILURE)
				return (FAILURE);
		}
		else if (utils->line[*i])
			*i = *i + 1;
	}
	if (utils->line[*i] == '\"')
		*i = *i + 1;
	return (SUCCESS);
}

static void	handle_single_quote(t_expand *utils, int *i)
{
	skip_quote(utils->line, i, utils->line[*i]);
	if (utils->line[*i] == '\'')
		*i = *i + 1;
}

static int	handle_dollar_sign(t_expand *utils, int *i, int *start)
{
	if (*i - *start != 0)
	{
		utils->new_line = ft_strjoin_b(utils->new_line, \
		utils->line, *start, *i);
		if (!(utils->new_line))
			return (FAILURE);
	}
	if (ft_isalpha(utils->line[*i + 1]) == 1 || utils->line[*i + 1] == '_')
	{
		utils->new_line = get_var(utils, i);
		if (!(utils->new_line))
			return (free(utils->line), FAILURE);
	}
	else
		*i = *i + 2;
	*start = *i;
	return (SUCCESS);
}

static char	*get_var(t_expand *utils, int *i)
{
	int		start;
	int		j;
	char	*name_var;

	j = 0;
	if (utils->line[*i] == '$')
		*i = *i + 1;
	start = *i;
	while (utils->line[*i] && (ft_isalnum(utils->line[*i]) == true \
	|| utils->line[*i] == '_'))
		*i = *i + 1;
	name_var = malloc(sizeof(char) * ((*i - start) + 1));
	if (!(name_var))
		return (free(utils->new_line), NULL);
	while (start < *i)
	{
		name_var[j] = utils->line[start];
		j++;
		start++;
	}
	name_var[j] = '\0';
	utils->new_line = check_var(name_var, utils->env, utils->new_line);
	free(name_var);
	if (!(utils->new_line))
		return (NULL);
	return (utils->new_line);
}
