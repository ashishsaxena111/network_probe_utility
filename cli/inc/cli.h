#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MAX_TEXT 512


struct my_msg_st {
long int my_msg_type;
char text[20];
char ch;
double val;
};
