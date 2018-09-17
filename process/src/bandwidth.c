#include "process.h"

int link_speed_calc(char *buf)
{
	int sock;
	struct ifreq ifr;
	struct ethtool_cmd edata;
	int rc;

	sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_IP);
        if(sock<0)
        {
       	 		perror("socket\n");
        		exit(1);
        }


        strncpy(ifr.ifr_name,buf,sizeof(ifr.ifr_name));
        ifr.ifr_data=&edata;
        edata.cmd=ETHTOOL_GSET;

        rc=ioctl(sock,SIOCETHTOOL,&ifr);

        if(rc<0)
        {
        	perror("ioctl");
        	return -1;
        }

	return ethtool_cmd_speed(&edata);



}


int find_num_of_bytes(char *interface)
{

	
	
        FILE *fp=NULL;
        char str[20];
        memset(str,0,10);
        strcpy(str,"/proc/net/dev");
        char temp[20],result[20];// varibles for storing the contents of file
        char var[20];
        int num1=0,num2=0,l;
        strcpy(var,interface);
        int k=1,uid=0,val,ret;
        fp=fopen(str,"r"); //opening the sysvipcs msg file in read mode
        if(NULL==fp)//unable to read msg file
        {
                printf("error in reading file\n");
                exit(1);
        }
        /* skipping the first line of msg file */
        while(k<21)
        {

                fscanf(fp,"%s",temp);
                k++;
        }

	 k=0;

	 while(1)//reading the msg file
        	{
			l=0;
                	memset(temp,0,20);
			

                	if(feof(fp))//break if end of file is reached
                	{
                        	fclose(fp);
                        	break;
                	}
                	ret=fscanf(fp,"%s",temp);
                	if(strcmp(temp,var)==0)

                	{
                		while(l<9)

                		{
               				 fscanf(fp,"%s",temp);
                			 l++;
                		}

                		num1=atoi(temp);
                		close(fp);
                		return num1;

			}
		}

}	


double bandwidth_utilisation(char ** interface)
{
	int sample_time=10;
	double percent;
	int link_speed,rate;
	int rx;
	int ret1,ret2;
        char buf[20];
        strcpy(buf,*interface);
	strcat(buf,":");
        ret1 = find_num_of_bytes(buf);
        printf("val=%d\n",ret1);
        sleep(10);
        ret2=find_num_of_bytes(buf);
        printf("val=%d\n",ret2);
       
	rx=ret2-ret1;
	


	
	rate=(rx*8)/sample_time; /*converting from bytes to bits and then divide by sample time */
	return rate;
}
