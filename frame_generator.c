#include "frame_generator.h"

static FrameInfo frameInfo = {
    .endOfFrameInd = FrameIncomplete,
    .framePartialLength = TransferBlockSize,
    .frameCounter = 0,
    .frameTime = 1111};

static TransferInfo transferInfo = {
    .SubBuffersProcessed = 0,
    .BuffersProcessed = 0,
    .frameCounter = 1111};

uint8_t frameBuffer[TransferBlockSize];

uint32_t fillVideoBufferWithColorRgb24(uint8_t *UsbBuffer, uint8_t RColor, uint8_t GColor, uint8_t BColor)
{
    if (UsbBuffer == NULL)
        return 0;

    if (transferInfo.SubBuffersProcessed == 0)
    {
        if (transferInfo.BuffersProcessed == (BufferCount - 1))
            frameInfo.endOfFrameInd = FrameComplete;
        else
            frameInfo.endOfFrameInd = FrameIncomplete;

        frameInfo.frameCounter++;

        memcpy(frameBuffer, &frameInfo, HeaderSize);
        for (uint32_t i = HeaderSize; i < TransferBlockSize; i += 3)
        {
            frameBuffer[i + 0] = RColor;
            frameBuffer[i + 1] = GColor;
            frameBuffer[i + 2] = BColor;
        }
    }

    uint32_t offset = transferInfo.SubBuffersProcessed * UsbFullSpeedBufferSize;
    memcpy(UsbBuffer, frameBuffer + offset, UsbFullSpeedBufferSize);

    transferInfo.SubBuffersProcessed++;

    if (transferInfo.SubBuffersProcessed >= SubBufferCount)
    {
        transferInfo.SubBuffersProcessed = 0;
        transferInfo.BuffersProcessed = (transferInfo.BuffersProcessed + 1) % BufferCount;
    }

    return UsbFullSpeedBufferSize;
}

uint32_t fillVideoBufferDynamic(uint8_t *UsbBuffer)
{
    if (UsbBuffer == NULL)
        return 0;

    return 0;
}

bool isBufferProcessed(void)
{
    return (transferInfo.BuffersProcessed == 0);
}

bool isSubBufferProcessed(void)
{
    return (transferInfo.SubBuffersProcessed == 0);
}