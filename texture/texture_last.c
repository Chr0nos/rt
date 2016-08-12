/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 13:01:44 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/12 13:02:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

t_texture	*texture_last(t_texture *lst)
{
	while (lst)
		lst = lst->next;
	return (lst);
}
