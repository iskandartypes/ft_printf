# ft_printf
[42 Silicon Valley](https://www.42.us.org/) recreation of printf.

These functions are now submodules of [my 42 library](https://github.com/naregjan/libft), so I would suggest grabbing that if you want to use them.

The floats are bad approximations that will only work for a small range of numbers; see the note in pf_floats.c on why, and for resources.

Has typedefs for printf, sprintf, snprintf, asprintf, dprintf, vprintf, vsprintf, vsnprintf, vasprintf, and vdprintf, with prefix `ft_` (i.e. `ft_printf(const char *format, ...)`).

Covers `dDioOuUxXfFcCsSp%` conversions, with `hh h l ll j z` length modifiers and `#0 -+.` flags. See [the printf man page](https://linux.die.net/man/3/printf) for more details on what each of those do.

Contains additional modifier `%b` or `%B` for binary, flag `%_<base>d` for bases [2, 16] (`%_^<base>d` for uppercase, works with any of `dDioOuUxX`) (ex `ft_printf("%_^12o", 11)` returns `B`), and colour printing. 

Colour printing is set via `%{<colour name>}` to change the text to one of the eight standard ANSI colours (red, green, blue, yellow, magenta, cyan, black, and white) and `%[<colour name>]` for background colour; `%#{<cn>}` or `%#[<cn>]` for bold; and `%{}` or `%[]` for end of colour.

Similarly, wide characters or strings can be printed with UTF-8 encoding for things like emojis in the terminal, with `%#lc` or `%#C` for wide chars and `%#ls` or `%#S` for strings.
