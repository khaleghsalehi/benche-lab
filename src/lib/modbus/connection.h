//
// Created by tomcat on 8/29/22.
//

#ifndef PARRALLER_CONNECTION_H
#define PARRALLER_CONNECTION_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <malloc.h>
#include <string.h>
#include <omp.h>
#include "../../benchmark.h"

void buff2hex(char *buff, size_t len) {
    size_t i;
    if (VERBOSE) {
        printf("\n");
        for (i = 0; i < len; i++) {
            printf("%02X ", (unsigned char) buff[i]);
        }
    }
}

int readCoils(int sockfd, char *request, char *response, size_t len, int t_id) {
    int readlen = 0;
    if (send(sockfd, request, len, 0) < 0) {
        if (VERBOSE)
            syslog(LOG_NOTICE, "**** send() failed! ****");
        return -1;
    } else {
        if (VERBOSE)
            buff2hex(request, len);
    }

    readlen = recv(sockfd, (char *) response, RESPLEN, 0);
    if (VERBOSE)
        syslog(LOG_NOTICE, "worker t-id -> {%d}, received length: {%d}", t_id, readlen);
    if (VERBOSE) {
        buff2hex(response, readlen);
    }
}

void send_req(char *ip) {
    while (1 == 1) {
        int sockfd = 0;
        int rconnect = 0;
        int startAddr = 0;
        int numCoils = 1;
        int len = 0;


        int *values = NULL;
        char *request = NULL;
        char *response = (char *) malloc(RESPLEN);
        char serverip[IPADDR] = {0};

        setlogmask(LOG_UPTO (LOG_NOTICE));
        openlog(TAG, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

        memset(serverip, 0, IPADDR);
        strncpy(serverip, ip, strlen(ip));

        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(modbus_tcp_port);
        inet_aton(serverip, &(serv_addr.sin_addr));


        unsigned char slave_addr;
        unsigned char func_code;

        if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) { // Create a socket
            total_failed++;
            if (VERBOSE)
                syslog(LOG_NOTICE, "socket error");
            // exit(1);
        } else {
            total_pass++;
            if (VERBOSE)
                syslog(LOG_NOTICE, "socket created.");
        }
        rconnect = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
        if (rconnect != 0) {
            if (VERBOSE)
                syslog(LOG_NOTICE, "connection to the modbus server: failed");
            //exit(0);
        } else {
            len = sizeof(char) * 12;
            request = (char *) malloc(len); //Modbus TCP ADU = 12 Bytes
            memset(request, 0, len);
            if (VERBOSE)
                syslog(LOG_NOTICE, "read coil...");
            slave_addr = 0x01;
            func_code = 0x01;
            request[1] = 0x00;
            request[5] = 0x06; // Length from here to the end of the frame(Unit ID~end of Data)
            memcpy(&request[6], &slave_addr, sizeof(unsigned char));
            memcpy(&request[7], &func_code, sizeof(unsigned char));
            memcpy(&request[9], &startAddr, sizeof(unsigned char));
            memcpy(&request[11], &numCoils, sizeof(unsigned char));
            for (;;) { // ping-pong server via infinite loop
                readCoils(sockfd, request, response, len, omp_get_thread_num());
                total_request_count++;
                if (VERBOSE)
                    syslog(LOG_NOTICE,
                           "total_connection_failed ->{%d}  total_connection_bind->{%d}  total_request_sent-> {%d}",
                           total_failed, total_pass, total_request_count);
                sleep(1);
            }
            sleep(1000);

        }
        close(sockfd);

    }
}

#endif //PARRALLER_CONNECTION_H
