/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 12:38:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/12 14:21:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

static int		textures_lstsearch(t_list *lst, const void *content)
{
	while (lst)
	{
		if (lst->content == content)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void			textures_cleanup(t_obj *node, t_texture **lst)
{
	t_list		*used;
	t_texture	*x;

	used = textures_used(node);
	x = *lst;
	while (x)
	{
		if (!textures_lstsearch(used, x))
			texture_remove(x);
		x = x->next;
	}
}
