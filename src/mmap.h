#ifndef CEDA_DEMO_MMAP
#define CEDA_DEMO_MMAP

enum mmap_mode_t {
    MMAP_MODE_LINEAR = 0x01,
    MMAP_MODE_CEDA_VIDEO = 0x00,
    MMAP_MODE_CEDA_ATTR = 0x80,
};

void mmap_set(enum mmap_mode_t mode);
enum mmap_mode_t mmap_get(void);

#endif // CEDA_DEMO_MMAP
