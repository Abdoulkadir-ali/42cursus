int    ft_how_much(char *flags, char c)
{
    if (ft_strchr(flags, c))
        return (ft_atoi(flags + ft_strchr(flags, c) + 1));
    return 0;
}