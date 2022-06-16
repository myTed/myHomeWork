/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_file_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:26:50 by kyolee            #+#    #+#             */
/*   Updated: 2022/04/28 19:28:55 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"
#include "libft/libft.h"
#include "ft_pipex_utils_gnl_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	open_infile_for_read(t_arg_info *parg, int *pfd)
{
	if ((parg == 0) || (pfd == 0))
		return (-1);
	if (access(parg->in_filename, R_OK) == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		perror(parg->in_filename);
		return (1);
	}
	*pfd = open(parg->in_filename, O_RDONLY);
	if (*pfd == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		perror(parg->in_filename);
		return (1);
	}
	if (parg->here_info.is_here_doc)
	{
		if (unlink(parg->in_filename) < 0)
		{
			close(*pfd);
			return (1);
		}
	}
	return (0);
}

int	open_infile(t_arg_info *parg, int *pfd)
{
	int	result;

	if ((parg == 0) || (pfd == 0))
		return (-1);
	if (parg->here_info.is_here_doc)
	{
		result = make_heredoc_file(parg);
		if (result != 0)
			return (result);
	}
	return (open_infile_for_read(parg, pfd));
}

int	open_outfile(t_arg_info *parg, int *pfd)
{
	int	fd;

	if ((parg == 0) || (pfd == 0))
		return (-1);
	if (parg->here_info.is_here_doc)
		fd = open(parg->out_filename, O_CREAT | O_WRONLY | O_APPEND, 00600);
	else
		fd = open(parg->out_filename, O_CREAT | O_WRONLY | O_TRUNC, 00600);
	if (fd == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		perror(parg->out_filename);
		return (1);
	}
	*pfd = fd;
	return (0);
}

int	write_heredoc(int fd, t_arg_info *parg)
{
	char	*buff;

	if (parg == 0)
		return (-1);
	while (1)
	{
		if (write(1, "heredoc> ", ft_strlen("heredoc> ")) < 0)
			return (-1);
		buff = get_next_line(0);
		if (buff == 0)
			return (-1);
		if (ft_strncmp(buff, parg->here_info.limiter,
				ft_strlen(buff) - 1) == 0)
			break ;
		if (write(fd, buff, ft_strlen(buff)) < 0)
			break ;
		free(buff);
	}
	free(buff);
	return (0);
}

int	make_heredoc_file(t_arg_info *parg)
{
	int	fd;

	if (parg == 0)
		return (-1);
	fd = open(parg->in_filename, O_CREAT | O_RDWR | O_TRUNC, 00600);
	if (fd == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		perror(parg->in_filename);
		return (1);
	}
	if (write_heredoc(fd, parg) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
