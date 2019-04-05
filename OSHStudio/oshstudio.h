#ifndef OSHSTUDIO_H
#define OSHSTUDIO_H

#include <QMainWindow>
#include "hidapi.h"
#include <QThread>
#include<QFileDialog>
#include<QTextStream>
#include "osha2bw.h"
#include "..\common_types\common_structs.h"
#include "oshbuttonw.h"

namespace Ui {
class OSHStudio;
//class WorkerThread;
}

struct single_encoders_pins {
    uint8_t pinA;
    uint8_t pinB;
};

struct A2B_params {
    osha2bw * widget_ptr;
    uint8_t number_buttons;
    uint8_t pin_number;
};

struct SB_params {
    oshbuttonw * SB_wid_prt;
    button_mode button_type;
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
  struct A2B_params A2Bstore[MAX_A2B_INPUTS];
  struct SB_params SBstore[MAX_BUTTONS];
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
  uint8_t A2BButtons = 0;
  uint16_t TotalButtons;
  uint8_t RotSwitchPoles;
  uint8_t RotSwitchWires;
  uint8_t Analog2Buttons_inputs;
  uint8_t pov1;
  uint8_t pov2;
  uint8_t pov3;
  uint8_t pov4;
  uint16_t axes_shapes[MAX_AXES][SHAPEVALUES];

private slots:
  void drawHelpSB(void);
  void setShapesW(void);
  void get_all_A2B_buttons(void);
  void get_all_SB_buttons(void);
  void populateDefSB(void);
  void getConfig_Slot();
  void gatherConfig_Slot();
  void getACKpacket(uint8_t);
  void getConfigPacket(uint8_t * buf);
  void writeConfig_Slot();
  void resetConfig_Slot();
  void setConfig_Slot();
  void restoreConfig_Slot();
  void resetConfigValues(void);
  void show_USB_ident_uniq(QString ident);
  void show_USB_exch_rate(int interval);
  void showBoardType(int boardtype);
  uint8_t convertPinnameToIndex (QString pname);
  void drawHelpSE();
  void profile_name_changed(QString);
  void getGamepadPacket(uint8_t *);
  void showConnectDeviceInfo();
  void hideConnectDeviceInfo();
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
  void populateDefA2B();
  void showA2Btab();
  void resetAllA2B();
  void showSingleEncodersTab(void);
  void current_profile_changed(int current_profile);
  void update_ro_shapes(void);
};

#endif // OSHSTUDIO_H
