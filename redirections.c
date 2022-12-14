/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:57:32 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/07 18:49:05 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include </Users/tkempf-e/.brew/Cellar/readline/8.2.1/include/readline/readline.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	startlim(char const *s1, char const *set)
{
	int		lim;
	int		i;
	int		j;

	i = 0;
	lim = 1;
	while (lim == 1 && s1[i])
	{
		j = 0;
		lim = 0;
		while (set[j] && lim == 0)
		{
			if (s1[i] == set[j])
				lim = 1;
			j++;
		}
		i++;
	}
	i--;
	return (i);
}

int	endlim(char const *s1, char const *set)
{
	int		h;
	int		lim;
	int		i;
	int		j;

	i = 0;
	lim = 1;
	h = ft_strlen(s1) - 1;
	while (lim == 1 && h >= 0)
	{
		j = 0;
		lim = 0;
		while (set[j] && lim == 0)
		{
			if (s1[h] == set[j])
				lim = 1;
			j++;
		}
		h--;
	}
	h++;
	return (h);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		h;
	char	*pure;

	i = startlim(s1, set);
	h = endlim(s1, set);
	if (h < i)
	{
		pure = malloc(sizeof(char));
		pure[0] = '\0';
		return (pure);
	}
	pure = malloc(sizeof(char) * (h - i + 2));
	if (!pure)
		return (0);
	pure[h - i + 1] = '\0';
	j = 0;
	while (i <= h)
	{
		pure[j] = s1[i];
		i++;
		j++;
	}
	return (pure);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	while (s[i])
	{
		write(fd, &(s[i]), 1);
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	j = 0;
	i = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1 && s1[i])
	{
		join[i] = *(char *)(s1 + i);
		i++;
	}
	while (s2[j])
	{
		join[i + j] = *(char *)(s2 + j);
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

int	ft_nbwords(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_word;

	if (s[0] == '\0')
		return (0);
	i = 0;
	while (s[i] == c && s[i])
		i++;
	nb_word = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c && s[i - 1] != c)
			nb_word++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c)
		nb_word++;
	return (nb_word);
}

char	**ft_tab(char	**tab, char	const *s, char c, int nb_word)
{
	int	i;
	int	j;
	int	compt;

	i = 0;
	j = 0;
	while (s[i] && j < nb_word)
	{
		while (s[i] == c && s[i])
			i++;
		compt = 0;
		while (s[i] != c && s[i++])
			compt ++;
		if (s[i - 1] != c)
		{
			tab[j] = malloc(sizeof(char) * (compt + 1));
			if (!tab)
				return (0);
			tab[j][compt] = '\0';
		}
		j++;
	}
	return (tab);
}

char	**ft_malloc_tab2d(char const *s, char c)
{
	size_t			nb_word;
	char			**tab;

	nb_word = ft_nbwords(s, c);
	if (s[0] == '\0' && nb_word == 0)
	{
		tab = (char **)malloc(sizeof(char *));
		tab[0] = NULL;
		return (tab);
	}
	tab = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (0);
	tab[nb_word] = 0;
	tab = ft_tab(tab, s, c, nb_word);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	index[2];
	char			**tab;

	tab = ft_malloc_tab2d(s, c);
	if (!tab)
		return (NULL);
	i = 0;
	index[0] = 0;
	while (tab[index[0]] && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		index[1] = 0;
		while (s[i] != c && s[i])
		{
			tab[index[0]][index[1]] = s[i];
			index[1]++;
			i++;
		}
		index[0]++;
	}
	return (tab);
}

char	*ft_path_tester(char *totest, char *cmd)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(totest, ':');
	while (tab && tab[i])
	{
		tab[i] = ft_strjoin(tab[i], ft_strjoin("/", cmd));
		if (access(tab[i], R_OK) == 0)
			return (tab[i]);
		i++;
	}
	return (NULL);
}

char	*ft_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
		&& envp[i][3] == 'H')
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	ft_strcmp(char *str1, char *str2)
{
	int		i;

	if (!str1 && !str2)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (0);
	else
		return (-1);
}

void	enter_redirect(char *entry, char *cmd, char **envp)
{
	int		fdopen;
	char	*path;
	char	**str2;
	int		pid;

	str2 = ft_split(cmd, ' ');
	fdopen = open(entry, O_RDONLY);
	path = ft_path_tester(ft_env(envp), cmd);
	dup2(fdopen, STDIN_FILENO);
	close(fdopen);
	pid = fork();
	if (pid == 0)
		execve(path, str2, envp);
	free (str2);
	free (path);
	waitpid(pid, 0, 0);
}

/*
	cmd << delimiter
	faire que cat lise de lentree standard qui est dup avec str
*/
void	here_doc(char *cmd, char *delimiter, char **envp)
{
	char	*str;
	char	*path;
	char	*line;
	char	**cmd_tab;
	int		fd;

	line = 0;
	str = 0;
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		str = ft_strjoin(str, ft_strjoin(line, "\n"));
	}
	fd = open(".hairdoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd(str, fd);
	free (str);
	close(fd);
	enter_redirect(".hairdoc", cmd, envp);
}

char	*ft_fdtostr(int fd)
{
	char	*str;
	char	buffer[2];
	int		octet;

	str = NULL;
	octet = read(fd, buffer, 1);
	buffer[1] = 0;
	str = ft_strjoin(str, buffer);
	while (octet > 0)
	{
		octet = read(fd, buffer, 1);
		buffer[octet] = 0;
		str = ft_strjoin(str, buffer);
	}
	return (str);
}

