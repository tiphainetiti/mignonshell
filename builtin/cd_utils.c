/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:54:10 by ocussy            #+#    #+#             */
/*   Updated: 2024/10/04 14:14:25 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_oldpwd(t_data *data, char **oldpwd, char *pwd)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 7 + ft_strlen(pwd));
	if (!tmp)
		exit_shell(data, 2, 1);
	ft_strlcpy(tmp, "OLDPWD=", 8);
	ft_strlcat(tmp, pwd + 4, ft_strlen(tmp) + ft_strlen(pwd) + 1);
	*oldpwd = ft_strdup(tmp);
	if (*oldpwd == NULL)
		return ;
	free(tmp);
}

void	set_newpwd(t_data *data, char **pwd, char *path)
{
	char	*str_tmp;

	str_tmp = malloc(sizeof(char) * (4 + ft_strlen(path) + 1));
	if (!str_tmp)
		exit_shell(data, 2, 1);
	ft_strlcpy(str_tmp, "PWD=", 5);
	ft_strlcat(str_tmp, path, 4 + ft_strlen(path) + 1);
	*pwd = ft_strdup(str_tmp);
	if (*pwd == NULL)
	{
		free(str_tmp);
		return ;
	}
	free(str_tmp);
}

void	set_pwds_env(t_data *data, t_envt *envt, char *path)
{
	t_envt	*tmp;
	t_envt	*tmp2;

	tmp = envt;
	tmp2 = envt;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "OLDPWD=", 7) == 0)
		{
			while (tmp2)
			{
				if (ft_strncmp(tmp2->str, "PWD=", 4) == 0)
				{
					free(tmp->str);
					set_oldpwd(data, &tmp->str, tmp2->str);
					free(tmp2->str);
					set_newpwd(data, &tmp2->str, path);
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
}

void	set_pwds_export(t_export *export, char *new_pwd)
{
	t_export	*tmp1;
	t_export	*tmp2;

	tmp1 = export;
	tmp2 = export;
	while (tmp1)
	{
		if (ft_strcmp(tmp1->key, "OLDPWD") == 0)
		{
			while (tmp2)
			{
				if (ft_strcmp(tmp2->key, "PWD") == 0)
				{
					free(tmp1->value);
					tmp1->value = ft_strdup(tmp2->value);
					free(tmp2->value);
					tmp2->value = ft_strdup(new_pwd);
				}
				tmp2 = tmp2->next;
			}
		}
		tmp1 = tmp1->next;
	}
}

void	error_cd(t_data *data, char *path)
{
	write(2, "bash: cd: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 29);
	data->exit_code = 1;
}
