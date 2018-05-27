// Client side C/C++ program to demonstrate Socket programming
#include "client.h"
#include <fstream>
#include <iostream>
using namespace std;
Client::Client(){}

int Client::proceed()
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *file_name = "test1.mis";
    //char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORTNUM);
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    char return_content[1024] = {0};
    FILE * f = fopen(file_name,"r"); // Try to open the file
    if ( f != NULL)	// If opened
        {
            fseek (f,0,2);	// Seek to the end of the file  
            long fsize = ftell(f);	// Get current location which represents the size
		// Allocate a buffer with the file size to read the content
            char * buffer = (char *) calloc(fsize+1,sizeof(char));
            fseek (f,0,0);  // Seek the beginning of the file
            fread(buffer,1,fsize,f); // Read the whole file into the buffer
            //tcpSocket->writeToSocket(buffer,fsize); // Write the buffer to the socket
            //free(buffer);	// Free the buffer
            fclose(f);	// Close the file
            send(sock , buffer , fsize , 0 );
            printf("File is sent to server\n");
            valread = read( sock , return_content, 1024);
            printf("%s\n",return_content );

            char filename[ ] = "error.err";
            fstream errfile;

            errfile.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);


            // If file does not exist, Create new file
            if (!errfile ) 
            {
               //cout << "Cannot open file, file does not exist. Creating new file..";

                errfile.open(filename,  fstream::in | fstream::out | fstream::trunc);
                errfile <<return_content;
                errfile.close();

            } 
            else   
            {    // use existing file
                cout<<"success "<<filename <<" found. \n";
               // cout<<"\nAppending writing and working with existing file"<<"\n---\n";

                errfile << return_content;
                errfile.close();
                cout<<"\n";
            }    
                    // FILE * f = fopen("error.err","r"); // Try to open the file
                    // long size = ftell(f);
                    // char * buff = (char *) calloc(size+1,sizeof(char));
                    // fseek (f,0,0);  // Seek the beginning of the file
                    // fread(buff,1,size,f); // Read the whole file into the buffer
                    // printf("%s \n", buff);
                    // printf("%ld \n", size);
        }
        else
        {
            printf("Error opening the file \n");
        }
    
    return 0;
}

Client::~Client(){}