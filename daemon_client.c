/* 
This submission is for the following people:
    Conner Swann
    Dylan Grayson
    Brandon Paree
*/

#include "daemon.h"
#include <netinet/in.h>
#include <netdb.h> 

#define PORT "23001"
#define HOST "localhost"

int main(int argc, char *argv[])
{
	//declare variables
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    //user input buffer
    char buffer[256];
    //connect to server
    portno = atoi(PORT);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        perror("ERROR opening socket");
    server = gethostbyname(HOST);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        perror("ERROR connecting");
        
    while(1){
		//get user input
		printf("IN| ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		//write input to server
		n = write(sockfd,buffer,strlen(buffer));
		// 'q' is escape character
		if (buffer[0] == 'q') {
			break;
		}
		if (n < 0) 
			 perror("ERROR writing to socket");
		bzero(buffer,256);
		//read server response
		n = read(sockfd,buffer,255);
		if (n < 0) 
			 perror("ERROR reading from socket");
		printf("OUT| %s\n",buffer);
		 }
    close(sockfd);
    return 0;
}
