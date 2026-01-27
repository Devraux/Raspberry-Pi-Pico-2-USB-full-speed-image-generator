import usb1
import time
import struct

VENDOR_ID =  ???
PRODUCT_ID = ???
EP_IN = ???

######################################
## CHOOSE PROPER DATA VISUALIZATION ##
######################################

SHOW_PAYLOAD = False

######################################

with usb1.USBContext() as ctx:
    dev = ctx.openByVendorIDAndProductID(VENDOR_ID, PRODUCT_ID)
    if not dev:
        print("Device not found")
        exit()

    dev.setConfiguration(1)          
    dev.claimInterface(0)

    total_bytes = 0
    eof_counter = 0
    last_stat_time = time.time()

    while True:
        try:
            data = dev.bulkRead(EP_IN, 64, timeout=1000)
            
            if data:
                total_bytes += len(data)
                
                if len(data) >= 4:
                    eof_flag = struct.unpack('<I', data[:4])[0]
                    if eof_flag == 1:
                        eof_counter += 1

                if SHOW_PAYLOAD:
                    hex_data = " ".join(f"{b:02x}" for b in data)
                    print(f"Payload: {hex_data}")
                
            current_time = time.time()
            elapsed_since_stat = current_time - last_stat_time
            
            if elapsed_since_stat >= 1.0:
                bps = (total_bytes * 8) / elapsed_since_stat
                kbps = bps / 1024
                mbps = kbps / 1024
                
                print(f"Bitrate: {kbps:.2f} kbps ({mbps:.2f} Mbps) | Received: {total_bytes} Bytes | EOF count: {eof_counter}")
                total_bytes = 0
                last_stat_time = current_time

        except usb1.USBErrorTimeout:
            pass
        except KeyboardInterrupt:
            print("\nProgram finished")
            break
        except Exception as e:
            print(f"Error: {e}")
            break