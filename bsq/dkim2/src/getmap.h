/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:09:04 by dkim2             #+#    #+#             */
/*   Updated: 2021/10/28 00:27:42 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETMAP_H
# define GETMAP_H
# include "utils.h"

int		read_line_zero(int fd, t_mark *M, char *buf);

char	*read_line_first(int fd, t_mark *M, char *buf);

char	**read_line_first2(int fd, t_mark M, char *first_row);

int		read_lines_left(int fd, t_mark M, char ***map, char *buf);

char	**getmap(int fd, char *buf, t_mark *p_mark);

#endif
