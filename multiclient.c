#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#define domain AF_INET
#define type SOCK_STREAM
#define protocol 0
#define port 3442
#define size 100
struct header{
        char filename[size];
        char method[size];
        int length;
        time_t last_modified;
        time_t res_time;
        char msg[size];
};
void file_read(int client)
{
        while(1)
        {
                struct header x,y;
                /*printf("Enter the methodor enter exit to close connection : ");
                scanf("%s", &x.method);*/
                printf("Enter file name : ");
                scanf("%s", &x.filename);
                if(strcmp(x.filename,"exit")==0)
                {
                        send(client,(void*)&x,sizeof(struct header),0);
                        break;
                }
                /*printf("Enter the URL(filename) : ");
                scanf("%s", &x.filename);*/
                send(client,(void*)&x,sizeof(struct header),0);
                recv(client,(struct header*)&y,sizeof(struct header),0);
                printf("The message is %s\n", y.msg);
                printf("The response time is :%s", ctime(&y.res_time));
        }
}
/*void test(int client)
{
        char a[size];
        strcpy(a,"hai server is good!!");
        send(client,&a,size,0);
        bzero(a,size);
        recv(client,&a,sizeof(a),0);
        printf("The message is %s\n", a);
}*/
int main()
{
        int client;
        client=socket(domain,type,protocol);
        if(client==-1)
        {
                printf("Error in creating scket at client side\n");
                exit(0);
        }
        else
        {
                printf("Client socket created successfully\n");
        }
        struct sockaddr_in client_addr;
        client_addr.sin_family=domain;
        client_addr.sin_port=htons(port);
        client_addr.sin_addr.s_addr=INADDR_ANY;
        int server=connect(client,(struct sockaddr*)& client_addr,sizeof(client_addr));
        if(server==-1)
        {
                printf("Error \n");
                close(client);
                exit(0);
        }
        else
        {
                printf("Connected to server successfully\n");
        }
        file_read(client);
        close(client);
        return 0;
}