// cmd > exit
void	exit_redirect(char *exit, char *cmd, char **envp)
{
	int		fdopen;
	int		fd[2];
	char	**str2;
	char	*path;
	int		pid;

	str2 = ft_split(cmd, ' ');
	path = ft_path_tester(ft_env(envp), str2[0]);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(path, str2, envp);
	}
	close(fd[1]);
	path = ft_fdtostr(fd[0]);
	close(fd[0]);
	fdopen = open(exit, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd(path, fdopen);
	close(fdopen);
	waitpid(pid, 0, 0);
}

int	redirection_counter(char *str)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			counter++;
			if (str[i + 1] && str[i + 1] == str[i])
				i++;
		}
		i++;
	}
	return (counter);
}

char	*filer_the_creator(char *str, int redirect_nbr)
{
	int		i;
	int		j;
	char	**no_redirect;
	char	*file;

	no_redirect = ft_split(str, '>');
	i = 0;
	while (no_redirect[i])// enlever les ' ' et '>' en trop
	{
		file = ft_strtrim(no_redirect[i], " ><");
		free (no_redirect[i]);
		no_redirect[i] = file;
		i++;
	}
	i = 1;
	while (no_redirect[i] && no_redirect[i + 1])
	{
		open(no_redirect[i], O_CREAT | O_RDWR , 0644);
		i++;
	}
	return (ft_strjoin(no_redirect[0], ft_strjoin(" > ", no_redirect[i])));
}

// gerer les redirections multiples
// return string without repetition of redirection
char	*pre_redirect(char *str)
{
	char	*new_str;
	int		redirect_nbr;
	
	redirect_nbr = redirection_counter(str);
	if (redirect_nbr < 2)
		return (str);
	new_str = filer_the_creator(str, redirect_nbr);
	return (new_str);
}

void	exit_append_redirect(char *exit, char *cmd, char **envp)
{
	int		fdopen;
	int		fd[2];
	char	**str2;
	char	*path;
	int		pid;

	str2 = ft_split(cmd, ' ');
	path = ft_path_tester(ft_env(envp), str2[0]);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(path, str2, envp);
	}
	close(fd[1]);
	path = ft_fdtostr(fd[0]);
	close(fd[0]);
	fdopen = open(exit, O_CREAT | O_RDWR | O_APPEND, 0644);
	ft_putstr_fd(path, fdopen);
	close(fdopen);
	waitpid(pid, 0, 0);
}
// cmd                        Stdin      envp   => fd
// cmd2                       fd    envp =>fd2
//  dup2()

int	ft_pipe(char *cmd, int inputfd, char **envp)
{
	int		fd[2];
	char	**str2;
	char	*path;
	int		pid;

	str2 = ft_split(cmd, ' ');
	path = ft_path_tester(ft_env(envp), str2[0]);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(inputfd, STDIN_FILENO);
		close(inputfd);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		//redirection ici
		execve(path, str2, envp);
	}
	close(fd[1]);
	waitpid(pid, 0, 0);
	return (fd[0]);
}

//return l'index de la 1ere redirection
int	redirection_checker(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (i > 0 && (str[i] == '<' || str[i] == '>')
			&& (str[i] == str[i - 1] || str[i - 1] == ' '))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isalnum(int c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97)
		|| (c >= 48 && c <= 57) || c == ' ')
		return (0);
	return (-1);
}

int	ft_test(char *str, int i)
{
	if (i > 0 && (str[i + 1] != str[i] && ft_isalnum(str[i + 1]) == -1))
	{
		printf("Minishell: syntax error near unexpected token '%c'\n", str[i]);
		return (-1);
	}
	return (0);
}

void	redirect_options(char *str, char *cmd, char *file, char **envp)
{
	int		i;

	i = redirection_checker(str);
	if (str[i] == '>' && str[i + 1] == '>')
		exit_append_redirect(file, cmd, envp);
	else if (str[i] == '>')
		exit_redirect(file, cmd, envp);
	else if (str[i] == '<' && str[i + 1] == '<')
		here_doc(cmd, file, envp);
	else if (str[i] == '<')
		enter_redirect(file, cmd, envp);
}

char	*ft_cmd(char *str, int i, int *ptrj)
{
	char	*cmd;
	char	**split;

	split = ft_split(str, str[i]);
	cmd = split[0];
	i = 1;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free (split);
	return (cmd);
}

char	*ft_file(char *str, int i, int *ptrj)
{
	char	*file;
	char	**split;

	split = ft_split(str, str[i]);
	file = ft_strtrim(split[1], " ");
	i = 0;
	while (split[i] && split[i + 1])
	{
		free(split[i]);
		i++;
	}
	free (split);
	return (file);
}

char	*redirections(char *str, char **envp)
{
	int		i;
	int		j;
	char	*cmd;
	char	*file;
	char	*ret;
	char	*new_str;

	i = redirection_checker(str);
	if (i == -1 || ft_test(str, i) == -1)
		return (str);
	new_str = pre_redirect(str);
	cmd = ft_cmd(new_str, i, &j);
	file = ft_file(new_str, i, &j);
	redirect_options(new_str, cmd, file, envp);
	free(file);
	return (cmd);
}

// mettre a la norme
int	main(int argc, char **argv, char **envp)
{
	printf("%s\n", redirections("echo \"salut les gentilles monsieur\" >> test >> test2 >> test3 > test4", envp));
	return (0);
}
