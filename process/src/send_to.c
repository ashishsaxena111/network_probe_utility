#include     "process.h"

uint16_t
 in_cksum (uint16_t * addr, int len)
 {
     int     nleft = len;
     uint32_t sum = 0;
     uint16_t *w = addr;
     uint16_t answer = 0;

     while (nleft > 1) {
         sum += *w++;
         nleft -= 2;
     }
         /* mop up an odd byte, if necessary */
     if (nleft == 1) {
         * (unsigned char *) (&answer) = * (unsigned char *) w;
         sum += answer;
     }

         /* add back carry outs from top 16 bits to low 16 bits */
     sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
     sum += (sum >> 16);     /* add carry */
     answer = ~sum;     /* truncate to 16 bits */
     return (answer);
 }


 void
 send_to (void)
 {
     int     len;
     struct icmp *icmp;

     icmp = (struct icmp *) sendbuf;
     icmp->icmp_type = ICMP_ECHO;
     icmp->icmp_code = 0;
     icmp->icmp_id = pid;
     icmp->icmp_seq = nsent++;
     memset (icmp->icmp_data, 0xa5, datalen); /* fill with pattern */
     gettimeofday((struct timeval *) icmp->icmp_data, NULL);

     len = 8 + datalen;           /* checksum ICMP header and data */
     icmp->icmp_cksum = 0;
     icmp->icmp_cksum = in_cksum ((u_short *) icmp, len);

     sendto (sockfd, sendbuf, len, 0, pr->sasend, pr->salen);
 }

