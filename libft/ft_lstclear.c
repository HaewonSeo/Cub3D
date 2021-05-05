/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:38:15 by haseo             #+#    #+#             */
/*   Updated: 2020/11/23 02:46:01 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *cur;
	t_list *tmp;

	if (!lst || !del)
		return ;
	cur = *lst;
	while (cur)
	{
		tmp = cur->next;
		ft_lstdelone(cur, del);
		cur = tmp;
	}
	*lst = NULL;
}
