/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:04:55 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/27 17:05:04 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARK_H
# define MARK_H
typedef struct mark
{
	int rows;
	int cols;
	char ch[3];
} Mark;
int is_mark(char c, Mark M);
Mark *check_mark_file(int fd);
Mark *check_mark_stdi(char *str);
#endif
