#include "mrt_print.h"

int	print_error(char *s1, char *s2, char *s3, char *s4)
{
	fprintf(stderr, "%sError%s\n", COLOR_RE_1, COLOR_NO);
	fflush(stderr);
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s3, STDERR_FILENO);
	}
	if (s4)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s4, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (-1);
}

int	print_error_scene(int line_num, const char *msg1,
		const char *msg2, const char *msg3)
{
	fprintf(stderr, "%sError%s\n", COLOR_RE_1, COLOR_NO);
	fflush(stderr);
	if (line_num > 0)
	{
		write(STDERR_FILENO, "line ", 5);
		ft_putnbr_fd(line_num, STDERR_FILENO);
		write(STDERR_FILENO, ": ", 2);
	}
	if (msg1)
		write(STDERR_FILENO, msg1, ft_strlen(msg1));
	if (msg2)
	{
		if (msg1)
			write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, msg2, ft_strlen(msg2));
	}
	if (msg3)
	{
		if (msg1 || msg2)
			write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, msg3, ft_strlen(msg3));
	}
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}
