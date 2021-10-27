/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:57:56 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/27 16:59:34 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

int		check_first_line(int fd, Mark *M);

int		check_each_line(char *str, Mark M);

int		check_whole_line(int fd, Mark M);

int		check_map_file(int fd, Mark *M);

char	**get_map(char *filename, Mark M);
#endif
