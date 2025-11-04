int ft_prefix_handle_precision(char *str, char *flags)
{
    int precision_val;
    int len_str;
    int zeros_to_add;
    int count;

    if (!ft_strchr(flags, '.'))
        return (0);

    precision_val = ft_how_much(flags, '.');
    len_str = ft_strlen(str);
    if (len_str == 1 && str[0] == '0' && precision_val == 0)
        return (-1); 
    zeros_to_add = precision_val - len_str;
    count = 0;
    while (zeros_to_add > 0)
    {
        ft_putchar('0');
        count++;
        zeros_to_add--;
    }
    return (count);
}


int ft_add_sign(char *str, char *flags)
{
    if (ft_is_negative(str))
        return (0); 
    if (ft_strchr(flags, '+'))
    {
        ft_putchar('+');
        return (1);
    }
    else if (ft_strchr(flags, ' '))
    {
        ft_putchar(' ');
        return (1);
    }
    return (0);
}

int ft_add_prefix(char *str, char *flags)
{
    if (!ft_strchr(flags, '#'))
        return (0);
    if (type == 'x' || type == 'X')
    {
        if (type == 'x')
            ft_putstr("0x");
        else
            ft_putstr("0X");
        return (2);
    }
    else if (type == 'o' && str[0] != '0')
    {
        ft_putchar('0');
        return (1);
    }
    return (0);
}

int ft_add_zeros(char *str, char *flags)
{
    int width;
    int len_str;
    int zeros_to_add;
    int count;


    if (!ft_strchr(flags, '0') || ft_strchr(flags, '-'))
        return (0);
    width = ft_how_much(flags, '1');
    len_str = ft_strlen(str);
    zeros_to_add = width - len_str - printed_len;
    count = 0;
    while (zeros_to_add > 0)
    {
        ft_putchar('0');
        count++;
        zeros_to_add--;
    }
    return (count);
}

int    ft_handle_prefixes(char *str, char *flags)
{
    int i;

    i = 0;
    if (ft_strchr(flags, '+') || ft_strchr(flags, ' '))
        i += ft_add_sign(str, flags);
    if (ft_strchr(flags, '#'))
        i += ft_add_prefix(str, flags);
    if (ft_strchr(flags, '0'))
        i += ft_add_zeros(str, flags);
    if (ft_strchr(flags, '.'))
        i+= ft_prefix_handle_precision(str, flags);
}