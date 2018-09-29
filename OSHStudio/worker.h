#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "..\common_types\common_defines.h"

class Worker : public QObject {
      Q_OBJECT

public slots:
    void processData(void);

signals:
    void putAxis1Value(uint16_t axis_value);
    void putAxis2Value(uint16_t axis_value);
    void putAxis3Value(uint16_t axis_value);
    void putAxis4Value(uint16_t axis_value);
    void putAxis5Value(uint16_t axis_value);
    void putAxis6Value(uint16_t axis_value);
    void putButtons1Value(uint64_t buttons_value);
    void putButtons2Value(uint64_t buttons_value);
    void putPOVSvalue(uint64_t buttons_value);
    void putDisconnectedDeviceInfo(void);
    void putConnectedDeviceInfo(uint8_t firmware_release);
    void putConfigPacket(uint8_t *);
    void putACKpacket(uint8_t);

private:
    uint16_t adc_value=0;
    uint8_t channel=0;

};


#endif // WORKER_H
