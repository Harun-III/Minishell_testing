/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:49:37 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/28 13:16:35 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_var(char *data, t_env *my_env, t_mem **manager)
{
	t_env	*env;

	env = my_env;
	while (env)
	{
		if (ft_strcmp(data, env->var) == 0)
			return (ft_strdup_mm(manager, env->value));
		env = env->next;
	}
	return (ft_strdup_mm(manager, "\'"));
}

void	exp_dat(char **expanded_data, char *new_data, t_mem **manager)
{
	char	*temp;

	temp = ft_strjoin_mm(manager, *expanded_data, new_data);
	if (temp)
	{
		*expanded_data = temp;
	}
}

void	exp_var(char **exp_data, char *dt, size_t *i, t_shell *the_shell)
{
	int		len;
	char	*var_name;
	char	*v_val;
	char	*nb;

	(1) && (len = 0, var_name = NULL, v_val = NULL, nb = NULL);
	if (dt[*i] == '?')
	{
		(2) && (nb = ft_itoa(get_set_return(0, GET_EXIT_STATUS)), (*i)++);
		exp_dat(exp_data, nb, &(the_shell->manager));
		free(nb);
		return ;
	}
	while (dt[*i + len] && (ft_isalnum(dt[*i + len]) || dt[*i + len] == '_'))
		len++;
	if (len > 0)
	{
		var_name = ft_substr(dt, *i, len);
		if (var_name)
		{
			v_val = ft_var(var_name, the_shell->my_env, &(the_shell->manager));
			exp_dat(exp_data, v_val, &(the_shell->manager));
			(3) && (free(var_name), *i += len);
		}
	}
	else
		(4) && (exp_dat(exp_data, " ", &(the_shell->manager)), (*i)++);
}

char	*expand_token_data(t_token *tokens, t_shell *the_shell, t_mem **manager)
{
	char	*expanded_data;
	char	*data;
	size_t	i;
	char	temp[2];

	expanded_data = ft_strdup_mm(manager, "");
	(1) && (data = tokens->data.origin,  i = 0);
	if (!expanded_data)
		return (NULL);
	while (data[i] != '\0')
	{
		if (data[i] == '$' && tokens->state != IN_SINGALE)
		{
			i++;
			if (data[i] == '\0')
				break;
			exp_var(&expanded_data, data, &i, the_shell);
		}
		else
		{
			(2) && (temp[0] = data[i++], temp[1] = '\0');
			exp_dat(&expanded_data, temp, manager);
		}
	}
	return (expanded_data);
}

