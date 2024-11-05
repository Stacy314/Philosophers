/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/11/04 19:56:36 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (initialize_simulation(&sim, argc, argv) != 0)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	start_simulation(&sim);
	cleanup_simulation(&sim);
	return (0);
}
