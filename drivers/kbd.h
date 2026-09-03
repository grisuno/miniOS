#ifndef KBD_H
#define KBD_H

int  kbd_available(void);
int  kbd_read(void);
void kbd_reset_for_shell(void);

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
