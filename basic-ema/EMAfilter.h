#ifndef __EMAFILTER_H__
#define __EMAFILTER_H__

#include <float.h>

typedef struct {
    float alpha;

    float out;
} EMAFilter;

void filter_init(EMAFilter *filt, float alpha);
float filter_update(EMAFilter *filt, float inp);

#endif /* __EMAFILTER_H__ */
