/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 11:45:12 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/16 11:45:25 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"

int   test_font(void)
{
  if (TTF_Init() == -1)
  {
    ft_printf("Erreur initialisation TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  else
    ft_putstr("TTF_Init : okay.\n");
  return (1);
}
