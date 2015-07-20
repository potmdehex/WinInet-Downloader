/* Created by John Åkerblom 10/26/2014 */

/* Replacement for some common CRT functions */
#ifndef __DOWNSCRT_H_DEF__
#define __DOWNSCRT_H_DEF__

int downs_itoa(int value, char *sp, int radix);
void *downs_memset(void *s, int c, unsigned int n);
unsigned int downs_fltoui(float fval);

#endif
