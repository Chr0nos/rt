/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_sdisable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 16:40:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:57:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "shaders.h"
#include "libft.h"
#include "objects.h"

static const char	*sda_sdisable_getshadername(t_sda_shader *x,
	t_shader *shader)
{
	int		p;

	if (!shader)
		return (NULL);
	p = SDA_COUNT_SHADER;
	while (p--)
		if (x[p].shader == (void*)shader->exec)
			return (x[p].name);
	return (NULL);
}

static char			*sda_export_sdisable_real(t_obj *obj)
{
	t_sda_shader		x[SDA_COUNT_SHADER];
	t_shader			*shader;
	char				*str;
	char				*tmp;
	const char			*name;

	str = NULL;
	sda_sdisable_init(x);
	shader = obj->shader->shader;
	while (shader)
	{
		if (!shader->enabled)
		{
			tmp = str;
			name = sda_sdisable_getshadername(x, shader);
			if (name)
			{
				str = (str) ? ft_strmjoin(3, str, " ", name) : ft_strdup(name);
				if (tmp)
					free(tmp);
			}
		}
		shader = shader->next;
	}
	return (str);
}

char				*sda_export_sdisable(t_obj *obj, t_sda_export *e)
{
	(void)e;
	if (!(obj->cfgbits & SDB_SDISABLE))
		return (NULL);
	return (sda_export_sdisable_real(obj));
}
