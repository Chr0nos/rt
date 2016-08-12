/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 12:52:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/12 14:10:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

void	texture_remove(t_texture *tex)
{
	if (!tex)
		return ;
	if (tex->prev)
	{
		tex->prev->next = tex->next;
		tex->next->prev = tex->prev;
	}
	textures_freetex(tex);
}
