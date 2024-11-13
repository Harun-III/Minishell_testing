/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:25:52 by rbouizer          #+#    #+#             */
/*   Updated: 2024/11/10 17:48:56 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*create_redir(t_redir **redir, t_token *tok, char **cmd, t_mem **mana)
{
	int		i;
	t_token	*cp;
	t_redir	*rd;

	i = 0;
	while (cmd[i])
	{
		cp = tok;
		while (cp)
		{
			if (is_redirec(cp, cmd[i]))
			{
				rd = handle_redirec(cp, cmd[i + 1], mana);
				if (!rd)
					return (NULL);
				add_back_redir(redir, rd);
				break ;
			}
			cp = cp->next;
		}
		i++;
	}
	return (*redir);
}

int	parse_args(char *arg, t_token *tok, t_cmd **cmd, t_mem **mana)
{
	char	**command_args;
	t_cmd	*new_cmd;
	t_redir	*new_redir;
	bool	type;

	command_args = ft_split_mm(mana, arg, 0x07);
	if (!command_args)
		return (0);
	command_args = fix_command(command_args);
	type = is_builtin(command_args[0]);
	new_redir = NULL;
	create_redir(&new_redir, tok, command_args, mana);
	remove_file(command_args);
	new_cmd = cr_cmd(type, command_args[0], command_args, new_redir, mana);
	if (!new_cmd)
		return (0);
	add_back_cmd(cmd, new_cmd);
	return (1);
}

int	parse_cmd(char *arg, t_token *tok, t_cmd **cmd_list, t_mem **mana)
{
	char	**args;
	int		i;

	args = ft_split_mm(mana, arg, '|');
	if (!args)
		return (0);
	i = 0;
	while (args[i] != NULL)
	{
		if (!parse_args(args[i], tok, cmd_list, mana))
			return (0);
		i++;
	}
	return (1);
}

int	create_cmd(t_cmd **cmd, t_shell **the_shell, t_token *tok)
{
	char	*arg;
	int		result;

	arg = create_arg(tok, &(*the_shell)->manager, *the_shell);
	if (!arg)
		return (0);
	result = parse_cmd(arg, tok, cmd, &(*the_shell)->manager);
	return (result);
}

int	create_shell(t_token *tokens, t_shell **the_shell)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!create_cmd(&cmd, the_shell, tokens))
		return (0);
	if (!cr_shell(the_shell, cmd))
		return (0);
	//print_cmd(cmd);
	return (1);
}
