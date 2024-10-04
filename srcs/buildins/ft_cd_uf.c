/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:25:37 by paradari          #+#    #+#             */
/*   Updated: 2024/10/04 16:25:39 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



int	ft_cd(char **argv)
{
	//check arg
	if (argv[2])
	{
		ft_putstr_fd("too many arguments\n", STDOUT_FILENO);
		return ();
	}
	//check dir
	if (check_exit)
	{
		ft_putstr_fd("No such file or directory\n", STDOUT_FILENO);
		return ();
	}
	if (is_dir)
	{
		ft_putstr_fd("Not a directory\n", STDOUT_FILENO);
		return ();
	}
	//change path && pwd

}