#ifndef CONFIG_H
#define CONFIG_H

#define LIBORIGIN_VERSION_MAJOR 3
#define LIBORIGIN_VERSION_MINOR 0
#define LIBORIGIN_VERSION_PATCH 3

#define LIBORIGIN_VERSION ((LIBORIGIN_VERSION_MAJOR << 24) | \
                           (LIBORIGIN_VERSION_MINOR << 16) | \
                           (LIBORIGIN_VERSION_PATCH << 8) )
#define LIBORIGIN_QUOTE_(x) #x
#define LIBORIGIN_QUOTE(x) LIBORIGIN_QUOTE_(x)
#define LIBORIGIN_VERSION_STRING LIBORIGIN_QUOTE(LIBORIGIN_VERSION_MAJOR) "." LIBORIGIN_QUOTE(LIBORIGIN_VERSION_MINOR) "." LIBORIGIN_QUOTE(LIBORIGIN_VERSION_PATCH)

#endif
