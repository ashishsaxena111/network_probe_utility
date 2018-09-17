#include "cli.h"

int
main(int argc, char **argv)
{  
	int     c;
	struct addrinfo *ai;
	int verbose = 0;
	char host[20];
	char opt;
	double res;
	char val[20];
	if (argc < 3)
	{
		printf("wrong usage\n");
		printf("invoking help for correct use\n");
		usage();
		exit(1);
	
	}
    	opterr = 0;                  /* don't want getopt() writing to stderr */
    	while ( (c = getopt (argc, argv, "ltbh") ) != -1) 
	{
        	switch (c) 
			{
        			case 'l':
					printf("Latency measurement\n");	
					opt = 'l';	
					strcpy(val,"Latency");
            				break;

				case 't':
					printf("Throughput measurement\n");
					opt='t';
					strcpy(val,"Throughput");
            				break;

				 case 'b':
                                        printf("Bandwidth utilisation measurement\n");
                                        opt = 'b';
					strcpy(val,"Bandwidth");
                                        break;

	
         			case '?':
             				printf ("unrecognized option  enter input  correctly\n ");
					exit(1);
         		}
    	}


	strcpy(host,argv[optind]);
	res = send_to_process(host,opt,val);

	return 0;
}	
