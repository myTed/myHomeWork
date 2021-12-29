/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:45:15 by kyolee            #+#    #+#             */
/*   Updated: 2021/12/30 00:26:04 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

#include <stdio.h>

int	add_list(t_list	**pplist, char *buff, ssize_t size)
{
	ssize_t	idx;
	size_t	start_idx;
	char	*tmp;

	idx = 0;
	start_idx = idx;
	while (idx < size)
	{
		if ((buff[idx] == '\n') || (idx == size - 1))
		{
			tmp = malloc(sizeof(char) * (idx - start_idx + 1));
			if (tmp == 0)
				return (MEM_ALLOC_ERROR);
			ft_memcpy(tmp, buff + start_idx, idx - start_idx + 1);
			ft_lstadd_back(pplist,
				ft_lstnew(tmp, idx - start_idx + 1, (buff[idx] == '\n')));
			start_idx = idx + 1;
		}
		idx++;
	}
	return (0);
}

int	concat_line(t_list **pplist, char **pnew_line, size_t new_len)
{
	int		start_idx;
	t_list	*ptmp;

	*pnew_line = malloc(sizeof(char) * new_len + 1);
	if (*pnew_line == 0)
		return (MEM_ALLOC_ERROR);
	ptmp = *pplist;
	start_idx = 0;
	while ((ptmp != NULL) && (!ptmp->is_newline))
	{
		ft_memcpy(*pnew_line + start_idx, ptmp->content, ptmp->len);
		start_idx += ptmp->len;
		free(ptmp->content);
		ptmp->ready_to_free = 1;
		ptmp = ptmp->next;
	}
	if (ptmp != NULL)
	{
		ft_memcpy(*pnew_line + start_idx, ptmp->content, ptmp->len);
		free(ptmp->content);
		ptmp->ready_to_free = 1;
		ptmp = ptmp->next;
	}
	(*pnew_line)[new_len] = 0;
	return (0);
}

int	make_newline(t_list **pplist, char **pnew_line, size_t new_len)
{
	t_list	*ptmp;

	ptmp = *pplist;
	if (ptmp->is_newline)
	{
		*pnew_line = malloc(sizeof(char) * ptmp->len + 1);
		if (*pnew_line == 0)
			return (MEM_ALLOC_ERROR);
		ft_memcpy(*pnew_line, ptmp->content, ptmp->len);
		(*pnew_line)[ptmp->len] = 0;
		free(ptmp->content);
		ptmp->ready_to_free = 1;
		return (0);
	}
	else
	{
		while ((ptmp != NULL) && (!ptmp->is_newline))
		{
			new_len += ptmp->len;
			ptmp = ptmp->next;
		}
		if (ptmp != NULL)
			new_len += ptmp->len;
		return (concat_line(pplist, pnew_line, new_len));
	}
}

int	make_list(int fd, t_list **plist, char *buff)
{
	ssize_t	read_cnt;

	read_cnt = -1;
	while (read_cnt != 0)
	{
		read_cnt = read(fd, buff, BUFFER_SIZE);
		if (read_cnt < 0)
			return (READ_ERROR);
		else if ((read_cnt == 0) && (*plist == 0))
			return (1);
		else
		{
			if (add_list(plist, buff, read_cnt) == MEM_ALLOC_ERROR)
				return (MEM_ALLOC_ERROR);
		}
		if (is_found_newline(buff, read_cnt))
			break ;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			*buff;
	static t_list	*plist;
	char			*line;
	int				error;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (buff == 0)
		return (0);
	error = make_list(fd, &plist, buff);
	line = 0;
	if (error == NON_ERROR)
		error = make_newline(&plist, &line, 0);
	delete_list(&plist, error);
	free(buff);
	return (line);
}

/*
int	main(void)
{
	int		fd;
	//char	*buff;
	//int		read_cnt;
	char	*str;
	fd = 0;
							
	fd = open("bbb.txt", O_RDONLY);	
	if (fd == -1)
		return (-1);
	
	while ((str = get_next_line(fd)) != 0)
	{
		printf("%s",str);
		fflush(stdout);
		free(str);
	}

	if (fd)
		close(fd);
	return (0);
}
*/
