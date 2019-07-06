#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTime>
#include "..\common_types\common_defines.h"

class Worker : public QObject {
      Q_OBJECT

public slots:
    void processData(void);


signals:
    void putDisconnectedDeviceInfo(void);
    void putConnectedDeviceInfo(void);
    void putConfigPacket(uint8_t *);
    void putACKpacket(uint8_t *);
    void putGamepadPacket(uint8_t *);
    void putSensorPacket(uint8_t *);
    void putHBPacket(void);

private:
    uint16_t adc_value=0;
    uint8_t channel=0;
    QTime current_time;
};


#endif // WORKER_H
