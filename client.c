#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <omp.h>
#include <stdbool.h>

#define modbus_tcp_port 80


// simple read coil
char *cmd = "\\x00\\x01\\x00\\x00\\x00\\x06\\xFF\\x03\\x00d\\x00\\x14";
int thread_count = 2000;

int send_req(char *src) {
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;

    char buffer[1024] = {0};

    while (true) {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("socket creation error \n");
            //return -1;
        }
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(modbus_tcp_port);
        if (inet_pton(AF_INET, src, &serv_addr.sin_addr) <= 0) {
            printf("Invalid address/ Address not supported \n");
            //return -1;
        }

        if ((client_fd = connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) < 0) {
            printf("connection Failed \n");
            //return -1;
        }

         printf("send  message {%s} \n", cmd);
        send(sock, cmd, strlen(cmd), 0);
        valread = read(sock, buffer, 1024);
         printf("%s\n", buffer);
        //close(client_fd);
        //usleep(1 * 1000);
    }

}

int main(int argc, char const *argv[]) {
    omp_set_num_threads(thread_count);
#pragma omp parallel
    while (true){
        //printf("coil req from thread = %d\n", omp_get_thread_num());
        send_req("172.16.2.63");
    }
    return 0;
}

