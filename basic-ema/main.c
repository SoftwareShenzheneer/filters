#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "EMAfilter.h"

FILE *fptrIn;
FILE *fptrOut;

EMAFilter filt;

void main(void)
{
    clock_t begin = clock();

    bool start = false;
    int sum = 0;
    int index = 0;
    float outp;

    char buf[255];
    size_t read;

    /* Init the filter */
    filter_init(&filt, 0.90f);

    /* stepresponse as input file, ema_filtered as output file */
    fptrIn = fopen("stepresponse.txt", "r");
    fptrOut = fopen("ema_filtered.txt", "w");

    // fptrIn = fopen("ema_filtered.txt", "r");
    // fptrOut = fopen("stepresponse.txt", "w");

    if ((NULL == fptrIn) || (NULL == fptrOut)) {
        printf("Error opening file.");
        exit(1);
    }

    /* Create a step response */
    /*for (int i = 0; i < 1000; i++) {*/
    /*    if (i < 10) {*/
    /*        fprintf(fptrOut, "%d,%d\n", i, 0);*/
    /*    } else {*/
    /*        fprintf(fptrOut, "%d,%d\n", i, 1);*/
    /*    }*/
    /*}*/

    while (fgets(buf, 255, fptrIn)) {
        int len = strlen(buf);
        for (int i = 0; i < len; i++) {
            if (buf[i] == ',') {
                i++;
                start = true;
            }

            if (buf[i] == '\n') {
                start = false;
                outp = filter_update(&filt, (float)sum);
                /*fprintf(fptrOut, "%d,%.2f\n", index, outp);*/
                fprintf(fptrOut, "%d,%.2f\n", index, outp);
                index++;
                sum = 0;
            }

            if (start && (buf[i] != '\n')) {
                buf[i] = buf[i] - '0';
                if (sum) {
                    sum = sum * 10;
                }
                sum = sum + buf[i];
            }
        }
    }

    clock_t end = clock();
    double time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\r\nRuntime: %lf seconds", time);
}
