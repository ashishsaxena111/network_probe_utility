#include     "process.h"

#define TIME 10
 void
 calculate(double * val_var)
 {
	int     size;
    	char    recvbuf[BUFSIZE];
    	char    controlbuf[BUFSIZE];
    	struct msghdr msg;
    	struct iovec iov;
     	ssize_t n;
	int i;
     	struct timeval tval;
	double tot = 0.0,val;
     	sockfd = socket(pr->sasend->sa_family, SOCK_RAW, pr->icmpproto);		 /*opening a raw socket */
     	setuid(getuid());           /* don't need special permissions any more */
     	if (pr->finit)
         (*pr->finit) ();

     	size = 60 * 1024;           /* OK if setsockopt fails */
     	setsockopt (sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof (size));

     	sig_alrm (SIGALRM);         /* send  packet */

     	iov.iov_base = recvbuf;
     	iov.iov_len = sizeof (recvbuf);
     	msg.msg_name = pr->sarecv;
     	msg.msg_iov = &iov;
     	msg.msg_iovlen = 1;
     	msg.msg_control = controlbuf;
     	for (i=0 ;i<TIME ;i++ )  /*sendig icmp request packet 10 times to take avg value*/ 
	{
         msg.msg_namelen = pr->salen;
         msg.msg_controllen = sizeof (controlbuf);
         n = recvmsg (sockfd, &msg, 0);
         if (n < 0) {
             if (errno == EINTR)
                 continue;
		
             else
			fprintf(stderr, "recvmsg error\n");
         	exit(EXIT_FAILURE);
                 err_sys("recvmsg error");
         }
         gettimeofday (&tval, NULL);
         (*pr->fproc) (recvbuf, n, &msg, &tval,&val);
		 tot=tot + val;
	
    	}

	tot=tot/TIME;
#ifdef DEBUG	
	printf("rtt= %f",tot);
#endif
	*val_var = tot;

 }

