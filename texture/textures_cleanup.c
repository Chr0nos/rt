/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 12:38:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 22:35:55 by snicolet         ###   ########.fr       */
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

/*
** this function just delete all unused textures
** it's used to clean the extra textures not needed anymore by the menu
*/

void			textures_cleanup(t_obj *node, t_texture **lst)
{
	t_list		*used;
	t_texture	*x;

	textures_used_display(node);
	used = textures_used(node);
	x = *lst;
	while (x)
	{
		if (!textures_lstsearch(used, x))
			x = texture_remove(x, lst);
		else
			x = x->next;
	}
}
