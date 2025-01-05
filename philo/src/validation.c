/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/05 17:40:07 by anastasiia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	comparison(t_simulation *sim, char **argv, int i)
{
	if (!sim->str)
		return (0);
	if (ft_strncmp(sim->str, argv[i], ft_strlen(argv[i])))
		return (free(sim->str), 0);
	free(sim->str);
	return (1);
}

static int	valid_arg(t_simulation *sim, char **argv)
{
	sim->str = ft_itoa(sim->num_philosophers);
	if (!comparison(sim, argv, 1))
		return (0);
	sim->str = ft_itoa(sim->time_to_die);
	if (!comparison(sim, argv, 2))
		return (0);
	sim->str = ft_itoa(sim->time_to_eat);
	if (!comparison(sim, argv, 3))
		return (0);
	sim->str = ft_itoa(sim->time_to_sleep);
	if (!comparison(sim, argv, 4))
		return (0);
	if (sim->meal_goal != -1)
	{
		sim->str = ft_itoa(sim->meal_goal);
		if (!comparison(sim, argv, 5))
			return (0);
	}
	return (1);
}

int	parse_arguments(t_simulation *sim, int argc, char **argv)
{
	sim->num_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		sim->meal_goal = ft_atoi(argv[5]);
		if (sim->meal_goal <= 0)
			return (0);
	}
	else
		sim->meal_goal = -1;
	if (!valid_arg(sim, argv))
		return (0);
	if (sim->num_philosophers < 1 || sim->num_philosophers > INT_MAX)
		return (0);
	if (sim->time_to_die <= 0 || sim->time_to_eat <= 0
		|| sim->time_to_sleep <= 0)
		return (0);
	if (sim->time_to_die > INT_MAX || sim->time_to_eat > INT_MAX
		|| sim->time_to_sleep > INT_MAX)
		return (0);
	return (1);
}
