/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:55:26 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/11/10 16:23:28 by tkempf-e         ###   ########.fr       */
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
# include </Users/tkempf-e/.brew/Cellar/readline/8.2.1/include/readline/readline.h>

struct sigaction old_action;

void ft_readline();

void ft_readline()
{
	while(42)
	{
		readline("patate : ");
	}
}

void handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		rl_redisplay();
		rl_on_new_line();
		
		rl_replace_line("", 0);
		
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
		exit(0);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int fd;
	struct sigaction action;

	action.sa_handler = &handle_signals;
	action.sa_flags = SA_RESTART;
	// sigaction(SIGINT, &action, NULL);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	ft_readline();
	return (0);
}