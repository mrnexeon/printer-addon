//
//  main.cpp
//  printer
//
//  Created by Андрей Архипов on 24/07/2019.
//  Copyright © 2019 Андрей Архипов. All rights reserved.
//

#include <iostream>

#include <cups/cups.h>
#include <cups/ppd.h>

int print_dest(void *user_data, unsigned flags, cups_dest_t *dest)
{
    if (dest->instance)
        printf("%s/%s\n", dest->name, dest->instance);
    else
        puts(dest->name);
    
    return (1);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    int        i;
    int        num_jobs;
    cups_job_t *jobs;
    num_jobs = cupsGetJobs(&jobs, NULL, 0, 0);
    
    const char* filepath = "/Users/nexeon/Downloads/test.pdf";
    
    cupsEnumDests(CUPS_DEST_FLAGS_NONE, 1000, NULL, 0, 0, print_dest, NULL);

    //int jobId = cupsPrintFile("ipp-printer", filepath, "xcode printer", 0, NULL);
    cups_dest_t *dests;
    int num_dests = cupsGetDests(&dests);
    printf("The default destination is %s\n", cupsGetDefault());
    //cupsSetDefaultDest("Xerox_Phaser_3117", NULL, num_dests, dests);
    printf("The default destination is %s\n", cupsGetDefault());   
    
    std::cout << "Hello, World!\n";
    return 0;
}
