/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:57:33 by kyolee            #+#    #+#             */
/*   Updated: 2022/04/28 20:28:01 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
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
