/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:57:51 by alhote            #+#    #+#             */
/*   Updated: 2016/06/21 19:36:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

t_shaders			*init_shader(unsigned int nbr_fshaders)
{
	t_shaders	*s;

	if ((s = malloc(sizeof(t_shaders))))
	{
		//printf("great\n");
		s->nbr_fshaders = nbr_fshaders;
		//printf("%d\n", s->nbr_fshaders);
		s->vertex_shader = 0;
		s->fragment_shader = malloc((sizeof(void*) * nbr_fshaders));
		return (s);
	}
	//printf("nope\n");
	return (0);
}

int					exec_fshaders(t_shaders *s, t_render *r, t_obj *o)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (1);
	printf("toto%d\n", s->nbr_fshaders);
	while (i < s->nbr_fshaders)
	{
		if (s->fragment_shader[i])
			printf("lol\n");
		else
			printf("zob\n");
		r->light_power = s->fragment_shader[i](r, o);
		++i;
	}
	if (i != 0)
		return (0);
	return (1);
}
