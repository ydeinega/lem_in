/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:08:25 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/07 16:08:27 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_room_str(char *line)
{
	int i;
	int num;
	int name;

	i = -1;
	num = 0;
	name = 0;
	while (line[++i])
	{
		if (i == 0 && line[i] != '#' && line[i] != 'L')
			name++;
		if (line[i] == ' ' && !ft_isdigit(line[i + 1]))
			return (0);
		if (ft_isdigit(line[i]) && i > 0 && line[i - 1] == ' ')
		{
			num++;
			while (line[++i] && line[i] != ' ')
			{
				if (!ft_isdigit(line[i]))
					return (0);
			}
			i--;
		}
	}
	return (num == 2 && name == 1 ? 1 : 0);
}

int		check_link_str(char *line)
{
	int i;
	int	name;

	i = -1;
	name = 0;
	while (line[++i])
	{
		if ((i == 0 || (i > 0 && line[i - 1] == '-'))
			&& line[i] != '#' && line[i] != 'L')
			name++;
	}
	return (1);
}

int		room_valid(char *line, t_lem_in *game, int *type)
{
	if (*type == LINK || !check_room_str(line))
		return (0);
	if (*type == ANTS)
	{
		if (game->ants == 0)
			return (0);
		*type = ROOM;
		//create head for node
	}
	else
	{
		if (!game->node)
			return (0);
		//create lst element and push it to the beginning of the list
	}
	return (1);
}

int		link_valid(char *line, t_lem_in *game, int *type)
{
	if (*type == ANTS || !check_link_str(line))
		return (0);
	if (*type != LINK)
	{
		if (!game->start || !game->end)
			return (0);
		//create array instead of list
	}	
	return (1);
}

int		ants_valid(char *line, t_lem_in *game, int *type)
{
	int i;

	i = -1;
	if (*type != ANTS && game->ants != 0)
		return (0);
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
	}
	game->ants = ft_atoi(line);
	return (game->ants > 0 ? 1 : 0);
}

int		command_valid(char *line, t_lem_in *game, int *type)
{
	return (1);
}
