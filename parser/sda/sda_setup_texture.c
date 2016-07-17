/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 18:02:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 22:47:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "texture.h"
#include "objects.h"
#include "libft.h"
#include <stdlib.h>

static int sda_setup_texture_fake(t_obj *obj, const char *filepath,
	t_texture **textures)
{
	t_texture	*tex;

	if (!(tex = malloc(sizeof(t_texture))))
		return (-1);
	tex->filepath = ft_strdup(filepath);
	tex->surface = NULL;
	tex->next = *textures;
	*textures = tex;
	rt_obj_set_texture(obj, tex);
	return (1);
}

int			sda_setup_texture(t_sda *e, t_obj *obj, char **av)
{
	t_texture	*tex;
	char		*filepath;

	if (!(filepath = ft_strunsplit((const char **)(unsigned long)av, ' ')))
		return (-2);
	if ((tex = texture_search(e->rt->textures, filepath)))
		free(filepath);
	else if (e->rt->settings.fake_texture_load)
		return (sda_setup_texture_fake(obj, filepath, &e->rt->textures));
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
