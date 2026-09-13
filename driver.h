#ifndef DRIVER_H
#define DRIVER_H

/* driver.h -- Strategy pattern for hardware drivers (thesis correction 2).
 *
 * The kernel never touches hardware directly: every driver publishes a
 * table of operations and registers a device at init time. Clients resolve
 * the device by name or type and call dev->ops->op(dev, ...). Porting to a
 * new platform means writing a new ops table, never rewriting the caller
 * (Open/Closed Principle). The registry is a fixed static table: no heap,
 * no locks (registration is boot-time only, before sti; lookup only reads).
 *
 * Canonical path per the thesis contract: include/kernel/driver.h. This
 * header lives at the repository root because all MiniOS headers do
 * (-I.); it IS that contract, not a copy of it.
 */

#define DEV_NAME_LEN 32
#define DEV_MAX      16

#define DEV_TYPE_BLOCK 1
#define DEV_TYPE_AUDIO 2
#define DEV_TYPE_NET   3
#define DEV_TYPE_CHAR  4

typedef struct device device_t;

typedef struct {
    int      (*read_sectors)(device_t *dev, unsigned lba,
                             unsigned count, void *buf);
    int      (*write_sectors)(device_t *dev, unsigned lba,
                              unsigned count, const void *buf);
    unsigned (*total_sectors)(device_t *dev);
    int      (*present)(device_t *dev);
} block_ops_t;

typedef struct {
    void     (*tone)(device_t *dev, unsigned freq);
    void     (*off)(device_t *dev);
    void     (*set_volume)(device_t *dev, unsigned vol);
    unsigned (*get_volume)(device_t *dev);
    int      (*present)(device_t *dev);
    void     (*pcm_open)(device_t *dev);
    void     (*pcm_close)(device_t *dev);
    int      (*pcm_submit)(device_t *dev, const unsigned char *pcm, unsigned len);
} audio_ops_t;

struct device {
    char              name[DEV_NAME_LEN];
    int               type;
    const block_ops_t *block;
    const audio_ops_t *audio;
    void              *priv;
};

int       device_register(device_t *dev);
device_t *device_find(const char *name);
device_t *device_find_by_type(int type);
int       device_count(void);
void      device_reset(void);

#endif
