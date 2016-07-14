/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 18:02:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 17:33:49 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "texture.h"
#include "objects.h"
#include "libft.h"
#include <stdlib.h>

int					sda_setup_texture(t_sda *e, t_obj *obj, char **av)
{
	t_texture	*tex;
	char		*filepath;

	filepath = ft_strunsplit((const char **)(unsigned long)av, ' ');
	if ((tex = texture_search(e->rt->textures, filepath)))
		free(filepath);
	else if ((tex = texture_create(&e->rt->textures, filepath)))
		;
	else
	{
		ft_putendl_fd("error: failed to load texture", 2);
		free(filepath);
		return (-1);
	}
	return (rt_obj_set_texture(obj, tex));
}
