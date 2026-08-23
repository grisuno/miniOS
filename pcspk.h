#ifndef PCSPK_H
#define PCSPK_H

#define PCSPK_VOL_MIN     0
#define PCSPK_VOL_MAX     100
#define PCSPK_VOL_DEFAULT 100

void     pcspk_init(void);
void     pcspk_tone(unsigned freq);
void     pcspk_off(void);
void     pcspk_set_volume(unsigned volume);
unsigned pcspk_get_volume(void);

#endif
