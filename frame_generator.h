#ifndef _FRAME_GENERATOR_
#define _FRAME_GENERATOR_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define TransferBlockSize (40960)
#define SubBufferCount (640) // (40960 / UsbFullSpeedBufferSize)
#define BufferCount (152)

#define HeaderSize (sizeof(FrameInfo))
#define PayloadSize (TransferBlockSize - HeaderSize)
#define VideoChannelsNumber 3 // RGB24 = 3, RAW16 = 2, RAW8 = 1

#define FrameIncomplete 0
#define FrameComplete 1

#define UsbFullSpeedBufferSize 64

uint32_t fillVideoBufferWithColorRgb24(uint8_t *UsbBuffer, uint8_t RColor, uint8_t GColor, uint8_t BColor);

bool isBufferProcessed(void);

bool isSubBufferProcessed(void);


typedef struct FrameInfo
{
    uint32_t endOfFrameInd;      // 1 - End Of Frame(EOF), 0 otherwise
    uint32_t framePartialLength; // Partial buffer length, in all cases in stead of last frame it is daBuffer.size
    uint32_t frameCounter;       // Frame counter
    uint32_t frameTime;          // frame time stamp
} FrameInfo;

typedef struct TransferInfo
{
    uint32_t SubBuffersProcessed; // Number of 64-byte chunks already filled in the current frame buffer
    uint32_t BuffersProcessed;    // Number of 40960-byte chunks filled
    uint32_t frameCounter;
} TransferInfo;

#endif