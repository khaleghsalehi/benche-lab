//
// Created by tomcat on 5/23/22.
//

#ifndef IC2_FUZZ_H
#define IC2_FUZZ_H

#define IPADDR 30
#define RESPLEN 100

int total_request_count=0;
int total_pass=0;
int total_failed=0;

const int VERBOSE = 0;
const char *TAG = "modbus_fuzzer";

int modbus_tcp_port = 502; // Modbus server port number

#endif //IC2_FUZZ_H
