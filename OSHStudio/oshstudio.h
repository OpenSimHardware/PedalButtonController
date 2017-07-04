#ifndef OSHSTUDIO_H
#define OSHSTUDIO_H

#include <QMainWindow>
#include "hidapi.h"
#include <QThread>
#include<QFileDialog>
#include<QTextStream>

//Input/output usb packet
#define BUFFSIZE 64
#define PINS 32
#define AXISES 6

#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >>8))

namespace Ui {
class OSHStudio;
//class WorkerThread;
}

class OSHStudio : public QMainWindow
{
  Q_OBJECT

public:
  explicit OSHStudio(QWidget *parent = 0);
  ~OSHStudio();

private:
  Ui::OSHStudio *ui;
  hid_device *handle_device;

  typedef enum {
      Not_Used = 0,
      AnalogNoSmooth = 1,
      AnalogLowSmooth = 2,
      AnalogMedSmooth = 3,
      AnalogHighSmooth = 4,
      Rotary_PINA = 5,
      Rotary_PINB = 6,
      Rotary_Enc = 7,
      Button_ROW = 8,
      Button_COLUMN = 9,
      Button = 10,
      Button_GND = 11,
      RotSwPole = 12,
      RotSwWire = 13,
} pintype;

private slots:
  void getConfig_Slot();
  void writeConfig_Slot();
  void drawAxis1Value(uint16_t axis_value);
  void drawAxis2Value(uint16_t axis_value);
  void drawAxis3Value(uint16_t axis_value);
  void drawAxis4Value(uint16_t axis_value);
  void drawAxis5Value(uint16_t axis_value);
  void drawAxis6Value(uint16_t axis_value);
  void drawButtons1Value(uint64_t buttons_value);
  void drawButtons2Value(uint64_t buttons_value);
  void drawPOVSvalue(uint64_t POVS_value);
  void showConnectDeviceInfo();
  void hideConnectDeviceInfo();
  QString DrawTypeComboBox(pintype i);
  QString convertIntToString(int i);
  int convertStringToInt(QString str);
  void lineEditAxis1Min_Slot(int i);
  void horiSliderAxis1Min_Slot(QString str);
  void lineEditAxis1Max_Slot(int i);
  void horiSliderAxis1Max_Slot(QString str);
  void lineEditAxis2Min_Slot(int i);
  void horiSliderAxis2Min_Slot(QString str);
  void lineEditAxis2Max_Slot(int i);
  void horiSliderAxis2Max_Slot(QString str);
  void lineEditAxis3Min_Slot(int i);
  void horiSliderAxis3Min_Slot(QString str);
  void lineEditAxis3Max_Slot(int i);
  void horiSliderAxis3Max_Slot(QString str);
  void lineEditAxis4Min_Slot(int i);
  void horiSliderAxis4Min_Slot(QString str);
  void lineEditAxis4Max_Slot(int i);
  void horiSliderAxis4Max_Slot(QString str);
  void lineEditAxis5Min_Slot(int i);
  void horiSliderAxis5Min_Slot(QString str);
  void lineEditAxis5Max_Slot(int i);
  void horiSliderAxis5Max_Slot(QString str);
  void lineEditAxis6Min_Slot(int i);
  void horiSliderAxis6Min_Slot(QString str);
  void lineEditAxis6Max_Slot(int i);
  void horiSliderAxis6Max_Slot(QString str);
  void comboBoxPaint();
  void loadFromFile();
  void saveToFile();
  void drawHelp();
  void gatherAllConf();
  void gatherPinConfig(pintype i);
  void checkBoxPOV1Changed(int state);
  void checkBoxPOV2Changed(int state);
  void checkBoxPOV3Changed(int state);
  void checkBoxPOV4Changed(int state);
};

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
    void putConnectedDeviceInfo(void);

private:
    uint16_t adc_value=0;
    uint8_t channel=0;

};


#endif // OSHSTUDIO_H
