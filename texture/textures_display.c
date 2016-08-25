/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 16:14:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/25 06:20:34 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

void	textures_display(t_texture *t)
{
	if (!t)
		return ;
	ft_printf("#tex: %s\n", t->filepath);
	textures_display(t->next);
}
