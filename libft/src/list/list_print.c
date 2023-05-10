/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:12 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/09 14:48:34 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	list_print_env(t_lst_env *lst_env)
{
	t_lst_env	*copy;

	copy = lst_env;
	while (copy)
	{
		ft_dprintf(1, "%s=%s\n", copy->variable, copy->value);
		copy = copy->next;
	}
}

void	in_exec_print_list(t_list *lst)
{
	int	i;

	i = 0;
	ft_dprintf(1, "IN PRINT LIST\n");
	ft_dprintf(1, "===============================\n");
	while (lst != NULL)
	{
		i = 0;
		while (lst->data[i] != NULL)
		{
			ft_dprintf(1, "row[%s]\n", lst->data[i]);
			i++;
		}
		lst = lst->next;
	}
	ft_dprintf(1, "===============================\n");
}
