/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:54:05 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/07 11:54:08 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		reading_lem_in(char *line, t_lem_in *game, int *type)
{
	char	*ptr;

	ptr = ft_strtrim(line);
	if (ptr[0] != '#')
	{
		if (ft_strchr(ptr, ' '))
		{
			if (!room_valid(ptr, game, type))
				return (0);
		}
		else if (ft_strchr(ptr, '-'))
		{
			if (!link_valid(ptr, game, type))
				return (0);
		}
		else if (!ants_valid(ptr, game, type))
			return (0);
	}
	else if (!command_valid(ptr, game, type))
		return (0);
	if (ptr)
		free (ptr);
	return (1);
}

int		main(void)
{
	char		*line;
	t_lem_in	*game;
	int			type;

	game = (t_lem_in *)malloc(sizeof(t_lem_in) * 1);
	game->node = NULL;
	game->room = NULL;
	game->ants = 0;
	game->start = 0;
	game->end = 0;
	game->room_num = 0;
	type = ANTS;
	while (get_next_line(0, &line))
	{
		if (!reading_lem_in(line, game, &type))
		{
			ft_printf("ERROR\n");
			//clean_game(&game);
			ft_strdel(&line);//???
			return (0);//return error
		}
		ft_strdel(&line);
	}
	//lem_in(game);
	//clean_game(&game);
}