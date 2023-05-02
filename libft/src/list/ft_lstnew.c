/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:12 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/02 12:36:30 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **token, int type)
{
	t_list	*tab;

	(void)type;
	tab = malloc(sizeof(t_list));
	if (!(tab))
		return (NULL);
	tab -> data = token;
	tab -> type = 0;
	tab -> next = NULL;
	return (tab);
}


t_lst_env	*ft_lstnew_env(char *variable, char *value)
{
	t_lst_env	*data;

	data = malloc(sizeof(t_lst_env));
	if (!(data))
		return (NULL);
	data ->variable = variable;
	data ->value = value;
	data ->equal = 0;
	data ->next = NULL;
	return (data);
}
