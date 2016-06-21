/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniature.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 10:30:07 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/21 11:45:37 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <dirent.h>

int	read_file(char **av)
{
	DIR				*rep;
	struct dirent	*file;
	char			*new;
	int				i;

	i = 0;
	if ((rep = opendir("./scenes/")) == NULL)
	{
		ft_putendl_fd("opendir faile\n", 2);
		exit(-1);
	}
	while ((file = readdir(rep)) != NULL && i < 12)
	{
		new = ft_strnew(ft_strlen("./scenes/") + ft_strlen(file->d_name));
		new = ft_strcpy(new, "./scenes/");
		if (file->d_name[0] != '.')
			av[++i] = ft_strdup(ft_strcat(new, file->d_name));
		free(new);
		ft_printf("av[%d] = %s.\n", i, av[i]); // debug a sup a la fin.
	}
	if (closedir(rep) == -1)
		exit(-1);
	return (i);
}
