/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/12/30 19:22:30 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	valid_arg(t_simulation *sim, char **argv)
{
	sim->str = ft_itoa(sim->num_philosophers);
	//sim->str = NULL;
	//if (!sim->str)
	//	return (0);
	if (ft_strncmp(sim->str, argv[1], ft_strlen(argv[1])))
		return (free(sim->str), 0);
	free(sim->str);
	sim->str = ft_itoa(sim->time_to_die);
	if (ft_strncmp(sim->str, argv[2], ft_strlen(argv[2])))
		return (free(sim->str), 0);
	free(sim->str);
	sim->str = ft_itoa(sim->time_to_eat);
	if (ft_strncmp(sim->str, argv[3], ft_strlen(argv[3])))
		return (free(sim->str), 0);
	free(sim->str);
	sim->str = ft_itoa(sim->time_to_sleep);
	if (ft_strncmp(sim->str, argv[4], ft_strlen(argv[4])))
		return (free(sim->str), 0);
	free(sim->str);
	if (sim->meal_goal != -1)
	{
		sim->str = ft_itoa(sim->meal_goal);
		if (ft_strncmp(sim->str, argv[5], ft_strlen(argv[5])))
			return (free(sim->str), 0);
		free(sim->str);
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
			return (printf("Error: wrong number of meal\n"), 0);
	}
	else
		sim->meal_goal = -1;
	if (!valid_arg(sim, argv))
		return (printf("Error: Invalid arguments\n"), 0);
	if (sim->num_philosophers < 1 || sim->num_philosophers > 200)
		return (printf("Error: There should be 1-200 philosophers.\n"), 0);
	if (sim->time_to_die <= 0 || sim->time_to_eat <= 0
		|| sim->time_to_sleep <= 0)
		return (printf("Error: ttd, tte, tts must be greater than 0.\n"), 0);
	if (sim->time_to_die < 60 || sim->time_to_eat < 60
		|| sim->time_to_sleep < 60)
		return (printf("Error: ttd, tte, tts must be at least 60 ms.\n"), 0);
	return (1);
}

void	init_philosopher(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].left_fork = &sim->forks[i];
		sim->philosophers[i].right_fork = &sim->forks[(i + 1)
			% sim->num_philosophers];
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].last_meal_time = current_time();
		sim->philosophers[i].sim = sim;
		i++;
	}
}

int	init_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		init_philosopher(sim);
		if (pthread_mutex_init(&sim->forks[i].fork_mutex, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&sim->philosophers[i].meal_mutex, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&sim->log_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	init_simulation(t_simulation *sim)
{
	sim->philosophers = ft_calloc(sim->num_philosophers
			* sizeof(t_philosopher), 1);
	if (!sim->philosophers)
	{
		if (sim->philosophers)
			free(sim->philosophers);
		return (0);
	}
	sim->forks = ft_calloc(sim->num_philosophers * sizeof(t_fork), 1);
	if (!sim->forks)
	{
		cleanup_simulation(sim);
		return (0);
	}
	if (!init_mutexes(sim))
	{
		cleanup_simulation(sim);
		return (0);
	}
	return (1);
}
