/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:38 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/07 11:52:41 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "./libft/libft.h"
# define START 1
# define END 2
# define ANTS 0
# define ROOM 3
# define LINK 4

typedef struct			s_coord
{
	int					i;
	int					j;
}						t_coord;

typedef struct			s_lst
{
	int					num;
	struct s_lst		*next;
}						t_lst;

typedef struct			s_room_lst
{
	char				*name;
	t_coord				pt;
	int					type;
	struct s_room_lst	*next;
}						t_room_lst;

typedef struct			s_room_ar
{
	char				*name;
	t_coord				pt;
	t_lst				*links;
}						t_room_ar;

typedef struct			s_lem_in
{
	int					ants;
	int					room_num;
	int					start;
	int					end;
	t_room_lst			*node;
	t_room_ar			*room;
	t_list				*info;
}						t_lem_in;

int						reading_lem_in(char *line, t_lem_in *game, int *type);
t_lem_in				*create_game(void);
void					add_info(t_lem_in *game, char *ptr);
int						room_valid(char *line, t_lem_in *game, int *type);
int						check_room_str(char *line);
int						link_valid(char *line, t_lem_in *game, int *type);
int						check_link_str(char *line);
int						ants_valid(char *line, t_lem_in *game, int *type);
int						command_valid(char *line, t_lem_in *game, int *type);
t_room_lst				*create_node(char *line, int *type);
int						add_node_lst(t_room_lst **head, t_room_lst *node);
void					create_room_array(t_lem_in *game);
int						manage_links(t_lem_in *game, char *line);
int						check_links(t_lem_in *game, char *name1, char *name2);
int						add_link(t_room_ar *room, int n1, int n2);
int						check_doubles(t_lem_in *game, int n1, int n2);
void					clean_game(t_lem_in *game);
void					clean_node(t_room_lst *node);
void					clean_room(t_room_ar *room, int room_num);
void					clean_info(t_list *info);
#endif
