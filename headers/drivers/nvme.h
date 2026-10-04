#ifndef DRIVERS_NVME_H
#define DRIVERS_NVME_H

int nvme_init(void);
int nvme_present(void);
unsigned nvme_version(void);
const char *nvme_note(void);
unsigned long nvme_sectors(void);
int nvme_read_sectors(unsigned lba, unsigned count, void *buf);

#endif
