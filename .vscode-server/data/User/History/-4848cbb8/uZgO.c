#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
int main()
{
	struct sockaddr_in s_addr,c_addr;    
                          
	int s_fd,c_fd1, c_fd2,s_len,c_len;



	if((s_fd=socket(AF_INET,SOCK_STREAM,0))==-1){
		printf("[-]Error in Socket\n");
		return 1;
	}				
		
	printf("[+]Server Socket created\n");

	s_addr.sin_family = AF_INET;                                  
	s_addr.sin_port = 3452;                                       
	s_len=sizeof(s_addr); 

	if(bind(s_fd,(struct sockaddr*)& s_addr,s_len)==-1){
		printf("[-]Error in binding\n");
		exit(0);
	}
	printf("[+]Binding successfull\n");

	if(listen(s_fd,5)==-1){
		printf("[-]Error in listen\n");
		exit(0);
	} 
	printf("[+]Listening... \n");


    c_len=sizeof(c_addr);                                 	
	if((c_fd1=accept(s_fd,(struct sockaddr*)&c_addr,&c_len))==-1)	
		printf("\n[-]Error in accepting\n");
	printf("[+]New Client Connected!!!: \n\n");

	if((c_fd2=accept(s_fd,(struct sockaddr*)&c_addr,&c_len))==-1)	
		printf("\n[-]Error in accepting\n");
	printf("[+]New Client Connected!!!: \n\n");

    char buff[100];
	while(1)
	{
        read(c_fd1,buff,100);
		 
        if (strcmp(buff, "Exit\n") == 0){
            printf("[-]Server disconnected\n");
            write(c_fd2,"Disconnected\n",100);
            break;
        }   
        else
        {
            write(c_fd2,buff,100);
        }									  
        printf("From Client: %s\n",buff);  

		read(c_fd2,buff,100);
		 
        if (strcmp(buff, "Exit\n") == 0){
            printf("[-]Server disconnected\n");
            write(c_fd1,"Disconnected\n",100);
            break;
        }   
        else
        {
            write(c_fd1,buff,100);
        }									  
        printf("From Client: %s\n",buff);         
	}
    close(c_fd1);
	close(c_fd2);
	return 0;
}
