/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:45:15 by kyolee            #+#    #+#             */
/*   Updated: 2021/12/16 20:50:10 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

#include <stdio.h>

static void	add_buff_to_list(t_list **list, char *read_buff, int read_len)
{
	char	*tmp;
	t_list	*new_list;

	tmp = NULL;
	tmp = malloc(sizeof(char) * read_len);
	if (tmp == NULL)
	{
		if (*list != NULL)
			ft_lstclear(list);
		return ;
	}
	ft_memcpy(tmp, read_buff, read_len);
	new_list = ft_lstnew(tmp, read_len);
	if (new_list == NULL)
	{
		if (*list != NULL)
			ft_lstclear(list);
		free(tmp);
	}
	else
		ft_lstadd_back(list, new_list);
}

static char	*make_one_line_string(t_list **lst, t_line_info *pline_info)
{
	char	*str;
	size_t	tmp_len;
	t_list	*tmp_lst;

	if (pline_info->total_cur_len <= 0)
		return (0);
	str = (char *)malloc(sizeof(char) * (pline_info->total_cur_len + 1));
	if (str == NULL)
	{
		ft_lstclear(lst);
		return (0);
	}
	tmp_len = 0;
	tmp_lst = *lst;
	while (tmp_lst)
	{
		ft_memcpy(str + tmp_len, tmp_lst->content, tmp_lst->len);
		tmp_len += tmp_lst->len;
		tmp_lst = tmp_lst->next;
	}
	str[pline_info->total_cur_len] = 0;
	return (str);
}

static void	save_buff_afterline(
	t_line_info *pline,
	char *buff,
	size_t read_cnt,
	size_t pos_line
){
	ssize_t	len;
	char	*str_after_newline;

	len = read_cnt - pos_line - 1;
	if (len <= 0)
		return ;
	str_after_newline = malloc(sizeof(char) * len);
	if (str_after_newline == NULL)
		return ;
	ft_memcpy(str_after_newline, buff + pos_line + 1, len);
	pline->after_new_str = str_after_newline;
	pline->after_new_len = len;
}

static void	make_list_for_one_line(
	t_list **lst,
	t_line_info *pline,
	int fd,
	char *buff
){
	int		is_found_line;
	int		read_cnt;
	size_t	pos_line;
	size_t	len;

	is_found_line = 0;
	len = 0;
	while (is_found_line == 0)
	{
		read_cnt = read(fd, buff, BUFFER_SIZE);
		if (read_cnt == 0)
		{
			if (*lst && (len == 0))
			{
				buff = (*lst)->content;
				read_cnt = (*lst)->len;
				pline->total_cur_len = 0;
			}
			else
				break ;
		}
		if (read_cnt < 0)
			break ;
		pos_line = get_pos_newline_in_buffer(buff, read_cnt, &is_found_line);
		if (is_found_line)
			len = pos_line + 1;
		else
			len = read_cnt;
		pline->total_cur_len += len;
		add_buff_to_list(lst, buff, len);
	}
	if (is_found_line && (read_cnt - pos_line - 1 > 0))
	{
		save_buff_afterline(pline, buff, read_cnt, pos_line);
		if (pline->after_new_str == 0)
			ft_lstclear(lst);
	}
}

char	*get_next_line(int fd)
{
	char				*buff;
	char				*str;
	static t_list		*lst;
	t_line_info			line;

	if (fd < 0)
		return (0);
	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (buff == NULL)
		return (0);
	line.after_new_len = 0;
	line.after_new_str = 0;
	line.total_cur_len = 0;
	if (lst != NULL)
		line.total_cur_len = lst->len;
	make_list_for_one_line(&lst, &line, fd, buff);
	str = make_one_line_string(&lst, &line);
	if (str != NULL)
		ft_lstclear(&lst);
	if ((line.after_new_len > 0) && (line.after_new_str != 0))
		lst = ft_lstnew(line.after_new_str, line.after_new_len);
	else
		lst = NULL;
	free(buff);
	return (str);
}

int	main(void)
{
	int		fd;
	char	*str;
	char	*buff;
	int		read_cnt;
	fd = 0;
		
	fd = open("ccc.txt", O_RDONLY);	
	if (fd == -1)
		return (-1);

	buff = malloc(sizeof(char)*BUFFER_SIZE);
	while(1)
	{
		read_cnt = read(fd, buff, BUFFER_SIZE);
		printf("%d\n", read_cnt);
		sleep(1);
	}
	/*	
	while ((str = get_next_line(fd)) != 0)
	{
		printf("%s",str);
		fflush(stdout);
		free(str);
	}
*/	
	if (fd)
		close(fd);
	return (0);
}
