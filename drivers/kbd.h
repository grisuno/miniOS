#ifndef KBD_H
#define KBD_H

/* Keyboard layout: US qwerty (default) or Spanish (Spain) qwerty. Toggled
 * from the taskbar widget or the `kbd` shell builtin. */
#define KBD_LAYOUT_EN 0
#define KBD_LAYOUT_ES 1

int  kbd_available(void);
int  kbd_read(void);
void kbd_reset_for_shell(void);

/* Layout selection */
int  kbd_get_layout(void);
void kbd_set_layout(int layout);
void kbd_toggle_layout(void);

/* Printable test for console input: ASCII 32..126 plus Latin-1 160..255
 * (the ES layout emits single-byte Latin-1 for ñ ¡ ¿ ´ ¨ · ª º ç Ç ¬).
 * DEL (127) and the C1 controls (128..159) are never input. */
static inline int kbd_is_printable(int c) {
    return (c >= 32 && c <= 126) || (c >= 160 && c <= 255);
}

/* Translated queue (shell input) */
int  kbd_q_empty(void);
int  kbd_q_pop(void);
void kbd_q_push(unsigned char c);

/* Raw queue (DOOM / SYS_KBD) */
int  kbd_raw_mode_get(void);
void kbd_raw_mode_set(int on);
int  kbd_raw_empty(void);
int  kbd_raw_pop(void);
void kbd_raw_push_byte(unsigned char c);
int  kbd_e0_get(void);
void kbd_e0_set(int v);
void kbd_flush_all(void);

#endif
