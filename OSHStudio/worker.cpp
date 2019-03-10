#include "worker.h"
#include <QThread>
#include "hidapi.h"
#include "../common_types/common_structs.h"

extern hid_device *handle_read, *handle_write;
//TODO make it non-global

void Worker::processData(void) {
    uint8_t buf[BUFFSIZE]={0};
    int res=0;
    struct gamepad_report_ empty_gamepad_report;
    uint8_t empty_buf[sizeof(struct gamepad_report_)];

    empty_gamepad_report.packet_id = 1;
    empty_gamepad_report.buttons = 0;
    for (uint8_t i=0;i<MAX_AXES;i++){
        empty_gamepad_report.axis[i] = 0;
    }
    for (uint8_t i=0;i<MAX_POVS;i++){
        empty_gamepad_report.pov[i] = 8;
    }
    memcpy(&(empty_buf),&(empty_gamepad_report.packet_id),sizeof(struct gamepad_report_));

while (1) {
    if (!handle_read) {
        handle_read = hid_open(0x1209, 0x3100,nullptr);
        if (!handle_read) {
            emit putGamepadPacket(empty_buf);
            emit putDisconnectedDeviceInfo();
            QThread::sleep(1);
        } else {
            emit putConnectedDeviceInfo();
        }
     }

     if (handle_read) {
          //  res=hid_read_timeout(handle_read, buf, BUFFSIZE,500);
        res=hid_read_timeout(handle_read, buf, BUFFSIZE,50);
            if (res < 0) {
                hid_close(handle_read);
                handle_read=nullptr;
             } else {
                if (buf[0] == 1) {
                    emit putGamepadPacket(buf);
                    QThread::msleep(10);
                }
                if (buf[0] == 4) {
                    emit putConfigPacket(buf);
                }
                if (buf[0] == 5) {
                    emit putACKpacket(buf[1]);
                }
            }
      }
   }
}
