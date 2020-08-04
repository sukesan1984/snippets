/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:49:59 by ktakami           #+#    #+#             */
/*   Updated: 2020/07/29 11:49:59 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main()
{
	char	buf[4000];
	char	*short_str;

	snprintf(buf, 4000, "hoge %d\n", 100);
	printf("%s", buf);

	// snprintf
	short_str = malloc(10 * sizeof(char));
	snprintf(short_str, 12, "abcdefghijklmn");
	printf("%s\n", short_str);

	// $のoption
	printf("%2$d, %3$s, %1$d\n", 1, 2, "hoge");
	printf("%2$d, %3$s, %4$d, %1$d, %1$d\n", 1, 2, "hoge", 4);


	// %s
	printf(" %%s: %s\n", "hoge");

	// u
	printf(" %%lu: %lu\n", 2147483904);

	// i
	printf("0x80000000 %%i: %i\n", 0x80000000);
	printf("0x7fffffff %%i: %i\n", 0x7fffffff);
	printf("32768 %%i: %i\n", 32768);
	printf("32767 %%i: %i\n", 32767);

	printf("012 %%i: %i\n", 012);
	printf("012 %%d: %d\n", 012);
	// d
	printf("0x80000000 %%d: %d\n", 0x80000000);
	printf("0x7fffffff %%d: %d\n", 0x7fffffff);
	printf("32768 %%d: %d\n", 32768);
	printf("32767 %%d: %d\n", 32767);

	// octal
	printf("octal    %%o: %o\n", 123);
	printf("octal   %%05o: %05o\n", 123);
	printf("octal   %%#o: %#o\n", 123);
	printf("octal  %%0#5o: %0#5o\n", 123);
	printf("octal  %%#3o: %#3o\n", 123);
	printf("octal  %%#2o: %#2o\n", 123);
	printf("octal %%#10o: %#10o\n", 123);

	// hexdecimal
	printf("hexdecimal %%x %x\n", 42);
	printf("hexdecimal %%X %X\n", 42);
	printf("hexdecimal %%#x %#x\n", 42);
	printf("hexdecimal %%#X %#X\n", 42);

	// d, u, i
	printf("d: %%'d %'d\n", 42424242);
	printf("d: %%'d %'d\n", 42424242);
	printf("u: %%'u %'u\n", 42424242);
	printf("u: %%'u %'u\n", 42424242);

	// double
	double a = 123.456789;
	double b = 123;
	double n = -123;
	printf("double:   %%a: %a\n", a);
	printf("double:  %%#a: %#a\n", b);
	printf("double:  %%0a: %0a\n", a);
	printf("double:  %% a: % a(-123)\n", n);
	printf("double: %% 5a: % 5a(-123)\n", n);
	printf("double:  %% a: % a(123)\n", a);
	printf("double: %% 5a: % 5a(123)\n", a);
	printf("double:  %%+a: %+a(-123)\n", n);
	printf("double: %%+5a: %+5a(-123)\n", n);
	printf("double:  %%+a: %+a(123)\n", a);
	printf("double: %%+5a: %+5a(123)\n", a);
	printf("double: %%-ahoge: %-ahoge\n", a);
	printf("double: %%-50a: %-50ahoge\n", a);
	printf("double:  %%A: %a\n", a);
	printf("double: %%#A: %#A\n", b);
	printf("double: %%-Ahoge: %-Ahoge\n", b);
	printf("double: %%-50Ahoge: %-50Ahoge\n", b);
	printf("double:  %%e: %e\n", a);
	printf("double: %%#e: %#e\n", b);
	printf("double: %%-ehoge: %-ehoge\n", b);
	printf("double: %%-50ehoge: %-50ehoge\n", b);
	printf("double:  %%E: %E\n", a);
	printf("double: %%#E: %#E\n", b);
	printf("double: %%-Ehoge: %-Ehoge\n", b);
	printf("double: %%-50Ehoge: %-50Ehoge\n", b);
	printf("double:  %%f: %f\n", a);
	printf("double: %%#f: %#f\n", b);
	printf("double: %%-fhoge: %-fhoge\n", b);
	printf("double: %%-50fhoge: %-50fhoge\n", b);
	printf("double:  %%F: %F\n", a);
	printf("double: %%#F: %#F\n", b);
	printf("double: %%-F: %-Fhoge\n", b);
	printf("double: %%-50Fhoge: %-50Fhoge\n", b);
	printf("double : %%g: %g\n", a);
	printf("double: %%#g: %#g\n", b);
	printf("double: %%-g: %-ghoge\n", b);
	printf("double: %%-50ghoge: %-50ghoge\n", b);
	printf("double:  %%G: %G\n", a);
	printf("double: %%#G: %#G\n", b);
	printf("double: %%-G: %-Ghoge\n", b);
	printf("double: %%-50G: %-50Ghoge\n", b);

	return (0);
}
