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

int		check_if_int(char *str)
{
	char	*s;
	int		len;
	int		i;

	i = -1;
	s = "2147483647";
	len = ft_strlen(str);
	if (len < 10 || len > 10)
	{
		ft_strdel(&str);
		return (len < 10 ? 1 : 0);
	}
	else if (len == 10)
	{
		while (str[++i])
		{
			if (str[i] < s[i])
				return (1);
			if (str[i] > s[i])
				return (0);
		}
	}
	ft_strdel(&str);
	return (1);
}

int		check_room_str(char *line)
{
	int i;
	int num;
	int start;

	i = -1;
	num = 0;
	while (line[++i])
	{
		if (i == 0 && (line[i] == '#' || line[i] == 'L'))
			return (0);
		else if (line[i] == ' ' && !ft_isdigit(line[i + 1]))
			return (0);
		if (ft_isdigit(line[i]) && i > 0 && line[i - 1] == ' ')
		{
			num++;
			start = i;
			while (line[++i] && line[i] != ' ')
				if (!ft_isdigit(line[i]))
					return (0);
			if (!check_if_int(ft_strsub(line, start, i - start)))
				return (0);
			i--;
		}
	}
	return (num == 2 ? 1 : 0);
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
		{
			ft_strdel(&(node->name));
			free(node);
			return (0);
		}
	}
	game->room_num++;
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
	if (!check_if_int(ft_strdup(line)))
		return (0);
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
