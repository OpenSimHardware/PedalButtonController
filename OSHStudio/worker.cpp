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
    struct sensor_report_ empty_sensor_report;
    uint8_t empty_buf_gamepad[sizeof(struct gamepad_report_)];
    uint8_t empty_buf_sensor[sizeof(struct sensor_report_)];
    uint8_t i = 0;
    const uint8_t hb_packet[BUFFSIZE] = {2,254,0};

    empty_gamepad_report.packet_id = 1;
    empty_gamepad_report.buttons = 0;
    for (uint8_t i=0;i<MAX_AXES;i++){
        empty_gamepad_report.axis[i] = 0;
    }
    for (uint8_t i=0;i<MAX_POVS;i++){
        empty_gamepad_report.pov[i] = 8;
    }
    memcpy(&(empty_buf_gamepad),&(empty_gamepad_report.packet_id),sizeof(struct gamepad_report_));

    empty_sensor_report.packet_id=5;
    for (int i=0;i<MAX_A2B_INPUTS;i++){
        empty_sensor_report.min_calib[i] = 0;
        empty_sensor_report.max_calib[i] = 0;
        empty_sensor_report.sensor_value[i] = 0;
    }
    memcpy(&(empty_buf_sensor),&(empty_sensor_report.packet_id),sizeof(struct sensor_report_));

while (1) {
    if (!handle_read) {
        handle_read = hid_open(0x1209, 0x3100,nullptr);
        if (!handle_read) {
            emit putGamepadPacket(empty_buf_gamepad);
            emit putSensorPacket(empty_buf_sensor);
            emit putDisconnectedDeviceInfo();
            QThread::sleep(1);
        } else {
            emit putConnectedDeviceInfo();
        }
     }


     if (handle_read) {
        res=hid_read_timeout(handle_read, buf, BUFFSIZE,20);
         //  res=hid_read(handle_read, buf, BUFFSIZE);
        if (res < 0) {
            hid_close(handle_read);
            handle_read=nullptr;
         } else {
            if (buf[0] == 1) {
                uint8_t gamepad_buf[BUFFSIZE]={0};
                memcpy(gamepad_buf,buf,BUFFSIZE);
                emit putGamepadPacket(gamepad_buf);
            }
            if (buf[0] == 4) {
                uint8_t config_buf[BUFFSIZE]={0};
                memcpy(config_buf,buf,BUFFSIZE);
                emit putConfigPacket(config_buf);
            }
            if ((buf[0] == 5) && (buf[1] != 254)){
                uint8_t ack_buf[BUFFSIZE]={0};
                memcpy(ack_buf,buf,BUFFSIZE);
                emit putACKpacket(ack_buf);
            }
            if ((buf[0] == 5) && (buf[1] == 254)) {
                uint8_t sensor_buf[BUFFSIZE]={0};
                memcpy(sensor_buf,buf,BUFFSIZE);
                emit putSensorPacket(sensor_buf);
                  //  QThread::msleep(30);
            }
            //emit putHBPacket();
            if (!(i++%10)){
                hid_write(handle_read, hb_packet, BUFFSIZE);
            }

            QThread::msleep(10);
          }
        }
      }
   }



