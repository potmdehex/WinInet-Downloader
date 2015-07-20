/* Created by John Åkerblom 10/26/2014 */

#ifndef __DOWNSLIB_H_DEF__
#define __DOWNSLIB_H_DEF__

void downslib_init(void);
void downslib_exit(void);

int downslib_easy_download(const char *url, const char *filename, int use_ssl);

typedef int (*downslib_cb)(int read_bytes, int total_bytes);

int downslib_download(const char *url, 
                    const char *filename,
                    int use_ssl,
                    const char *useragent,
                    unsigned int timeout, 
                    downslib_cb cb);

#endif

