#ifndef OSHSTUDIO_H
#define OSHSTUDIO_H

#include <QMainWindow>
#include "hidapi.h"
#include <QThread>
#include<QFileDialog>
#include<QTextStream>
#include "..\common_types\common_structs.h"

namespace Ui {
class OSHStudio;
//class WorkerThread;
}

struct single_encoders_pins {
    uint8_t pinA;
    uint8_t pinB;
};

struct pin_comp_geometry {
    QString Label_name;
    uint16_t Label_X;
    uint16_t Label_Y;
    QString ComboBox_name;
    uint16_t ComboBox_X;
    uint16_t ComboBox_Y;
};


class OSHStudio : public QMainWindow
{
  Q_OBJECT

public:
  explicit OSHStudio(QWidget *parent = 0);
  ~OSHStudio();

private:
  Ui::OSHStudio *ui;
  hid_device *handle_device;
  struct total_config_ config;
  struct single_encoders_pins single_encoders_1_store[MAX_SINGLE_ENCODERS];
  struct single_encoders_pins single_encoders_2_store[MAX_SINGLE_ENCODERS];
  struct single_encoders_pins single_encoders_4_store[MAX_SINGLE_ENCODERS];
  uint8_t single_encoders_1;
  uint8_t single_encoders_2;
  uint8_t single_encoders_4;
  QStringList PINAlist, PINBlist;
  uint8_t NumberAnalogInputs;
  uint8_t Chain_PinA;
  uint8_t Chain_PinB;
  uint8_t Chain_Rotaries_1;
  uint8_t Chain_Rotaries_2;
  uint8_t Chain_Rotaries_4;
  uint8_t Single_Rotaries_PINA_1;
  uint8_t Single_Rotaries_PINB_1;
  uint8_t Single_Rotaries_PINA_2;
  uint8_t Single_Rotaries_PINB_2;
  uint8_t Single_Rotaries_PINA_4;
  uint8_t Single_Rotaries_PINB_4;
  uint8_t ButtonsRows;
  uint8_t ButtonsColumns;
  uint8_t Buttons;
  uint8_t RotSwitchPoles;
  uint8_t RotSwitchWires;

private slots:
  void getConfig_Slot();
  void gatherConfig_Slot();
  void getACKpacket(uint8_t);
  void getConfigPacket(uint8_t * buf);
  void writeConfig_Slot();
  void resetConfig_Slot();
  void setConfig_Slot();
  void restoreConfig_Slot();
  void show_USB_ident_uniq(QString ident);
  void show_USB_exch_rate(int interval);
  void showBoardType(int boardtype);
  uint8_t convertPinnameToIndex (QString pname);
  void drawHelpSE();
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
  QString convertIntToString(int i);
  void showPercentAxisComb(int i);
  void showPin1AxisComb(QString pinname);
  void showPin2AxisComb(QString pinname);
  void showAxisCombSection(bool checked);
  void showAxisCombSlider(bool state);
  void loadFromFile();
  void saveToFile();
  void drawHelp();
  void gatherPinsConf();
  void pinConfChanged();
  void populateDefSE();
  void showSingleEncodersTab(void);
  void checkBoxPOV1Changed(int state);
  void checkBoxPOV2Changed(int state);
  void checkBoxPOV3Changed(int state);
  void checkBoxPOV4Changed(int state);
};

#endif // OSHSTUDIO_H
