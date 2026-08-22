/* doom_hal.c - Hardware Abstraction Layer for doomgeneric on MiniOS.
 *
 * Implements the 5 functions doomgeneric expects, using MiniOS syscalls:
 *   204 = SYS_TIME (milliseconds via RDTSC)
 *   205 = SYS_KBD  (PS/2 scancode, non-blocking)
 *   206 = SYS_PALETTE (VGA DAC 256-color load)
 *
 * This file is meant to be compiled on the HOST with the host toolchain
 * together with doomgeneric source, producing a static ELF that runs inside
 * MiniOS.  The resulting binary is uploaded as `bin/doom.elf` and run via
 * `run bin/doom.elf` from the MiniOS shell.
 */

#include <stdint.h>
#include <stddef.h>

/* ---------- MiniOS syscall wrappers (inline syscall instruction) ---------- */

static long syscall1(long n, long a1) {
    long ret;
    /* rax = n, rdi = a1, then syscall; result in rax */
    __asm__ volatile ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
    return ret;
}

static long syscall2(long n, long a1, long a2) {
    long ret;
    /* rax = n, rdi = a1, rsi = a2, then syscall; result in rax */
    __asm__ volatile ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2) : "rcx", "r11", "memory");
    return ret;
}

/* ---------- doomgeneric interface (stubs / minimal impl) ---------- */

#define FB_ADDR ((uint8_t *)0x1F00000UL) /* framebuffer virtual, mapped in mmap */

/* 1. Inicialización: cargar la paleta por defecto de DOOM */
void DG_Init(void) {
    /* Cargar la paleta integrada (hardcoded) al DAC de VGA.
     * La paleta de DOOM usa RGB de 8 bits; el DAC de VGA usa 6 bits,
     * así que desplazamos 2 bits a la derecha. */
    static const unsigned char doom_palette[768] = {
        /* Se omitiría la paleta completa de 256 colores por espacio.
         * En la compilación real se embeddea un archivo .h generado
         * desde los .lump del WAD.  Aquí ponemos un placeholder que
         * hará que el fondo sea oscuro/verde típico de DOOM. */
    };
    /* Llenar con una paleta mínima si el embed no está disponible */
    if (doom_palette[0] == 0) {
        /* Paleta por defecto: tonos verdes/oscuros typicos de DOOM */
        int i;
        for (i = 0; i < 768; i++) {
            /* Patrones simples por canal */
            unsigned char v = (i % 256);
            ((unsigned char *)doom_palette)[i] = v;
        }
    }
    syscall2(206, (long)doom_palette, 0);
}

/* 2. Dibujar frame: copia el buffer de doomgeneric al framebuffer VGA */
void DG_DrawFrame(void) {
    /* DOOM renderiza en su buffer interno (320x200 = 64000 bytes).
     * Copiamos directamente a la dirección virtual del framebuffer.
     * En una implementación real DOOM pasaría un puntero al buffer;
     * aquí asumimos que el buffer está en una dirección conocida. */
    /* Placeholder: llenar el framebuffer con un patrón de chequeras
     * simple mientras tanto. */
    int x, y;
    for (y = 0; y < 200; y++) {
        for (x = 0; x < 320; x++) {
            uint8_t color = ((x & 8) ^ (y & 8)) ? 0xFF : 0x00;
            FB_ADDR[y * 320 + x] = color;
        }
    }
}

/* 3. Tiempo: devuelve milisegundos */
unsigned int DG_GetTicksMs(void) {
    return (unsigned int)syscall1(204, 0);
}

/* 4. Teclado: lee una tecla de la cola PS/2 sin bloquear */
int DG_GetKey(int *pressed, unsigned char *key) {
    int k = (int)syscall1(205, 0);
    if (k == -1) {
        *pressed = 0;
        return 0;
    }
    *pressed = 1;
    *key = (unsigned char)k;
    return 1;
}

/* 5. Sleep: espera ms milisegundos (busy-wait) */
void DG_SleepMs(unsigned int ms) {
    unsigned int start = DG_GetTicksMs();
    while (DG_GetTicksMs() - start < ms) {
        /* busy-wait; el kernel no tiene scheduler, así que esto bloquea
         * al programa pero es aceptable para un sistema single-task. */
        __asm__ volatile ("pause");
    }
}

/* ---------- Punto de entrada para ELF estático ---------- */

void _start(void) {
    /* Inicializar doomgeneric */
    DG_Init();

    /* Bucle principal del motor */
    while (1) {
        DG_DrawFrame();
        /* Chequeo de teclado y actualización de juego iria aquí. */
        int pressed;
        unsigned char key;
        if (DG_GetKey(&pressed, &key)) {
            /* Manejo de entrada del teclado */
        }
        DG_SleepMs(16); /* ~60 FPS */
    }
}