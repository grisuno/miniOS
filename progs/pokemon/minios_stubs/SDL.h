/* SDL.h stub for MiniOS cross-compilation */
#ifndef SDL_H_STUB_MINIOS
#define SDL_H_STUB_MINIOS
#include <stdint.h>
typedef uint64_t Uint64;
typedef uint32_t Uint32;
typedef int32_t Sint32;
typedef int16_t Sint16;
typedef uint8_t Uint8;

static inline Uint64 SDL_GetPerformanceCounter(void) { return 0; }
static inline Uint64 SDL_GetPerformanceFrequency(void) { return 1; }
static inline Uint32 SDL_GetTicks(void) { return 0; }
static inline void SDL_Delay(Uint32 ms) { (void)ms; }
#endif
