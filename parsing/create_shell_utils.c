/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shell_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:54:57 by rbouizer          #+#    #+#             */
/*   Updated: 2024/11/11 00:07:53 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *str)
{
	return (ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "unset") == 0);
}

int	is_redirec(t_token *tok, char *cmd)
{
	return ((ft_strcmp(tok->data.origin, ">") == 0 && ft_strcmp(cmd, ">") == 0)
		|| (ft_strcmp(tok->data.origin, ">>") == 0 && ft_strcmp(cmd, ">>") == 0)
		|| (ft_strcmp(tok->data.origin, "<<") == 0 && ft_strcmp(cmd, "<<") == 0)
		|| (ft_strcmp(tok->data.origin, "<") == 0 && ft_strcmp(cmd, "<") == 0));
}

t_redir	*handle_redirec(t_token *cp, char *cmd, t_mem **mana)
{
	t_redir	*rd;

	if (cp->data.type_fd == HERE)
		rd = cr_redir(cp->data.fd, "here_doc", cp->type, mana);
	else
		rd = cr_redir(-1, cmd, cp->type, mana);
	return (rd);
}

void	remove_file(char **arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], ">>") == 0
			|| ft_strcmp(arg[i], "<<") == 0 || ft_strcmp(arg[i], "<") == 0)
		{
			if (arg[i + 1])
				i += 2;
			else
				i += 1;
		}
		else
			arg[j++] = arg[i++];
	}
	arg[j] = NULL;
}

char *ft_fix_exp(char *data, t_mem **mana)
{
    char **exp;
    int i = 0;
    int space = 0;
    char *new_data = NULL;

    if (data == NULL)
        return data;

    while (data[i] != '\0') {
        if (isspace(data[i]))
            space++;
        i++;
    }

    if (space == 0)
        return data;

    exp = ft_split_mm(mana, data, ' ');

    if (!exp)
        return NULL;

    i = 0;
    while (exp[i]) {
        new_data = ft_strjoin_mm(mana, new_data, exp[i]);
        if (exp[i + 1])
		{
			new_data = ft_strjoin_mm(mana, new_data, (char []){0x07, '\0'});
			new_data = ft_strjoin_mm(mana, new_data, (char []){0x04, '\0'});
		}  
        i++;
    }

    return new_data;
}

char	*create_arg(t_token *tokens, t_mem **manager, t_shell *the_shell)
{
	char	*join;
	char	*data;
	char	*temp;

	join = NULL;
	while (tokens)
	{
		if (ft_strcmp(tokens->data.origin, "\0" ) == 0)
			data = ft_strdup_mm(manager, (char []){0x05, '\0'});
		else
		{
			data = expand_token_data(tokens, the_shell, manager);
			data = ft_fix_exp(data, manager);
		}
		if (!data)
			return (NULL);
		temp = ft_strjoin_mm(manager, join, data);
		if (!temp)
			return (NULL);
		join = temp;
		if (tokens->join == NON_JOINBLE)
		{
			temp = ft_strjoin_mm(manager, join, (char []){0x07, '\0'});
			if (!temp)
				return (NULL);
			join = temp;
		}
		tokens = tokens->next;
	}
	//printf("%s\n", join);
	return (join);
}
