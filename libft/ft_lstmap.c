/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:50:46 by yooshima          #+#    #+#             */
/*   Updated: 2024/05/05 11:42:54 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;

	new_lst = NULL;
	if (lst == NULL)
		return (NULL);
	while (1)
	{
		node = ft_lstnew(f(lst -> content));
		if (node == NULL)
		{
			ft_lstdelone(node, del);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		if (lst -> next == NULL)
			break ;
		lst = lst -> next;
	}
	return (new_lst);
}
