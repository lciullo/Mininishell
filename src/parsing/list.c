/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:03:58 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/09 14:20:04 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*list_2(int	*start, int *end, char **tab_line);
static void		find_malloc_size(char ** tab_line, int *end, int *start, int *malloc_size);
static void		fill_tab(char **tab_line, char **tokn, int  *start, int *end);
static void		del_delimiteur(t_list **list);

t_list	*create_list(char *line, t_parsing *parsing)
{
	char	**tab_line;
	int		start;
	int		end;
	t_list	*list;
	t_list	*new;

	start = 0;
	end = 0;
	list = NULL;
	(void) parsing;
	tab_line = ft_split(line, ' ');
	if (!tab_line)
		return (free(line), NULL);
	free(line);
	change_tab(tab_line);
	while (start != -1)
	{
		start = end;
		new = list_2(&start, &end, tab_line);
		ft_lstadd_back(&list, new);
	}
	change_list(&list);
	free_array(tab_line);
	if ((parsing->nbr_pipe + parsing->nbr_redir) != 0)
		del_delimiteur(&list);
	return (list);
}

static t_list	*list_2(int	*start, int *end, char **tab_line)
{
	int		malloc_size;
	char	**token;
	t_list	*new;

	malloc_size = 0;
	if (tab_line[*end] == NULL)
	{
		*start = -1;
		return (NULL);
	}
	find_malloc_size(tab_line, end, start, &malloc_size);
	token = malloc(sizeof(char *) * (malloc_size + 1));
	if (!token)
		return (NULL);
	fill_tab(tab_line, token, start, end);
	new = ft_lstnew(token, -1);
	if (!new)
		return (NULL);
	return (new);
}

static void	find_malloc_size(char ** tab_line, int *end, int *start, int *malloc_size)
{
	while (tab_line[*end])
	{
		if ((tab_line[*end][0] == '<' || tab_line[*end][0] == '>' \
		|| tab_line[*end][0] == '|'))
		{
			*end = *end + 1;
			*malloc_size = 1;
			break ;
		}
		else if (*end != 0 && tab_line[*end - 1] && \
		(tab_line[*end - 1][0] == '<' || tab_line[*end - 1][0] == '>'))
		{
			*end = *end + 1;
			*malloc_size = 1;
			break ;
		}
		else if (tab_line[*end + 1] && (tab_line[*end + 1][0] == '<' \
		|| tab_line[*end + 1][0] == '>' || tab_line[*end + 1][0] == '|'))
		{
			*end = *end + 1;
			*malloc_size = *end - *start;
			break ;
		}
		*end = *end + 1;
	}
	if (*malloc_size == 0) 
		*malloc_size = (*end - *start) + 1;
}

static void	fill_tab(char **tab_line, char **token, int  *start, int *end)
{
	int	i;

	i = 0;
	while (*start < *end)
	{
		token[i] = ft_strdup(tab_line[*start]);
		if (!token[i])
			return ;
		*start = *start + 1;
		i++;
	}
	token[i] = NULL;
}

static void	del_delimiteur(t_list **list)
{
	t_list	*copy;
	
	if (*list == NULL || list == NULL)
		return ;
	copy = (*list);
	if (copy->type == -1)
	{
		*list = copy->next;
		free(copy->data);
		free(copy);
		del_delimiteur(list);
	}
	copy = *list;
	del_delimiteur(&copy->next);
}
