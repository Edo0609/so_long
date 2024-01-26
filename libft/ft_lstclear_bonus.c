/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:25:33 by epenaloz          #+#    #+#             */
/*   Updated: 2023/10/13 19:40:37 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next_n;

	node = *lst;
	while (node != NULL)
	{
		next_n = node -> next;
		ft_lstdelone(node, del);
		node = next_n;
	}
	*lst = NULL;
}
