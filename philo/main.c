#include "philo.h"

int check_digits(char *av)
{
    int i;

    i = 0;
    if (ft_atol(av) <= 0)
    {
        printf("argument cannot be zero");
        return (1);
    }
    while (av[i])
    {
        if (ft_isdigit(av[i]) == 0)
        {
            printf("the argument must only contain numbers\n");
            return (1);
        }
        i++;
    }
    return (0);
}
int streating_args(int ac, char **av, t_table *table)
{
    int i;

    i = 0;
    if (ac != 5 && ac != 6)
    {
        printf("expected: [1]<number philos> | [2]<time to die> | [3]<time to eat> | [4]<time to sleep> | [5]<number of time for eat>\n");
        return (1);
    }
    while (++i < ac)
    {
        if (check_digits(av[i]))
            return (1);
    }
    table->has_dead = 0;
    table->num_eats = -42;
    table->philo_nbr = ft_atoi(av[1]);
    table->time_die = ft_atol(av[2]);
    table->time_eats = ft_atol(av[3]);
    table->tm_sleep = ft_atol(av[4]);
    if (ac == 6)
        table->num_eats = ft_atoi(av[5]);
    table->forks = malloc(table->philo_nbr * sizeof(t_mtx));
    table->philos = malloc(table->philo_nbr * sizeof(t_philo));
    return (0);
}

int main(int    ac, char    **av)
{
    t_table table;

    if (streating_args(ac, av, &table))
        return (1);
    if (starting_thread(&table))
        return (1);
    clear(&table);
    return (0);
}