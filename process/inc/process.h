#include    <netinet/in_systm.h>
#include    <netinet/ip.h>
#include    <netinet/ip_icmp.h>
#include    <stdarg.h>          /* ANSI C header file */
#include    <syslog.h>          /* for syslog() */



#include    <sys/types.h>       /* basic system data types */
#include    <sys/socket.h>      /* basic socket definitions */
#include    <sys/time.h>        /* timeval{} for select() */
#include    <time.h>            /* timespec{} for pselect() */
#include    <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include    <arpa/inet.h>       /* inet(3) functions */
#include    <errno.h>
#include    <fcntl.h>           /* for nonblocking */
#include    <netdb.h>
#include    <signal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/stat.h>        /* for S_xxx file mode constants */
#include    <sys/uio.h>         /* for iovec{} and readv/writev */
#include    <unistd.h>
#include    <sys/wait.h>
#include    <sys/un.h>          /* for Unix domain sockets */


#include<stdio.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<linux/sockios.h>
#include<linux/if.h>
#include<linux/ethtool.h>




#define MAXLINE     4096         /* max text line length */


#define BUFSIZE     1500

             /* globals */
 char    sendbuf[BUFSIZE];

 int     datalen;                /* #bytes of data following ICMP header */
 char   *host;
 int     nsent;                  /* add 1 for each sendto() */
 pid_t   pid;                    /* our PID */
 int     sockfd;
 int     verbose;

int daemon_proc;
             /* function prototypes */
 void    process_packet(char *, ssize_t, struct msghdr *, struct timeval *,double *);
 void    send_to(void);
 void    calculate(double *);
 void    sig_alrm(int);
 void    tv_sub(struct timeval *, struct timeval *);

 struct proto {
     void    (*fproc) (char *, ssize_t, struct msghdr *, struct timeval *,double *);
     void    (*fsend) (void);
     void    (*finit) (void);
     struct sockaddr *sasend;    /* sockaddr{} for send, from getaddrinfo */
     struct sockaddr *sarecv;    /* sockaddr{} for receiving */
     socklen_t salen;            /* length of sockaddr {}s */
     int     icmpproto;          /* IPPROTO_xxx value for ICMP */
 } *pr;

void host_name(void);
