WinInet-Downloader
========

Basic downloader with progress bar using WinInet supporting SSL (code sets flags to ignore invalid certificates which can be tweaked). File to download specified in main.c.

downslib.c, downslib.h and wininet_defs.h together are standalone, they do not need anything from the other source files.

Compiles to an ~8KB EXE with VS without fiddling (CRT not used).
