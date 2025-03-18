#include "main.h"

#define MAX_ITERATIONS 100

typedef struct {
  float alpha;

  float outp;
} Filter;
Filter* filt = NULL;

static Filter* filter_init(float alpha, float calibration_value);
static float filter_update(Filter* filt, float inp);

static float filter_update(Filter* filt, float inp) {
  filt->outp = ((1.0f - filt->alpha) * inp) + (filt->alpha * filt->outp);

  return filt->outp;
}

void main(void) {
  float alpha = 0.5f;
  float outp_offset = 0;
  filt = filter_init(alpha, outp_offset);

  float output = 0.0f;

  uint16_t iterations = MAX_ITERATIONS;
  while(true) {
    float inp = rand() % 4095;
    output = filter_update(filt, inp);
    printf("%lu, %.2f\r\n", (MAX_ITERATIONS - iterations), output);

    iterations--;
    if (0 == iterations) {
      break;
    }
  }
}


static Filter* filter_init(float alpha, float calibration_value) {
  Filter* filter = NULL;
  filter = (Filter*)malloc(sizeof(Filter));

  if (NULL != filt) {
    filt->alpha = alpha;
    filt->outp = calibration_value;
  }

  return filter;
}
