#include "worker.h"
#include <QThread>
#include "hidapi.h"

extern hid_device *handle_read, *handle_write;
//TODO make it non-global

void Worker::processData(void) {
    uint8_t buf[BUFFSIZE]={0};
    int8_t res=0;
    uint64_t buttonsState=0;
    hid_device_info * cur_dev;


while (1) {
     if (!handle_read) {
      handle_read = hid_open(0x1209, 0x3100,NULL);
      if (!handle_read) {
          emit putAxis1Value(0);
          emit putAxis2Value(0);
          emit putAxis3Value(0);
          emit putAxis4Value(0);
          emit putAxis5Value(0);
          emit putAxis6Value(0);
          emit putButtons1Value(0);
          emit putButtons2Value(0);
          emit putPOVSvalue(0x08080808);
          emit putDisconnectedDeviceInfo();
          QThread::sleep(1);
      } else {
        res=hid_set_nonblocking(handle_read, 1);
        cur_dev = hid_enumerate(0x1209, 0x3100);
        emit putConnectedDeviceInfo(cur_dev->release_number);
        }
     }

     if (handle_read) {
          //  res=hid_read_timeout(handle_read, buf, BUFFSIZE,500);
          res=hid_read_timeout(handle_read, buf, BUFFSIZE,50);
            if (res < 0) {
                hid_close(handle_read);
                handle_read=0;
             } else {
                if (buf[0] == 1) {
                    emit putAxis1Value(buf[10]*0x100+buf[9]);
                    emit putAxis2Value(buf[12]*0x100+buf[11]);
                    emit putAxis3Value(buf[14]*0x100+buf[13]);
                    emit putAxis4Value(buf[16]*0x100+buf[15]);
                    emit putAxis5Value(buf[18]*0x100+buf[17]);
                    emit putAxis6Value(buf[20]*0x100+buf[19]);
                    buttonsState=(buf[4]<<24)+(buf[3]<<16)+(buf[2]<<8)+buf[1];
                    emit putButtons1Value(buttonsState);
                    buttonsState=(buf[8]<<24)+(buf[7]<<16)+(buf[6]<<8)+buf[5];
                    emit putButtons2Value(buttonsState);
                    buttonsState=(buf[24]<<24)+(buf[23]<<16)+(buf[22]<<8)+buf[21];
                    emit putPOVSvalue(buttonsState);
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
