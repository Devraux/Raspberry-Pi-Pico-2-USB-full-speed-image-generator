![Visitor Badge](https://visitor-badge.laobi.icu/badge?page_id=Devraux.Raspberry-Pi-Pico-2-USB-full-speed-image-generator)


# RP2350 Bare-Metal USB RGB888 Streamer

This project implements a low-level USB data provider for the **Raspberry Pi Pico 2 (RP2350)**. It is designed to simulate high-throughput USB devices that transmit raw image data (RGB888) directly to a host. 

The project successfully achieves a stable transfer rate of **3 MB/s**, pushing the limits of USB Full Speed (12 Mbps) through highly optimized bare-metal register access.

## Overview

The firmware generates synthetic **RGB888** data chunks. Currently, it cycles the color of the entire transmitted image (Red -> Green -> Blue) once the full frame is completed. This allows for easy visual verification of data integrity on the host side.

### Data Structure & Buffering
Transmission is organized into large memory blocks. Each block is segmented into standard 64-byte USB packets.

**Transfer Block Layout (40,960 Bytes):**
```text
  +-----------------------------------------------------------------------+
  |    Header (16 Bytes)   |              Payload (RGB888)                |
  +------------------------+----------------------------------------------+
  | [0]  EOF Indicator     | [16] Pixel 0: R                              |
  | [4]  Partial Length    | [17] Pixel 0: G                              |
  | [8]  Frame Counter     | [18] Pixel 0: B                              |
  | [12] Timestamp         | [19] Pixel 1: R ...                          |
  +------------------------+----------------------------------------------+
  | <--- Fixed Header ---> | <--- 40,944 Bytes of Raw Pixel Data ------>  |
  +-----------------------------------------------------------------------+
