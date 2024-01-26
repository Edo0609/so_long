/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:29:58 by epenaloz          #+#    #+#             */
/*   Updated: 2023/12/26 23:54:18 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*lst_index;
	void	*n_content;

	new_list = NULL;
	while (lst)
	{
		n_content = f(lst -> content);
		lst_index = ft_lstnew(n_content);
		if (lst_index == NULL)
		{
			del(n_content);
			ft_lstclear(&new_list, del);
			free(new_list);
			return (NULL);
		}
		ft_lstadd_back(&new_list, lst_index);
		lst = lst -> next;
	}
	return (new_list);
}
