//
// Created by tomcat on 8/28/22.
//

#ifndef PARRALLER_UTIL_H
#define PARRALLER_UTIL_H

#define VERSION "0.1"

#include <stdio.h>

void menu() {
    fprintf(stderr, "\n\n");
    fprintf(stderr, "██████╗ ███████╗███╗   ██╗ ██████╗██╗  ██╗   ██╗      █████╗ ██████╗ \n"
                    "██╔══██╗██╔════╝████╗  ██║██╔════╝██║  ██║   ██║     ██╔══██╗██╔══██╗\n"
                    "██████╔╝█████╗  ██╔██╗ ██║██║     ███████║   ██║     ███████║██████╔╝\n"
                    "██╔══██╗██╔══╝  ██║╚██╗██║██║     ██╔══██║   ██║     ██╔══██║██╔══██╗\n"
                    "██████╔╝███████╗██║ ╚████║╚██████╗██║  ██║██╗███████╗██║  ██║██████╔╝\n"
                    "╚═════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ \n");
    fprintf(stderr, "SCADA/ICS protocols benchmark toolkit (version %s)\n", VERSION);
    fprintf(stderr, "Sponsored by: Safe Instrument (https://safeinst.com/)\n\n");
}

#endif //PARRALLER_UTIL_H
