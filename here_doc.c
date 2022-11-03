/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:54:59 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/11/03 15:24:50 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_strcmp(char *str1, char *str2)
{
	int		i;

	if (!str1 && !str2)
		return (0);
	i = 0;
	while (str1[i] == str2[i])
		i++;
	if (str1[i] || str2[i])
		return (-1);
	return (0);
}

/*
	cmd << delimiter
*/
void	here_doc(char *cmd, char *delimiter)
{
	char	*str;

	str = 0;
	while (!ft_strcmp(str, delimiter))
	{
		
	}
}

int	main()
{
	return (0);
}