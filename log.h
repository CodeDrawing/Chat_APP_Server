#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "status.h"
int write_Log(LOG_MESSAGE msg);

#endif