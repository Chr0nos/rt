/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_skybox.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 13:40:27 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/13 04:02:59 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "texture.h"
#include "objects.h"
#include "libft.h"
#include <stdlib.h>

int					sda_setup_skybox(t_sda *e, t_obj *obj, char **av)
{
	t_texture	*tex;
	char		*filepath;

	if (!(filepath = ft_strunsplit((const char **)(unsigned long)av, ' ')))
		return (-2);
	if ((tex = texture_search(*e->rt->textures, filepath)))
		free(filepath);
	else if (e->rt->settings.fake_texture_load)
		tex = sda_setup_texture_fake(filepath, e->rt->textures);
	else if ((tex = texture_create(e->rt->textures, filepath)))
		;
	else
	{
		ft_putendl_fd("error: failed to load texture", 2);
		free(filepath);
		return (-1);
	}
	e->rt->settings.skybox = tex;
	((t_setting*)obj->content)->skybox = tex;
	return (1);
}
