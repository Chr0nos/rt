/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_sdisable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 15:17:39 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 15:56:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "shaders.h"
#include "libft.h"

static int	sda_setup_sdisable_real(t_obj *obj, t_shader *shader, void *target)
{
	if (!shader)
		return (0);
	if ((void*)shader->exec == target)
	{
		shader->enabled = 0;
		return (1);
	}
	return (sda_setup_sdisable_real(obj, shader->next, target));
}

static int	sda_setup_sdisable_shader(t_obj *obj, t_sda_shader *x, int p,
	const char *name)
{
	while (p--)
	{
		if (!ft_strcmp(x->name, name))
		{
			ft_printf("disabling shader: %s\n", name);
			return (sda_setup_sdisable_real(obj, obj->shader->shader,
				x->shader));
		}
		x++;
	}
	return (0);
}

int			sda_setup_sdisable(t_sda *e, t_obj *obj, char **av)
{
	int				p;
	t_sda_shader	x[] = {
			(t_sda_shader){"diffuse", (void*)&rt_light_pow},
			(t_sda_shader){"specular", (void*)&rt_specular_pow},
			(t_sda_shader){"shadow", (void*)&shader_shadow}
	};

	(void)e;
	p = 0;
	while (av[p])
	{
		if (!(sda_setup_sdisable_shader(obj, x, 3, av[p])))
		{
			ft_putendl_fd("error: shader not found", 2);
			return (-1);
		}
		p++;
	}
	return (1);
}
