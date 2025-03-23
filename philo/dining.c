#include "philo.h"

void    dinner_one(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    printf("%ld %d has taken a fork\n", now() - philo->table->tm_start, philo->id);
    pthread_mutex_unlock(philo->left_fork);
}

void    *dinner(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    if (philo->table->philo_nbr == 1)
    {
        dinner_one (philo);
        return (NULL);
    }
    if (philo->id % 2 == 0)
        usleep(600);
    while (!has_dead(philo->table) && get_meal(philo) != philo->table->num_eats)
    {
        take_fork(philo);
        eat(philo);
        philo_sleep(philo);
        think(philo);
    }
    return (NULL);
}