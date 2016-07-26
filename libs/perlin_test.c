/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 00:05:48 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/27 00:16:13 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "draw.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_v2f		geo;
	double		d;
	double		zoom;
	char		*str;

	zoom = (ac == 2) ? ft_atod(av[1]) : 1.0;
	geo.x = 45.0f;
	geo.y = 30.1f;
	while (geo.x > 1.0f)
	{
		d = draw_perlin_noise(geo, 1.0f);
		str = ft_dtoa(d, 6);
		ft_putendl(str);
		free(str);
		geo.x *= 0.5f;
	}
	return (0);
}
