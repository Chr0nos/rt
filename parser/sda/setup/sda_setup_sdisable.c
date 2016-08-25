/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_sdisable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 15:17:39 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/25 23:36:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "shaders.h"
#include "libft.h"

void		*sda_setup_getshader_addr(t_shader *s, void *item)
{
	while (s)
	{
		if (item == (void*)(unsigned long)s->exec)
			return (s);
		s = s->next;
	}
	return (NULL);
}

int			sda_setup_sdisable_real(t_shader *shader, void *target)
{
	if (shader)
	{
		if ((void*)shader->exec == target)
		{
			shader->enabled = 0;
			return (1);
		}
		return (sda_setup_sdisable_real(shader->next, target));
	}
	return (0);
}

static int	sda_setup_sdisable_shader(t_sda_shader *x, int p,
	const char *name, t_obj *obj)
{
	while (p--)
	{
		if (!ft_strcmp(x->name, name))
			return (sda_setup_sdisable_real(obj->shader->shader, x->shader));
		x++;
	}
	return (0);
}

void		sda_sdisable_init(t_sda_shader *x)
{
	x[0] = (t_sda_shader){"diffuse", (void*)&rt_light_pow};
	x[1] = (t_sda_shader){"specular", (void*)&rt_specular_pow};
	x[2] = (t_sda_shader){"shadow", (void*)&shader_shadow};
	x[3] = (t_sda_shader){"normal", (void*)&shader_normalmap};
	x[4] = (t_sda_shader){"reflect", (void*)&shader_reflection};
	x[5] = (t_sda_shader){"texture", (void*)&shader_texture};
}

int			sda_setup_sdisable(t_sda *e, t_obj *obj, char **av)
{
	int				p;
	t_sda_shader	x[SDA_COUNT_SHADER];

	sda_sdisable_init(x);
	(void)e;
	p = 0;
	while (av[p])
	{
		if (!(sda_setup_sdisable_shader(x, SDA_COUNT_SHADER, av[p], obj)))
		{
			ft_putendl_fd("error: shader not found", 2);
			return (-1);
		}
		p++;
	}
	return (1);
}
