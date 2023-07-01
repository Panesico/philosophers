#include "../includes/philosophers.h"

void	*ft_check_dead(void *arg)
{
	t_phm *phm;
	int i;
	int wtf;

	phm = (t_phm * )arg;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < phm->philo_count)
		{
			ft_get_time(phm->ph[i], 0);
			wtf = (int)(phm->ph[i]->current_time - phm->ph[i]->since_ate);
			if (wtf > phm->die_time)
			{
				pthread_mutex_lock(&phm->print);
				ft_printf("%d %d died\n", phm->ph[i]->ms_time, phm->ph[i]->philo_id);
				phm->alive = 0;
				return (0);
			}
			i++;
		}
	}
}

int ft_initialize(t_phm *phm)
{
	int i;

	i = 0;
	while (i < phm->philo_count)
	{
		if ((phm->philo_count % 2) == 0)
		{
			if (!i)
				phm->ph[i]->left_fork = phm->philo_count - 1;
			else
				phm->ph[i]->left_fork = i - 1;
			if (i == phm->philo_count - 1)
				phm->ph[i]->right_fork = 0;
			else
				phm->ph[i]->right_fork = i;
		}
		else
		{
			phm->ph[i]->left_fork = i;
			if (i == phm->philo_count - 1)
				phm->ph[i]->right_fork = 0;
			else
				phm->ph[i]->right_fork = i + 1;
		}
		phm->ph[i]->philo_id = i;
		phm->ph[i]->ph_eat_count = phm->eat_count;
		phm->ph[i]->phm = phm;
		pthread_create(&phm->philo[i], NULL, ft_philo_ft, (void *)phm->ph[i]);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_phm *phm;
	int i;

	i = 0;
	if (argc > 4 && argc < 7)
	{
		phm = ft_create_struct(argc, argv);
		ft_initialize(phm);
		pthread_create(&phm->check_dead, NULL, ft_check_dead, phm);
		while (phm->alive)
			usleep(5);
		ft_free_all(phm);
	}
}
