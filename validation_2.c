/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 14:34:22 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/26 14:34:29 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_link_str(char *line)
{
	int i;
	int	name;

	i = -1;
	name = 0;
	while (line[++i])
	{
		if (i == 0 || (i > 0 && line[i - 1] == '-'))
		{
			if (line[i] != '#' && line[i] != 'L')
				name++;
			else
				return (0);
		}
	}
	return (name == 2 ? 1 : 0);
}

int		link_valid(char *line, t_lem_in *game, int *type)
{
	int ret;

	if (*type == ANTS)
		game->error = !game->ants ? 5 : 6;
	if (*type == START || *type == END)
		game->error = 3;
	if (!(ret = check_link_str(line)))
		game->error = 1;
	if (*type == ANTS || *type == START ||
		*type == END || !ret)
		return (0);
	if (*type != LINK)
	{
		if (!game->start || !game->end)
		{
			game->error = 3;
			return (0);
		}
		*type = LINK;
		create_room_array(game);
	}
	if (!manage_links(game, line))
		return (0);
	return (1);
}

int		ants_valid(char *line, t_lem_in *game, int *type)
{
	int i;

	i = -1;
	if (*type != ANTS || game->ants != 0)
	{
		game->error = 12;
		return (0);
	}
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
		{
			game->error = 2;
			return (0);
		}
	}
	if (!check_if_int(ft_strdup(line)))
	{
		game->error = 2;
		return (0);
	}
	game->ants = ft_atoi(line);
	if (!game->ants)
		game->error = 5;
	return (game->ants > 0 ? 1 : 0);
}

int		command_valid(char *line, t_lem_in *game, int *type)
{
	if (ft_strequ(line, "##start"))
	{
		if (*type == LINK || game->start != 0 || !game->ants)
		{
			game->error = *type == LINK ? 12 : game->error;
			game->error = game->start != 0 ? 4 : game->error;
			game->error = !game->ants ? 5 : game->error;
			return (0);
		}
		*type = START;
		game->start = 1;
	}
	if (ft_strequ(line, "##end"))
	{
		if (*type == LINK || game->end != 0 || !game->ants)
		{
			game->error = *type == LINK ? 12 : game->error;
			game->error = game->end != 0 ? 4 : game->error;
			game->error = !game->ants ? 5 : game->error;
			return (0);
		}
		*type = END;
		game->end = 1;
	}
	return (1);
}
