#include"cli.h"

double send_to_process(char *address,char opt,char * input)
{
	double ret_val;
	struct my_msg_st data;
	int msgid;
	long int msg_to_receive = 0;

	int size= sizeof(struct my_msg_st);

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid == -1)
		 {
			fprintf(stderr, "msgget failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}


	data.my_msg_type = 1;
	data.val = 1.0;
	strcpy(data.text, address);
	data.ch = opt;
	if (msgsnd(msgid, (void *)&data, size, 0) == -1) 
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}




	if (msgrcv(msgid, (void *)&data, size,msg_to_receive, 0) == -1)
		 {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}

		if((opt=='b')&&(data.val==-1))
		{
		printf("%s",data.text);
		}
		else
		{	
		printf("\n %s for  %s= %f \n",input, data.text,data.val);
		}
	return data.val;

}

void usage()

{
	printf("\nlatency calculation\n");
	printf("./util -l <ipaddress>/<URL>\n");
	printf("./util -l www.google.com\n");
	printf("./util -l 192.168.10.12\n");
	
	printf("\nThroughput calculation\n");
        printf("./util -t <ipaddress>/<URL>\n");
        printf("./util -t www.google.com\n");
        printf("./util -t 192.168.10.12\n");

	printf("\n bandwidth ulilisation\n");
	printf("./util -b <n/w interface>\n");
	printf("./util -b eth0\n");


}
