#include     "process.h"

 struct proto proto_v4 =
     { process_packet, send_to, NULL, NULL, NULL, 0, IPPROTO_ICMP };


#include <sys/msg.h>
#include<stdlib.h>

#define TEXT_SIZE 20


struct my_msg_st {	/*structure for  msgque data*/
	long int my_msg_type;
	char text[TEXT_SIZE];
	char ch;
	double val;
};

int     datalen = 1500;   /* data that goes with ICMP echo request */

int main()
{

	int     c;
	int msgid;
	double lat_val;
	struct my_msg_st data;
	long int msg_to_receive = 0;
	int ret;
	char choice;

	double ret_val;	

	int size = sizeof(struct my_msg_st);

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid == -1)
		 {
			fprintf(stderr, "msgget failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
	while(1)
	{

	ret = msgrcv(msgid, (void *)&data, size,msg_to_receive, 0);
	if(ret ==-1)
		{
		continue;
		}
	

	host = data.text;
	choice = data.ch;
	
	switch(choice)
                {

                	case 'b':
			ret_val=0;	
			double percent;	
                        data.my_msg_type = 1;
			int link_speed=link_speed_calc(host);/*calculate link speed in Mbps*/
			if(link_speed==-1)
			      {
		      			strcpy(data.text,"error opening i/f ");
                        		data.val=-1;
					break;
			      }

                        ret_val=bandwidth_utilisation(&host);/*find out byts send*/
			if(ret_val==-1)
				{
					strcpy(data.text,"error opening i/f ");
					data.val=-1;	
					break;
				}
			
        		percent=((ret_val/(link_speed*10000000)))*100;/* formula to find bandwidth utilisation percentage*/

                        data.val=percent;
                        break;
        
		
			case 'l':
			host_name();
                        calculate(&lat_val);
                        printf("\nrtt= %f\n",lat_val);
                        data.my_msg_type = 1;
                        data.val = lat_val;

                        break;

                        case 't':
			host_name();
                        datalen = 1472;
                        calculate(&lat_val);
                        printf("\nrtt= %f\n",lat_val);
                        lat_val = ((datalen*1000)/lat_val)/(1024*1024);
                        data.my_msg_type = 1;
                        data.val = lat_val;

                        break;

                }

	if (msgsnd(msgid, (void *)&data, size, 0) == -1) 
		{
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
		}

	}

    exit(0);

}

void host_name(void)
{

	struct addrinfo *ai;
        char   *h;
	pid = getpid() & 0xffff;     /* ICMP ID field is 16 bits */
        signal(SIGALRM, sig_alrm);

        ai = host_serv (host, NULL, 0, 0);

        h = sock_ntop_host(ai->ai_addr, ai->ai_addrlen);
         /* initialize  according to protocol */
        if (ai->ai_family == AF_INET)
                {
                pr = &proto_v4;
                }
         else

        perror("unknown address family\n");
	
	pr->sasend = ai->ai_addr;
        pr->sarecv = calloc (1, ai->ai_addrlen);
        pr->salen = ai->ai_addrlen;

                                              

}


