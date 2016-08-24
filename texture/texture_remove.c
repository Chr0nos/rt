/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 12:52:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 20:59:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

/*
** remove the texture of the list
** return the new/current root of the list
** edit the root by itself, the return is a security (see textures_cleanup)
*/

t_texture	*texture_remove(t_texture *t, t_texture **root)
{
	if (!t)
		return (NULL);
	if (t == *root)
		*root = t->next;
	if (t->next)
		t->next->prev = t->prev;
	if (t->prev)
		t->prev->next = t->next;
	textures_freetex(t);
	return (*root);
}
