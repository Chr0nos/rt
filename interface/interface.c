/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 11:45:12 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/16 13:17:35 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"


/*
 ** Le moment venu penser a :
 ** add TTF_CLoseFont(police);
 ** add TTF_Quit;
 */
 
static SDL_Color	*define_color(SDL_Color *color, Uint8 r, Uint8 g, Uint8 b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

void init_ttf(void)
{
	if (TTF_Init() == -1)
	{
		ft_printf("Erreur initialisation TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	else
		ft_putstr("TTF_Init : okay.\n");
}

int   test_font(t_rt *rt)
{
	TTF_Font *police;
	SDL_Surface *texte = NULL;
	SDL_Rect position;
	SDL_Color color;

	police = NULL;
	position.x = 10;
	position.y = 10;
	define_color(&color, 120, 50, 200);
	if ((police = TTF_OpenFont("interface/font/another.ttf", 65)) != NULL)
	{
		texte = TTF_RenderText_Blended(police, "Merry Christmas !", color);
		SDL_BlitSurface(texte, NULL, rt->sys.screen, &position);
	}
	else
		ft_putstr("fail font\n");
	return (1);
}
