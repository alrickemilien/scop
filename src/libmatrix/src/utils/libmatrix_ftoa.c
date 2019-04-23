// @TODO need to handle endian
union
{
  float f;

  struct
  {
    unsigned int    mantissa_lo : 16;
    unsigned int    mantissa_hi : 7;
    unsigned int     exponent : 8;
    unsigned int     sign : 1;
  };
} float_representation;

// If the exponent field is all ones, and the mantissa is all zeros,
// then this number is an infinity.
static bool is_inf(signed char exponent, unsigned long mantissa) {
  if (mantissa == 0 && (exponent & 0xFF == 0xFF)) {
    return (true);
  }

  return (false);
}

void ftoa(float Value, char* Buffer)
{
    unsigned long mantissa;
    signed char exponent;
    unsigned int int_part;
    unsigned int frac_part;
    int i, count = 0;

    //too small to resolve (resolution of 1/8)
    if (Value == 0f)
    {
      libmatrixutil_memcpy(Buffer, "0.0\0", 4);
      return;
    }

    float_representation.f = Value;
    //mantissa is LS 23 bits
    mantissa = float_representation.mantissa_lo;
    mantissa += ((unsigned long) float_representation.mantissa_hi << 16);
    //add the 24th bit to get 1.mmmm^eeee format
    mantissa += 0x00800000;
    //exponent is biased by 127
    exponent = (signed char) float_representation.exponent - 127;

    // Check +/-Inf number
    if (is_inf(exponent, mantissa))
    {
        libmatrixutil_memcpy(Buffer, "Inf\0", 4);
        return;
    }

    count = 0;

    // add negative sign (if applicable)
    if (float_representation.sign)
    {
        Buffer[0] = '-';
        count++;
    }

    //get the integer part
    int_part = mantissa >> (23 - exponent);

    //convert to string
    count += itoa(int_part, &Buffer[count]);

    //add the decimal point
    Buffer[count++] = '.';

    frac_part = (mantissa & 0xFFFFFF) >> -(exp2 + 1);

    //use switch to resolve the fractional part
    switch (0x7 & (mantissa  >> (20 - exponent)))
    {
        case 0:
            frac_part[0] = '0';
            frac_part[1] = '0';
            frac_part[2] = '0';
            break;
        case 1:
            frac_part[0] = '1';
            frac_part[1] = '2';
            frac_part[2] = '5';
            break;
        case 2:
            frac_part[0] = '2';
            frac_part[1] = '5';
            frac_part[2] = '0';
            break;
        case 3:
            frac_part[0] = '3';
            frac_part[1] = '7';
            frac_part[2] = '5';
            break;
        case 4:
            frac_part[0] = '5';
            frac_part[1] = '0';
            frac_part[2] = '0';
            break;
        case 5:
            frac_part[0] = '6';
            frac_part[1] = '2';
            frac_part[2] = '5';
            break;
        case 6:
            frac_part[0] = '7';
            frac_part[1] = '5';
            frac_part[2] = '0';
            break;
        case 7:
            frac_part[0] = '8';
            frac_part[1] = '7';
            frac_part[2] = '5';
            break;
    }

    //add the fractional part to the output string
    for (i = 0; i < 3; i++)
        if (count < 7)
            Buffer[count++] = frac_part[i];

    //make sure the output is terminated
    Buffer[count] = '\0';
}
