#include <stdint.h>
#include "../consts.h"

#ifndef BFS_H
#define BFS_H

#define ROOT_DIR_LBA 64
#define ROOT_DIR_SECTORS 8
#define ROOT_DIR_SIZE (ROOT_DIR_SECTORS * 512)


void PrintHex(unsigned char byte, int y, int x);

static inline void outb(uint16_t port, uint8_t value) 
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) 
{
    uint8_t ret;
    __asm__ volatile ("inb %1, %0"
                      : "=a"(ret)
                      : "Nd"(port));
    return ret;
}

static inline uint16_t inw(uint16_t port) 
{
    uint16_t ret;
    __asm__ volatile ("inw %1, %0"
                      : "=a"(ret)
                      : "Nd"(port));
    return ret;
}

static inline void outw(uint16_t port, uint16_t val) 
{
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}

bool is_bit_free(int bit) ;
void set_bit(int bit);
uint32_t AllocateFileSectors(uint8_t size);

void CreateFile(const char* name, const char *ext, uint8_t size);
void ReadSector(uint32_t sectorId, uint8_t* bufer);
void WriteSector(uint32_t lba, const char *buffer, int sizeoftext);
void ShowFiles();


#endif

