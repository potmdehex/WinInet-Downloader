/* Created by John Åkerblom 10/26/2014 */

/* Useless symbol that we need to resolve for using floats */
int _fltused = 0;

/* C/P from http://stackoverflow.com/a/12386915 with incorrect comment removed */
int downs_itoa(int value, char *sp, int radix)
{
    char tmp[16];
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);
    if (sign)
        v = -value;
    else
        v = (unsigned)value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < 10)
            *tp++ = i + '0';
        else
            *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    if (sign)
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
        *sp++ = *--tp;

    return len;
}

/* Need these pragmas or the loop will be replaced by unresolved memset call */
#pragma optimize("", off)
void *downs_memset(void *s, int c, unsigned int n)
{
    unsigned int i = 0;

    for (i = 0; i < n; ++i) {
        ((unsigned char *)s)[i] = c;
    }

    return s;
}
#pragma optimize("", on)

union UFloatInt {
    int i;
    float f;
};

/** by Vlad Kaipetsky
portable assuming FP24 set to nearest rounding mode
efficient on x86 platform
*/
unsigned int downs_fltoui(float fval)
{
    /* Assert(fabs(fval) <= 0x003fffff); // only 23 bit values handled */
    union UFloatInt fi = *(union UFloatInt *)&fval;
    fi.f += 3 << 22;
    return ((fi.i) & 0x007fffff) - 0x00400000;
}
