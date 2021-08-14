#include <stdint.h>

// Max scan lines used for a circle segment, this will be an odd number
// as we have a center line and given equakl number of lines up and down.
#define MAX_LINES 31

#define pixlesPerLine 640

typedef struct point {
  unsigned x;
  unsigned y;
} point_t;

typedef struct circle {
  unsigned radius;               // where to startt in Y (and also gives
                                 // the number of lines using a trivial formula)
  unsigned width[MAX_LINES];     // double pixel width
} circle_t;

// Start of frame buffer we are writing to
char* screenStart;

// Draw a circle
static inline void drawCircle (char* screenStart,
                               circle_t *circle,
                               point_t *at,
                               unsigned color2) {
  unsigned lines = circle->radius * 2 + 1;
  char* screen = screenStart + at->y * pixlesPerLine + at->x;
  for (unsigned i = 0; i < lines; i++) {
    unsigned width = circle->width[i];
    uint16_t* mem = (uint16_t*) (screen + width);

    while (width >= 6) {
      width -= 6;
      mem -=6;
      mem[5] = color2;
      mem[4] = color2;
      mem[3] = color2;
      mem[2] = color2;
      mem[1] = color2;
      mem[0] = color2;
    }

    signed swidth = width;
    do {
      mem[swidth] = color2;
    } while (--swidth >= 0);
    screen += pixlesPerLine;
  }
}

extern inline void drawCircle (char* screenStart,
                               circle_t *circle,
                               point_t *at,
                               unsigned color2);
