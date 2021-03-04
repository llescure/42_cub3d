/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:26:23 by slescure          #+#    #+#             */
/*   Updated: 2019/11/11 20:15:16 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*element;

	if (!(element = malloc(sizeof(element))))
		return (NULL);
	element->next = NULL;
	element->content = content;
	return (element);
}
