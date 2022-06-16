/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_arg_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:07:11 by kyolee            #+#    #+#             */
/*   Updated: 2022/04/28 19:09:39 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"
#include "libft/libft.h"
#include <stdlib.h>

int	free_cmd_argv(t_arg_info *parg)
{
	int	idx;

	if (parg == 0)
		return (-1);
	idx = 0;
	if (parg->cmd_argv != 0)
	{
		while (parg->cmd_argv[idx] != 0)
			free(parg->cmd_argv[idx++]);
		free(parg->cmd_argv);
		parg->cmd_argv = 0;
	}
	return (0);
}
