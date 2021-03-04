/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:39:58 by slescure          #+#    #+#             */
/*   Updated: 2019/11/11 20:14:58 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int			i;
	t_list		*current;

	i = 0;
	current = lst;
	if (lst)
	{
		while (current->next)
		{
			i++;
			current = current->next;
		}
		i++;
		return (i);
	}
	return (0);
}
