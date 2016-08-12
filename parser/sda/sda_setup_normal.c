/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 17:46:46 by alhote            #+#    #+#             */
/*   Updated: 2016/08/12 17:38:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "texture.h"
#include "objects.h"
#include "libft.h"
#include <stdlib.h>

int					sda_setup_normal(t_sda *e, t_obj *obj, char **av)
{
	t_texture	*tex;
	char		*filepath;

	if (!(filepath = ft_strunsplit((const char **)(unsigned long)av, ' ')))
		return (-2);
	if ((tex = texture_search(*e->rt->textures, filepath)))
		free(filepath);
	else if (e->rt->settings.fake_texture_load)
	{
		tex = sda_setup_texture_fake(filepath, e->rt->textures);
		rt_obj_set_normal(obj, tex);
		return (1);
	}
	else if ((tex = texture_create(e->rt->textures, filepath)))
		;
	else
	{
		ft_putendl_fd("error: failed to load texture", 2);
		free(filepath);
		return (-1);
	}
	return (rt_obj_set_normal(obj, tex));
}
