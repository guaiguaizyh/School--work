#ifndef __RFID_H_
#define	__RFID_H_

#include <stdio.h>
#include <assert.h>
#include <fcntl.h> 
#include <unistd.h>
#include <termios.h> 
#include <sys/types.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>

#define DEV_PATH1   "/dev/ttySAC1"
#define DEV_PATH2   "/dev/ttySAC2"

int rfid();

#endif
