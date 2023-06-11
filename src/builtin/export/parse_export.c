/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:08 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/10 19:06:32 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	first_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (SUCCESS);
	else
		return (FAILURE);
}

int	last_char(char *name)
{
	size_t	end;
	char	c;

	if (ft_strlen(name) > 1)
		end = ft_strlen(name) - 1;
	else
		end = 1;
	c = name[end];
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '+') || \
		(c >= '0' && c <= '9') || (c == '_'))
		return (SUCCESS);
	return (FAILURE);
}

static int	is_valid(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') \
	|| (c >= 'A' && c <= 'Z') || (c == '_') || (c == '='))
		return (SUCCESS);
	else
		return (FAILURE);
}

static	int	is_valid_syntax(char *name)
{
	size_t	i;
	size_t	end;

	i = 1;
	if (ft_strlen(name) > 1)
		end = ft_strlen(name) - 1;
	else
		end = 1;
	while (name[i] != '\0' && i < end)
	{
		if (is_valid(name[i]) == FAILURE)
		{
			ft_dprintf(2, "export '%s' : not a valid identifier\n", name);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	is_equal(char *name)
{
	size_t	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '=')
			return (EQUAL);
		i++;
	}
	return (NO_EQUAL);
}

int	parse_name(char *name)
{
	char	*tmp;
	size_t	start;

	tmp = NULL;
	start = begin_of_name(name);
	tmp = ft_strndup(tmp, name, start);
	if (!tmp)
		return (FAILURE);
	if (is_valid_syntax(tmp) == FAILURE)
	{
		free(tmp);
		return (FAILURE);
	}
	if (first_char(tmp[0]) == FAILURE)
	{
		ft_dprintf(2, "export '%s': not a valid identifier\n", name);
		free(tmp);
		return (FAILURE);
	}
	if (last_char(tmp) == FAILURE)
	{
		ft_dprintf(2, "export '%s': not a valid identifier\n", name);
		free(tmp);
		return (FAILURE);
	}
	free(tmp);
	return (SUCCESS);
}
