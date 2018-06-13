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

int		room_valid(char *line, t_lem_in *game, int *type)
{
	t_room_lst	*node;

	node = NULL;
	if (*type == LINK || !check_room_str(line) || !game->ants)
		return (0);
	if (!game->node)
		game->node = create_node(line, type);
	else
	{
		node = create_node(line, type);
		if (!add_node_lst(&(game->node), node))
			return (0);
	}
	game->room_num++;
	// node = game->node;
	// while (node)
	// {
	// 	ft_printf("name = |%s| ", node->name);
	// 	ft_printf("point = (%i,%i) ", node->pt.i, node->pt.j);
	// 	ft_printf("type = %i\n", node->type);
	// 	node = node->next;
	// }
	return (1);
}

int		link_valid(char *line, t_lem_in *game, int *type)
{
	if (*type == ANTS || *type == START || *type == END || !check_link_str(line))
		return (0);
	if (*type != LINK)
	{
		if (!game->start || !game->end)
			return (0);
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
	if (ft_strequ(line, "##start"))
	{
		if (*type == LINK || game->start != 0 || !game->ants)
			return (0);
		*type = START;
		game->start = 1;
	}
	if (ft_strequ(line, "##end"))
	{
		if (*type == LINK || game->end != 0 || !game->ants)
			return (0);
		*type = END;
		game->end = 1;
	}
	return (1);
}
