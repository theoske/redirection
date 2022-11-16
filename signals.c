/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:55:26 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/11/16 15:21:40 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "readline/include/readline/readline.h"

void ft_readline()
{
	char	*str;
	while(42)
	{
		str = readline("patate : ");
		if (!str)
			exit(0);
	}
}

void handle_signals(int signo)
{
	if (signo == SIGINT)//ctrl-c
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)/* ctrl-\  */
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
}
// gcc -lreadline -L/Users/tkempf-e/.brew/opt/readline/lib -I/Users/tkempf-e/.brew/opt/readline/include actions.c
int	main(int argc, char *argv[], char **envp)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	ft_readline();
	return (0);
}