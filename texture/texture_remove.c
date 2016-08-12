/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 12:52:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/12 16:26:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

void	texture_remove(t_texture **tex)
{
	t_texture	*t;

	t = *tex;
	if (!t)
		return ;
	if (t->prev)
		t->prev->next = t->next;
	else
		*tex = t->next;
	if (t->next)
		t->next->prev = t->prev;
	textures_freetex(t);
}
