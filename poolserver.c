#include "common.h"

#define SERV_PORT 9998
#define OPEN_MAX 1024

int main() {
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    struct pollfd client[OPEN_MAX];
    int maxi, nready, clilen;
    char * ipaddr;
    //socket 
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0) {
        perror("listen error: ");
        return 1;
    }
    memset(&servaddr,0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
   
    //bind 
    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind error: ");
        return 1;
    }

    //listen
    if(listen(listenfd, 10) < 0) {
        perror("listen error: ");
        return 1;
    }
    
    client[0].fd = listenfd;
    client[0].events = POLLIN;
    for (int i=1; i<OPEN_MAX; ++i) {
        client[i].fd = -1;
    }
    maxi = 0;
    printf("start polling\n");
    for(;;) {
        nready = poll(client, maxi+1, -1);
        if(client[0].revents & POLLIN) {
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
            struct sockaddr_in *peer = (struct sockaddr_in *)&cliaddr;
            ipaddr = inet_ntoa(peer->sin_addr);
            printf("accept one client %s:%d\n", ipaddr, (int)ntohs(peer->sin_port));
        }
    }
    return 0;
}
