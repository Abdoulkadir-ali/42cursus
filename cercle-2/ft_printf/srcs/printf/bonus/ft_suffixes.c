int ft_suffix_handle_precision(char *str, char *flags)
{
    int precision_val;
    int chars_written;
    int i;
    
    if (!ft_strchr(flags, '.'))
        return (0);
    
    precision_val = ft_how_much(flags, '.');
    chars_written = 0;

    ft_putchar('.');
    chars_written++;
    
    i = 0;
    while (i < precision_val)
    {
        if (str[i])
            ft_putchar(str[i]);
        else
            ft_putchar('0');
            
        chars_written++;
        i++;
    }

    return (chars_written);
}


int ft_left_justify(char *str, char *flags)
{
    int i;
    int p;

    p = ft_how_much(flags, '-');
    if (!ft_strchr(flags, '-'))
        return (0);
    i = 0;
    while (i < p)
    {
        ft_putchar(' ');
        i++;
    }
    return (p);
}

int    ft_handle_suffixes(char *str, char *flags)
{
    int i;

    i = 0;
    if (ft_strchr(flags, '.'))
        i += ft_suffix_handle_precision(str, flags);
    if (ft_strchr(flags, '-'))
        i += ft_left_justify(str, flags);
    return i;
}

