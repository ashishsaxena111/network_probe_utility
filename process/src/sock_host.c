#include "process.h"

char *
sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
 {
     static char str[128];       /* Unix domain is largest */

     switch (sa->sa_family) 
		{
     		
		case AF_INET:
			
			{
             		struct sockaddr_in *sin = (struct sockaddr_in *) sa;

             		if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
                 	return (NULL);
             		return (str);
        		}

		default:
		
			snprintf(str,sizeof(str),"sock_ntop_host:unknown AF_xxx:%d,len%d",sa->sa_family,salen);	
			return (str);
		}

	return(NULL);

}
