/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:44:55 by alhote            #+#    #+#             */
/*   Updated: 2016/06/30 17:09:02 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

unsigned int		to_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	r = (r > 255 ? 255 : r);
	g = (g > 255 ? 255 : g);
	b = (b > 255 ? 255 : b);
	return ((r << 16) | (g << 8) | (b));
}

unsigned int		blend_lighten(unsigned int a, unsigned int b)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = (R(a) > R(b) ? R(a) : R(b));
	green = (G(a) > G(b) ? G(a) : G(b));
	blue = (B(a) > B(b) ? B(a) : B(b));
	return (to_rgb(red, green, blue));
}

unsigned int		blend_darken(unsigned int a, unsigned int b)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = (R(a) < R(b) ? R(a) : R(b));
	green = (G(a) < G(b) ? G(a) : G(b));
	blue = (B(a) < B(b) ? B(a) : B(b));
	return (to_rgb(red, green, blue));
}

unsigned int		blend_add(unsigned int a, unsigned int b)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = R(a) + R(b);
	green = G(a) + G(b);
	blue = B(a) + B(b);
	return (to_rgb(red, green, blue));
}

unsigned int		blend_multiply(unsigned int a, unsigned int b)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = (R(a) * R(b)) / 255;
	green = (G(a) * G(b)) / 255;
	blue = (B(a) * B(b)) / 255;
	return (to_rgb(red, green, blue));
}
