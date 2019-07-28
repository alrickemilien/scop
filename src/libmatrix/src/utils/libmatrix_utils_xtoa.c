#include "libmatrix.h"

int itoa_hex(uint64_t value, char *buffer, uint64_t base) {
  bool  isNegative;
  int   i;
  char  *str;
  int   rem;

  libmatrixutil_bzero(buffer, 514 * sizeof(char));
  str = buffer;
  isNegative = false;
  i = 0;
  // Handle 0 explicitely, otherwise empty string is printed for 0
  if (value == 0)
  {
      str[i++] = '0';
      str[i] = '\0';
      return (i);
  }

  // In standard itoa(), negative numbers are handled only with
  // base 10. Otherwise numbers are considered unsigned.
  if ((int)value < 0 && base == 10)
  {
      isNegative = true;
      value = -value;
  }

  // Process individual digits
  while (value != 0)
  {
      rem = value % base;
      str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
      value = value / base;
  }

  // If number is negative, append '-'
  if (isNegative)
      str[i++] = '-';

  // Append string terminator
  str[i] = 0;

  // Reverse the string
  libmatrixutil_reverse_string(str, i);

  return (i);
}

int ltoa_hex(uint64_t value, char *buffer, uint64_t base) {
  bool  isNegative;
  int   i;
  char  *str;

  str = buffer;

  isNegative = false;
  i = 0;

  // Handle 0 explicitely, otherwise empty string is printed for 0
  if (value == 0)
  {
      str[i++] = '0';
      str[i] = '\0';
      return (i);
  }

  // In standard itoa(), negative numbers are handled only with
  // base 10. Otherwise numbers are considered unsigned.
  if ((long)value < 0 && base == 10)
  {
      isNegative = true;
      value = -value;
  }

  // Process individual digits
  while (value != 0)
  {
      long rem = value % base;
      str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
      value = value / base;
  }

  // If number is negative, append '-'
  if (isNegative)
      str[i++] = '-';

  // Append string terminator
  str[i] = 0;

  // Reverse the string
  libmatrixutil_reverse_string(str, i);
  return (i);
}

int libmatrix_itoa(void *param, char *buffer)
{
  int value;

  libmatrixutil_memcpy(&value, param, sizeof(int));
  return ((int)itoa_hex(value, buffer, 10));
}

int libmatrix_ltoa(void *param, char *buffer)
{
  long  value;

  libmatrixutil_memcpy(&value, param, sizeof(long));
  return ((int)ltoa_hex(value, buffer, 10));
}

/*
** 2^-126 is the most little float you can have
** It is in decimal 2.3509887e-38
** It means that the most bigger number will be
** 1(The 2) +  1(The dot) +  38(e-38) + 1(\0 character) => 40 characters wide
*/

int libmatrix_ftoa(void *param, char *buffer)
{
  float   value;
  int     integer_part;
  float   float_part;
  char    integer_part_str[514];
  size_t  i;
  int     precision_afterpoint;
  
  precision_afterpoint = 38;

  libmatrixutil_memcpy(&value, param, sizeof(float));
  libmatrixutil_bzero(buffer, sizeof(char) * 41);

  integer_part = (int)value;
  float_part = fabsf(value - (float)integer_part);

  // convert integer part to string
  i = itoa_hex(integer_part, integer_part_str, 10);

  libmatrixutil_memcpy(buffer, integer_part_str, i);

  free(integer_part_str);

  // add dot
  buffer[i++] = '.';

  while (precision_afterpoint--)
	{
      float_part *= 10.0f;
      integer_part = float_part;
      buffer[i++] = '0' + integer_part;
      float_part -= integer_part;
  }

  // Remove useless 0
  while (buffer[i - 1] == '0' && buffer[i - 2] != '.')
  {
    buffer[i - 1] = 0;
    i--;
  }

  return ((int)i);
}