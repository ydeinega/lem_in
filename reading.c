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

void		error(char *line, char *ptr, t_lem_in *game)
{
	if (line)
		ft_strdel(&line);
	if (ptr)
		ft_strdel(&ptr);
	if (game)
		clean_game(game);
	if (game->error >= 0)
		ft_printf("ERROR: %s\n", g_error[game->error]);
	else
		ft_printf("ERROR\n");
	exit(1);
}

void		reading_lem_in(char *line, t_lem_in *game, int *type)
{
	char	*ptr;

	ptr = ft_strtrim(line);
	if (ptr[0] != '#')
	{
		if (ft_strchr(ptr, '-'))
		{
			if (!link_valid(ptr, game, type))
				error(line, ptr, game);
		}
		else if (ft_strchr(ptr, ' '))
		{
			if (!room_valid(ptr, game, type))
				error(line, ptr, game);
		}
		else if (!ants_valid(ptr, game, type))
			error(line, ptr, game);
	}
	else if (!command_valid(ptr, game, type))
		error(line, ptr, game);
	add_info(game, ptr);
	if (ptr)
		ft_strdel(&ptr);
}

void		add_info(t_lem_in *game, char *ptr)
{
	t_list	*tmp;

	tmp = ft_lstnew(ptr, ft_strlen(ptr) + 1);
	if (game->info)
		ft_lstaddb(&(game->info), tmp);
	else
		game->info = tmp;
}

t_lem_in	*create_game(void)
{
	t_lem_in	*game;

	game = (t_lem_in *)malloc(sizeof(t_lem_in) * 1);
	if (!game)
		return (NULL);
	game->ants = 0;
	game->room_num = 0;
	game->start = 0;
	game->end = 0;
	game->error = -1;
	game->node = NULL;
	game->room = NULL;
	game->info = NULL;
	return (game);
}

int			main(void)
{
	char		*line;
	t_lem_in	*game;
	int			type;
	int			ret;

	line = NULL;
	type = ANTS;
	game = create_game();
	while ((ret = get_next_line(0, &line)) > 0)
	{
		reading_lem_in(line, game, &type);
		ft_strdel(&line);
	}
	if (ret < 0 || type != LINK)
	{
		game->error = ret < 0 ? 8 : 7;
		error(line, NULL, game);
	}
	if (!lem_in(game))
	{
		game->error = 10;
		error(line, NULL, game);
	}
	clean_game(game);
}
