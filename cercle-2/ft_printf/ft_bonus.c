int ft_handle_bonus(char *str, char *flags)
{
    char *flags;
    int i;

    flags = "# +-0.";
    while (str[i] && ft_strchr(flags, str[i]))
    {
        if (str[i] == '#')
            ft_handle_alternate();
        if (str[i] == '+' || str[i] == ' ')
            ft_handle_signs();
        if (str[i] == '-' || str[i] == '0')
            ft_handle_formatting()
        if (str[i] == '.')
            ft_handle_precision();
        i++;
    }
}
