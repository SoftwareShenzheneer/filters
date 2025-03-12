
#include "EMAfilter.h"

void filter_init(EMAFilter *filt, float alpha)
{
    if (alpha < 0.0f) {
        filt->alpha = 0.0f;
    } else if (alpha > 1.0f) {
        filt->alpha = 1.0f;
    } else {
        filt->alpha = alpha;
    }

    filt->out = 0.0f;
}

float filter_update(EMAFilter *filt, float inp)
{
    filt->out = ((1.0f - filt->alpha) * inp) + (filt->alpha * filt->out);

    return (float)filt->out;
}
