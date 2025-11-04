int     ft_handle_bonus(char *str, char *flags)
{
    int i;

    i = ft_handle_prefixes(str, flags) + ft_strlen(str);
    ft_putstr(str);
    i += ft_handle_suffixes(str, flags);
    free(str);
    return i;
}