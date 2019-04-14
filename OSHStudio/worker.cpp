#include "worker.h"
#include <QThread>
#include "hidapi.h"
#include "../common_types/common_structs.h"

extern hid_device *handle_read;
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
            emit putSensorPacket(empty_buf);
            emit putDisconnectedDeviceInfo();
            QThread::sleep(1);
        } else {
              emit putConnectedDeviceInfo();
        }
     }


     if (handle_read) {
    //    current_time = QTime::currentTime();
    //    if (!(current_time.msec()%HBTIME)) {
            //hid_write(handle_read, hb_packet, BUFFSIZE);
            emit putHBPacket();
    //    }
        QThread::msleep(30);
         //  res=hid_read(handle_read, buf, BUFFSIZE);
        res=hid_read_timeout(handle_read, buf, BUFFSIZE,20);
            if (res < 0) {
                hid_close(handle_read);
                handle_read=nullptr;
             } else {
                if (buf[0] == 1) {
                    emit putGamepadPacket(buf);
                    //QThread::msleep(30);
                }
             }
        }
      }
   }


void Worker::processCHIDData(void){
    uint8_t buf[BUFFSIZE]={0};
    int res=0;
    while (1){
        if (handle_read) {
            QThread::msleep(30);
        res=hid_read_timeout(handle_read, buf, BUFFSIZE,20);
            if (res < 0) {
               hid_close(handle_read);
               handle_read=nullptr;
            } else {
               if (buf[0] == 4) {
                    emit putConfigPacket(buf);
               }
               if ((buf[0] == 5) && (buf[1] != 254)){
                    emit putACKpacket(buf);
               }
                //QThread::msleep(30);
           }
        } else {
           QThread::sleep(1);
        }
    }
}

void Worker::processSensorData(void){
    uint8_t buf[BUFFSIZE]={0};
    int res=0;
    while (1){
        if (handle_read) {
        res=hid_read_timeout(handle_read, buf, BUFFSIZE,20);
            if (res < 0) {
               hid_close(handle_read);
               handle_read=nullptr;
            } else {
                if ((buf[0] == 5) and (buf[1] == 254)) {
                        emit putSensorPacket(buf);
                        QThread::msleep(30);
                }
                //QThread::msleep(30);
           }
        } else {
           QThread::sleep(1);
        }
    }
}

