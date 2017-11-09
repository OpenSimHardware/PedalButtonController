#include "oshstudio.h"
#include "ui_oshstudio.h"
#include<QTextEdit>
#include<QMessageBox>



hid_device *handle_read, *handle_write;

uint8_t NumberAnalogInputs,
        Chain_PinA,
        Chain_PinB,
        Chain_Rotaries_1,
        Chain_Rotaries_2,
        Chain_Rotaries_4,
        Single_Rotaries_PINA_1,
        Single_Rotaries_PINB_1,
        Single_Rotaries_PINA_2,
        Single_Rotaries_PINB_2,
        Single_Rotaries_PINA_4,
        Single_Rotaries_PINB_4,
        ButtonsRows,
        ButtonsColumns,
        Buttons,
        RotSwitchPoles,
        RotSwitchWires;
uint8_t Total_Single_encoders=0;
uint8_t AxisComb_StartPin=0,
        AxisComb_EndPin=0,
        AxisComb_Percent=0;
struct single_encoders_pins single_encoders_store[14] = {0,0,0,0};


QStringList PINAlist, PINBlist;

void Worker::processData(void) {
    uint8_t buf[BUFFSIZE]={0};
    struct hid_device_info *cur_dev;
    int8_t res=0;
    uint64_t buttonsState=0;


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
          res=hid_read(handle_read, buf, BUFFSIZE);
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
            }
      }
    }
}


OSHStudio::OSHStudio(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSHStudio)
{
    ui->setupUi(this);
    ui->label_Stud_version->setText("0." + QString::number(OSHSTUDIOVERSION));



    connect (ui->comboBox_BoardType, SIGNAL(currentIndexChanged(int)), SLOT(showBoardType(int)));

      connect(ui->getConfig_button, SIGNAL(clicked()), SLOT(getConfig_Slot()));
      connect(ui->saveConfig_Button, SIGNAL(clicked()), SLOT(writeConfig_Slot()));
      connect(ui->resetConfig_button, SIGNAL(clicked()), SLOT(resetConfig_Slot()));
      connect(ui->restoreConfig_button, SIGNAL(clicked()), SLOT(restoreConfig_Slot()));

      connect(ui->lineEdit_Device_ident, SIGNAL(textEdited(QString)), SLOT(show_USB_ident_uniq(QString)));
      connect(ui->spinBox_USB_exchange, SIGNAL(valueChanged(int)), SLOT(show_USB_exch_rate(int)));

      connect(ui->comboBoxA0, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA0()));
      connect(ui->comboBoxA1, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA1()));
      connect(ui->comboBoxA2, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA2()));
      connect(ui->comboBoxA3, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA3()));
      connect(ui->comboBoxA4, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA4()));
      connect(ui->comboBoxA5, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA5()));
      connect(ui->comboBoxA6, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA6()));
      connect(ui->comboBoxA7, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA7()));
      connect(ui->comboBoxA8, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA8()));
      connect(ui->comboBoxA9, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA9()));
      connect(ui->comboBoxA10, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA10()));
      connect(ui->comboBoxA11, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA11()));
      connect(ui->comboBoxA12, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA12()));
      connect(ui->comboBoxA15, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintA15()));
      connect(ui->comboBoxB0, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB0()));
      connect(ui->comboBoxB1, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB1()));
      connect(ui->comboBoxB3, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB3()));
      connect(ui->comboBoxB4, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB4()));
      connect(ui->comboBoxB5, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB5()));
      connect(ui->comboBoxB6, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB6()));
      connect(ui->comboBoxB7, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB7()));
      connect(ui->comboBoxB8, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB8()));
      connect(ui->comboBoxB9, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB9()));
      connect(ui->comboBoxB10, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB10()));
      connect(ui->comboBoxB11, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB11()));
      connect(ui->comboBoxB12, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB12()));
      connect(ui->comboBoxB13, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB13()));
      connect(ui->comboBoxB14, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB14()));
      connect(ui->comboBoxB15, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintB15()));
      connect(ui->comboBoxC13, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintC13()));
      connect(ui->comboBoxC14, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintC14()));
      connect(ui->comboBoxC15, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaintC15()));

/*
      connect(ui->horiSliderAxis1Min, SIGNAL(valueChanged(int)), SLOT(lineEditAxis1Min_Slot(int)));
      connect(ui->lineEditAxis1Min, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis1Min_Slot(QString)));
      connect(ui->horiSliderAxis1Max, SIGNAL(valueChanged(int)), SLOT(lineEditAxis1Max_Slot(int)));
      connect(ui->lineEditAxis1Max, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis1Max_Slot(QString)));

      connect(ui->horiSliderAxis2Min, SIGNAL(valueChanged(int)), SLOT(lineEditAxis2Min_Slot(int)));
      connect(ui->lineEditAxis2Min, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis2Min_Slot(QString)));
      connect(ui->horiSliderAxis2Max, SIGNAL(valueChanged(int)), SLOT(lineEditAxis2Max_Slot(int)));
      connect(ui->lineEditAxis2Max, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis2Max_Slot(QString)));

      connect(ui->horiSliderAxis3Min, SIGNAL(valueChanged(int)), SLOT(lineEditAxis3Min_Slot(int)));
      connect(ui->lineEditAxis3Min, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis3Min_Slot(QString)));
      connect(ui->horiSliderAxis3Max, SIGNAL(valueChanged(int)), SLOT(lineEditAxis3Max_Slot(int)));
      connect(ui->lineEditAxis3Max, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis3Max_Slot(QString)));

      connect(ui->horiSliderAxis4Min, SIGNAL(valueChanged(int)), SLOT(lineEditAxis4Min_Slot(int)));
      connect(ui->lineEditAxis4Min, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis4Min_Slot(QString)));
      connect(ui->horiSliderAxis4Max, SIGNAL(valueChanged(int)), SLOT(lineEditAxis4Max_Slot(int)));
      connect(ui->lineEditAxis4Max, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis4Max_Slot(QString)));

      connect(ui->horiSliderAxis5Min, SIGNAL(valueChanged(int)), SLOT(lineEditAxis5Min_Slot(int)));
      connect(ui->lineEditAxis5Min, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis5Min_Slot(QString)));
      connect(ui->horiSliderAxis5Max, SIGNAL(valueChanged(int)), SLOT(lineEditAxis5Max_Slot(int)));
      connect(ui->lineEditAxis5Max, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis5Max_Slot(QString)));

      connect(ui->horiSliderAxis6Min, SIGNAL(valueChanged(int)), SLOT(lineEditAxis6Min_Slot(int)));
      connect(ui->lineEditAxis6Min, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis6Min_Slot(QString)));
      connect(ui->horiSliderAxis6Max, SIGNAL(valueChanged(int)), SLOT(lineEditAxis6Max_Slot(int)));
      connect(ui->lineEditAxis6Max, SIGNAL(textEdited(QString)), SLOT(horiSliderAxis6Max_Slot(QString)));
*/
/*      connect(ui->horiSliderAxisCombPin1Min, SIGNAL(valueChanged(int)), SLOT(lineEditAxisCombPin1Min_Slot(int)));
      connect(ui->horiSliderAxisCombPin2Min, SIGNAL(valueChanged(int)), SLOT(lineEditAxisCombPin2Min_Slot(int)));
      connect(ui->horiSliderAxisCombPin1Max, SIGNAL(valueChanged(int)), SLOT(lineEditAxisCombPin1Max_Slot(int)));
      connect(ui->horiSliderAxisCombPin2Max, SIGNAL(valueChanged(int)), SLOT(lineEditAxisCombPin2Max_Slot(int)));
      connect(ui->lineEditAxisCombPin1Min, SIGNAL(textEdited(QString)), SLOT(horiSliderAxisCombPin1Min_Slot(QString)));
      connect(ui->lineEditAxisCombPin2Min, SIGNAL(textEdited(QString)), SLOT(horiSliderAxisCombPin2Min_Slot(QString)));
      connect(ui->lineEditAxisCombPin1Max, SIGNAL(textEdited(QString)), SLOT(horiSliderAxisCombPin1Max_Slot(QString)));
      connect(ui->lineEditAxisCombPin2Max, SIGNAL(textEdited(QString)), SLOT(horiSliderAxisCombPin2Max_Slot(QString)));
*/
      connect(ui->horizontalSliderAxisComb, SIGNAL(valueChanged(int)), SLOT(showPercentAxisComb(int)));
      connect(ui->comboBox_AxisCombBegin, SIGNAL(currentTextChanged(QString)),  SLOT(showPin1AxisComb(QString)));
      connect(ui->comboBox_AxisCombEnd, SIGNAL(currentTextChanged(QString)),  SLOT(showPin2AxisComb(QString)));
      connect(ui->checkBox_AxisComb, SIGNAL(toggled(bool)), SLOT(showAxisCombSection(bool)));
      connect(ui->radioButtonCoopwoork, SIGNAL(toggled(bool)), SLOT(showAxisCombSlider(bool)));

      connect(ui->loadFile_Button, SIGNAL(clicked(bool)), SLOT(loadFromFile()));
      connect(ui->saveFile_Button, SIGNAL(clicked(bool)), SLOT(saveToFile()));

      connect(ui->checkBox_POV1, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV1Changed(int)));
      connect(ui->checkBox_POV2, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV2Changed(int)));
      connect(ui->checkBox_POV3, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV3Changed(int)));
      connect(ui->checkBox_POV4, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV4Changed(int)));


      connect(ui->comboBox_SEA1, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB1, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA2, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB2, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA3, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB3, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA4, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB4, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA5, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB5, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA6, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB6, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA7, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB7, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA8, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB8, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA9, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB9, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA10, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB10, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA11, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB11, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA12, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB12, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA13, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB13, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEA14, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));
      connect(ui->comboBox_SEB14, SIGNAL(activated(int)),  SLOT(comboBoxSEManualConfig()));



      qRegisterMetaType<uint16_t>("uint16_t");
      qRegisterMetaType<uint64_t>("uint64_t");
      qRegisterMetaType<uint16_t>("uint8_t");


//      oshaxis* axis1 = new oshaxis();
//      axis1->


      QThread* thread = new QThread;
      Worker* worker = new Worker();
      worker->moveToThread(thread);

      connect(thread, SIGNAL(started()), worker, SLOT(processData()));
      connect(worker, SIGNAL(putAxis1Value(uint16_t)),
                            SLOT(drawAxis1Value(uint16_t)));
      connect(worker, SIGNAL(putAxis2Value(uint16_t)),
                            SLOT(drawAxis2Value(uint16_t)));
      connect(worker, SIGNAL(putAxis3Value(uint16_t)),
                            SLOT(drawAxis3Value(uint16_t)));
      connect(worker, SIGNAL(putAxis4Value(uint16_t)),
                            SLOT(drawAxis4Value(uint16_t)));
      connect(worker, SIGNAL(putAxis5Value(uint16_t)),
                            SLOT(drawAxis5Value(uint16_t)));
      connect(worker, SIGNAL(putAxis6Value(uint16_t)),
                            SLOT(drawAxis6Value(uint16_t)));
      connect(worker, SIGNAL(putButtons1Value(uint64_t)),
                            SLOT(drawButtons1Value(uint64_t)));
      connect(worker, SIGNAL(putButtons2Value(uint64_t)),
                            SLOT(drawButtons2Value(uint64_t)));
      connect(worker, SIGNAL(putPOVSvalue(uint64_t)),
                            SLOT(drawPOVSvalue(uint64_t)));
      connect(worker, SIGNAL(putConnectedDeviceInfo(uint8_t)),
                            SLOT(showConnectDeviceInfo(uint8_t)));
      connect(worker, SIGNAL(putDisconnectedDeviceInfo()),
                            SLOT(hideConnectDeviceInfo()));


      thread->start();

      //hide all single encoders config for now
      QString name_template_Pix("label_SE%1");
      QString name_template_CBBA("comboBox_SEA%1");
      QString name_template_CBBB("comboBox_SEB%1");
      QString name_template_Pow("label_SE%1_CPin");
       for(int i =1; i < 15; i++)
      {
          QLabel *SEpic_Label = ui->tabWidget->findChild<QLabel *>(name_template_Pix.arg(i));
          QLabel *SEpow_Label = ui->tabWidget->findChild<QLabel *>(name_template_Pow.arg(i));
          QComboBox *SEcbba = ui->tabWidget->findChild<QComboBox *>(name_template_CBBA.arg(i));
          QComboBox *SEcbbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBB.arg(i));
          SEpic_Label->setVisible(false);
          SEpow_Label->setVisible(false);
          SEcbba->setVisible(false);
          SEcbbb->setVisible(false);
        }
       ui->label_ZeroSglEncoders->setVisible(false);



      QStringList list=(QStringList()<<"Not Used"<<"Analog No Smoothing"<<"Analog Low Smoothing"
                        <<"Analog Medium Smooth"<<"Analog High Smooting"<<"Analog to Button"
                        <<"Chd Rot Enc PINA"<<"Chd Rot Enc PINB"
                        <<"Chd Rot Enc 1/1"<<"Chd Rot Enc 1/2"<<"Chd Rot Enc 1/4"
                        <<"Sng Rot Enc PINA 1/1"<<"Sng Rot Enc PINB 1/1"
                        <<"Sng Rot Enc PINA 1/2"<<"Sng Rot Enc PINB 1/2"
                        <<"Sng Rot Enc PINA 1/4"<<"Sng Rot Enc PINB 1/4"
                        <<"Button Matrix ROW"<<"Button Matrix COLUMN"
                        <<"Single Button +3.3V"<<"Single Button GND"
                        <<"Rotary Switch Pole"
                        <<"Rotary Switch Wire");

      ui->comboBoxA11->setEnabled(false);
      ui->comboBoxA12->setEnabled(false);
//      ui->comboBoxC13->setEnabled(false);

      QString name_template("comboBoxA%1");
      for(int i = 0; i < 13; i++) {
         QComboBox *pinComboBox = ui->tabWidget->findChild<QComboBox *>(name_template.arg(i));
         pinComboBox->addItems(list);
            if (i > 6) {
                pinComboBox->setItemData(1, 0, Qt::UserRole - 1);
                pinComboBox->setItemData(2, 0, Qt::UserRole - 1);
                pinComboBox->setItemData(3, 0, Qt::UserRole - 1);
                pinComboBox->setItemData(4, 0, Qt::UserRole - 1);
            }
      }

      ui->comboBoxA15->addItems(list);
      ui->comboBoxA15->setItemData(1, 0, Qt::UserRole - 1);
      ui->comboBoxA15->setItemData(2, 0, Qt::UserRole - 1);
      ui->comboBoxA15->setItemData(3, 0, Qt::UserRole - 1);
      ui->comboBoxA15->setItemData(4, 0, Qt::UserRole - 1);

      name_template="comboBoxB%1";
      for(int i = 0; i < 16; i++) {
         if (i !=2 ) {
          QComboBox *pinComboBox = ui->tabWidget->findChild<QComboBox *>(name_template.arg(i));
          pinComboBox->addItems(list);
          pinComboBox->setItemData(1, 0, Qt::UserRole - 1);
          pinComboBox->setItemData(2, 0, Qt::UserRole - 1);
          pinComboBox->setItemData(3, 0, Qt::UserRole - 1);
          pinComboBox->setItemData(4, 0, Qt::UserRole - 1);
         }
      }

      name_template="comboBoxC%1";
      for(int i = 13; i < 16; i++) {
          QComboBox *pinComboBox = ui->tabWidget->findChild<QComboBox *>(name_template.arg(i));
          pinComboBox->addItems(list);
          pinComboBox->setItemData(1, 0, Qt::UserRole - 1);
          pinComboBox->setItemData(2, 0, Qt::UserRole - 1);
          pinComboBox->setItemData(3, 0, Qt::UserRole - 1);
          pinComboBox->setItemData(4, 0, Qt::UserRole - 1);
      }

      ui->comboBoxC13->setItemData(5, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(6, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(10, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(11, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(12, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(13, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(14, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(15, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(16, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(18, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(19, 0, Qt::UserRole - 1);
      ui->comboBoxC13->setItemData(21, 0, Qt::UserRole - 1);


      // fake assignment for making slots active;
      ui->spinBox_USB_exchange->setValue(2);
      ui->spinBox_USB_exchange->setValue(1);
      ui->horizontalSliderAxisComb->setValue(51);
      ui->horizontalSliderAxisComb->setValue(50);
      ui->checkBox_AxisComb->setChecked(true);
      ui->checkBox_AxisComb->setChecked(false);

      ui->comboBox_BoardType->addItem("BluePill Board");
      ui->comboBox_BoardType->addItem("BlackPill Board");
      ui->comboBox_BoardType->setCurrentIndex(0);
}

OSHStudio::~OSHStudio()
{
    delete ui;
}



void OSHStudio::show_USB_ident_uniq(QString ident) {
    QString const_desc="Your identifier for the device, it will appear in Windows as \"OSH PB Controller";
    if (ident.length()) {
        ui->label_60->setText(const_desc + "(" + ident + ")\"");
    } else ui->label_60->setText(const_desc + "\"");
}


void OSHStudio::show_USB_exch_rate(int interval) {
    QString const_desc="USB polling interval, ms. Current value means USB exchange frequency of ";
    interval=(int)1000/interval;
    ui->label_59->setText(const_desc + QString::number(interval) + " Hz");
}

QString OSHStudio::DrawTypeComboBox(pintype i) {
    switch (i) {
        case AnalogNoSmooth:    return "QComboBox { color: white; background-color: black; }";
        case AnalogLowSmooth:   return "QComboBox { color: white; background-color: black; }";
        case AnalogMedSmooth:   return "QComboBox { color: white; background-color: black; }";
        case AnalogHighSmooth:  return "QComboBox { color: white; background-color: black; }";
        case Analog2Button:  return "QComboBox { color: white; background-color: black; }";
        case Chain_Rotary_PINA: return "QComboBox { color: white; background-color: darkRed; }";
        case Chain_Rotary_PINB: return "QComboBox { color: white; background-color: darkRed; }";
        case Chain_Rotary_Enc_1:return "QComboBox { color: black; background-color: darkRed; }";
        case Chain_Rotary_Enc_2:return "QComboBox { color: black; background-color: darkRed; }";
        case Chain_Rotary_Enc_4:return "QComboBox { color: black; background-color: darkRed; }";
        case Single_Rotary_PINA_1:return "QComboBox { color: black; background-color: Red; }";
        case Single_Rotary_PINB_1:return "QComboBox { color: black; background-color: Red; }";
        case Single_Rotary_PINA_2:return "QComboBox { color: black; background-color: #FF3333; }";
        case Single_Rotary_PINB_2:return "QComboBox { color: black; background-color: #FF3333; }";
        case Single_Rotary_PINA_4:return "QComboBox { color: black; background-color: #FF6666; }";
        case Single_Rotary_PINB_4:return "QComboBox { color: black; background-color: #FF6666; }";
        case Button_ROW:        return "QComboBox { color: white; background-color: green; }";
        case Button_COLUMN:     return "QComboBox { color: white; background-color: darkGreen; }";
        case Button:            return "QComboBox { color: white; background-color: blue; }";
        case Button_GND:        return "QComboBox { color: white; background-color: blue; }";
        case RotSwPole:         return "QComboBox { color: white; background-color: magenta; }";
        case RotSwWire:         return "QComboBox { color: white; background-color: darkMagenta; }";
        case Not_Used:          return "QComboBox { color: black; background-color: light gray; }";
    }
    return ("Non valid pin type");
}


void OSHStudio::drawAxis1Value(uint16_t axis_value) {
    ui->widget_axis1->setAxisValue(axis_value);
}

void OSHStudio::drawAxis2Value(uint16_t axis_value) {
    ui->widget_axis2->setAxisValue(axis_value);
}

void OSHStudio::drawAxis3Value(uint16_t axis_value) {
    ui->widget_axis3->setAxisValue(axis_value);
}

void OSHStudio::drawAxis4Value(uint16_t axis_value) {
    ui->widget_axis4->setAxisValue(axis_value);
}

void OSHStudio::drawAxis5Value(uint16_t axis_value) {
    ui->widget_axis5->setAxisValue(axis_value);
}

void OSHStudio::drawAxis6Value(uint16_t axis_value) {
    ui->widget_axis6->setAxisValue(axis_value);
}

void OSHStudio::drawPOVSvalue(uint64_t POVS_value) {
    uint8_t value;
    QString name_template("label_POV%1");
    QPixmap povTop (":/Images/dpad_ct.png");
    QPixmap povRight (":/Images/dpad_cr.png");
    QPixmap povBottom (":/Images/dpad_cb.png");
    QPixmap povLeft (":/Images/dpad_cl.png");
    QPixmap povTopRight (":/Images/dpad_ctr.png");
    QPixmap povRightBottom (":/Images/dpad_crb.png");
    QPixmap povBottomLeft (":/Images/dpad_cbl.png");
    QPixmap povLeftTop (":/Images/dpad_clt.png");
    QPixmap povNull (":/Images/dpad.png");


    for (int i=0; i<4; i++) {
        QLabel *povLabel = ui->tabWidget->findChild<QLabel *>(name_template.arg(i+1));
        value=0xFF & (POVS_value >> (i*8));
        switch (value) {
            case 0: povLabel->setPixmap(povTop); break;
            case 1: povLabel->setPixmap(povTopRight); break;
            case 2: povLabel->setPixmap(povRight); break;
            case 3: povLabel->setPixmap(povRightBottom); break;
            case 4: povLabel->setPixmap(povBottom); break;
            case 5: povLabel->setPixmap(povBottomLeft); break;
            case 6: povLabel->setPixmap(povLeft); break;
            case 7: povLabel->setPixmap(povLeftTop); break;
            default: povLabel->setPixmap(povNull);
        }
    }
}

void OSHStudio::drawButtons2Value(uint64_t buttons_value) {
    QPixmap buttOn (":/Images/ON_2.png");
    QPixmap buttOff (":/Images/OFF.png");

    QString name_template("labelButt_%1");


    for(int i =32; i < 64; i++)
    {
        QLabel *buttLabel = ui->tabWidget->findChild<QLabel *>(name_template.arg(i));
        if (buttons_value & (0x1<<(i-32))) {
            buttLabel->setPixmap(buttOn);
        } else buttLabel->setPixmap(buttOff);

    }
}

void OSHStudio::drawButtons1Value(uint64_t buttons_value) {
    QPixmap buttOn (":/Images/ON_2.png");
    QPixmap buttOff (":/Images/OFF.png");

    QString name_template("labelButt_%1");


    for(int i = 0; i < 32; i++)
    {
        QLabel *buttLabel = ui->tabWidget->findChild<QLabel *>(name_template.arg(i));
        if (buttons_value & (0x1<<i)) {
            buttLabel->setPixmap(buttOn);
        } else buttLabel->setPixmap(buttOff);
    }
}

void OSHStudio::checkBoxPOV1Changed(int state) {
    bool chk;

    if (state) chk=true; else chk=false;

    ui->label_POV1->setEnabled(chk);
    ui->labelButt_0->setEnabled(!chk);
    ui->labelButt_1->setEnabled(!chk);
    ui->labelButt_2->setEnabled(!chk);
    ui->labelButt_3->setEnabled(!chk);
}

void OSHStudio::checkBoxPOV2Changed(int state) {
    bool chk;

    if (state) chk=true; else chk=false;

    ui->label_POV2->setEnabled(chk);
    ui->labelButt_4->setEnabled(!chk);
    ui->labelButt_5->setEnabled(!chk);
    ui->labelButt_6->setEnabled(!chk);
    ui->labelButt_7->setEnabled(!chk);
}

void OSHStudio::checkBoxPOV3Changed(int state) {
    bool chk;

    if (state) chk=true; else chk=false;

    ui->label_POV3->setEnabled(chk);
    ui->labelButt_8->setEnabled(!chk);
    ui->labelButt_9->setEnabled(!chk);
    ui->labelButt_10->setEnabled(!chk);
    ui->labelButt_11->setEnabled(!chk);
}

void OSHStudio::checkBoxPOV4Changed(int state) {
    bool chk;

    if (state) chk=true; else chk=false;

    ui->label_POV4->setEnabled(chk);
    ui->labelButt_12->setEnabled(!chk);
    ui->labelButt_13->setEnabled(!chk);
    ui->labelButt_14->setEnabled(!chk);
    ui->labelButt_15->setEnabled(!chk);
}




void OSHStudio::showConnectDeviceInfo(uint8_t firmware_release) {
    QString firmware_correctness="";

    ui->label_DevDescImg->setVisible(true);
    ui->label_DevDesc->setVisible(true);
    ui->getConfig_button->setEnabled(true);
    ui->saveConfig_Button->setEnabled(true);
    if (!firmware_release) ui->label_Firmware_Vers->setText("") ;
            else ui->label_Firmware_Vers->setText("0."+QString::number(firmware_release));
    if (firmware_release == OSHSTUDIOVERSION) {
        firmware_correctness="color : green";
    } else {
        firmware_correctness="color : red";
        }
        ui->label_Firmware_Vers->setStyleSheet(firmware_correctness);
        ui->label_58->setStyleSheet(firmware_correctness);
        ui->label_34->setStyleSheet(firmware_correctness);
        ui->label_Stud_version->setStyleSheet(firmware_correctness);
}

void OSHStudio::hideConnectDeviceInfo() {
    ui->label_DevDescImg->setVisible(false);
    ui->label_DevDesc->setVisible(false);
    ui->getConfig_button->setEnabled(false);
    ui->saveConfig_Button->setEnabled(false);
    ui->label_Firmware_Vers->setText("") ;
    ui->label_Firmware_Vers->setStyleSheet("color : black");
    ui->label_58->setStyleSheet("color : black");
    ui->label_34->setStyleSheet("color : black");
    ui->label_Stud_version->setStyleSheet("color : black");
}

QString OSHStudio::convertIntToString(int i) {
    return QString::number(i);
}

void OSHStudio::showPercentAxisComb(int i) {
    ui->label_AxisComb1->setText(QString::number(i)+"%");
    ui->label_AxisComb2->setText(QString::number(100-i)+"%");
}

void OSHStudio::showAxisCombSlider(bool state) {
    ui->horizontalSliderAxisComb->setEnabled(state);
    ui->label_4->setVisible(state);
    ui->label_AxisComb1->setVisible(state);
    ui->label_5->setVisible(state);
    ui->label_6->setVisible(state);
    ui->label_AxisComb2->setVisible(state);
    ui->label_7->setVisible(state);
    ui->label_AxisCombPin1->setVisible(state);
    ui->label_AxisCombPin2->setVisible(state);
}

void OSHStudio::showAxisCombSection(bool checked) {
        ui->comboBox_AxisCombBegin->setEnabled(checked);
        ui->comboBox_AxisCombEnd->setEnabled(checked);
        ui->widget_axisComb1->setPinsEnabled(checked);
        ui->widget_axisComb2->setPinsEnabled(checked);
        ui->widget_axisComb1->setEnabled(checked);
        ui->widget_axisComb2->setEnabled(checked);

        ui->radioButtonCoopwoork->setEnabled(checked);
        ui->radioButtonEachonhisown->setEnabled(checked);

        if (checked) {
            if (ui->radioButtonCoopwoork->isChecked()) showAxisCombSlider(true);
                else showAxisCombSlider(false);
        } else {
            showAxisCombSlider(false);
        }
}

void OSHStudio::showPin1AxisComb(QString pinname){
    ui->label_AxisCombPin1->setText(pinname);
    AxisComb_StartPin=convertPinnameToIndex(pinname);
}

void OSHStudio::showPin2AxisComb(QString pinname){
    ui->label_AxisCombPin2->setText(pinname);
    AxisComb_EndPin=convertPinnameToIndex(pinname);
}

int OSHStudio::convertStringToInt(QString str) {
    return str.toInt();
}

/*void OSHStudio::lineEditAxis1Min_Slot(int i) {
    ui->lineEditAxis1Min->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis1Min_Slot(QString str) {
    ui->horiSliderAxis1Min->setValue(str.toInt());
}

void OSHStudio::lineEditAxis1Max_Slot(int i) {
    ui->lineEditAxis1Max->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis1Max_Slot(QString str) {
    ui->horiSliderAxis1Max->setValue(str.toInt());
}

void OSHStudio::lineEditAxis2Min_Slot(int i) {
    ui->lineEditAxis2Min->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis2Min_Slot(QString str) {
    ui->horiSliderAxis2Min->setValue(str.toInt());
}

void OSHStudio::lineEditAxis2Max_Slot(int i) {
    ui->lineEditAxis2Max->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis2Max_Slot(QString str) {
    ui->horiSliderAxis2Max->setValue(str.toInt());
}

void OSHStudio::lineEditAxis3Min_Slot(int i) {
    ui->lineEditAxis3Min->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis3Min_Slot(QString str) {
    ui->horiSliderAxis3Min->setValue(str.toInt());
}

void OSHStudio::lineEditAxis3Max_Slot(int i) {
    ui->lineEditAxis3Max->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis3Max_Slot(QString str) {
    ui->horiSliderAxis3Max->setValue(str.toInt());
}

void OSHStudio::lineEditAxis4Min_Slot(int i) {
    ui->lineEditAxis4Min->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis4Min_Slot(QString str) {
    ui->horiSliderAxis4Min->setValue(str.toInt());
}

void OSHStudio::lineEditAxis4Max_Slot(int i) {
    ui->lineEditAxis4Max->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis4Max_Slot(QString str) {
    ui->horiSliderAxis4Max->setValue(str.toInt());
}

void OSHStudio::lineEditAxis5Min_Slot(int i) {
    ui->lineEditAxis5Min->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis5Min_Slot(QString str) {
    ui->horiSliderAxis5Min->setValue(str.toInt());
}

void OSHStudio::lineEditAxis5Max_Slot(int i) {
    ui->lineEditAxis5Max->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis5Max_Slot(QString str) {
    ui->horiSliderAxis5Max->setValue(str.toInt());
}

void OSHStudio::lineEditAxis6Min_Slot(int i) {
    ui->lineEditAxis6Min->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis6Min_Slot(QString str) {
    ui->horiSliderAxis6Min->setValue(str.toInt());
}

void OSHStudio::lineEditAxis6Max_Slot(int i) {
    ui->lineEditAxis6Max->setText(QString::number(i));
}

void OSHStudio::horiSliderAxis6Max_Slot(QString str) {
    ui->horiSliderAxis6Max->setValue(str.toInt());
}*/
/*
void OSHStudio::lineEditAxisCombPin1Min_Slot(int i) {
    ui->lineEditAxisCombPin1Min->setText(QString::number(i));
}

void OSHStudio::horiSliderAxisCombPin1Min_Slot(QString str) {
    ui->horiSliderAxisCombPin1Min->setValue(str.toInt());
}

void OSHStudio::lineEditAxisCombPin1Max_Slot(int i) {
    ui->lineEditAxisCombPin1Max->setText(QString::number(i));
}

void OSHStudio::horiSliderAxisCombPin1Max_Slot(QString str) {
    ui->horiSliderAxisCombPin1Max->setValue(str.toInt());
}

void OSHStudio::lineEditAxisCombPin2Min_Slot(int i) {
    ui->lineEditAxisCombPin2Min->setText(QString::number(i));
}

void OSHStudio::horiSliderAxisCombPin2Min_Slot(QString str) {
    ui->horiSliderAxisCombPin2Min->setValue(str.toInt());
}

void OSHStudio::lineEditAxisCombPin2Max_Slot(int i) {
    ui->lineEditAxisCombPin2Max->setText(QString::number(i));
}

void OSHStudio::horiSliderAxisCombPin2Max_Slot(QString str) {
    ui->horiSliderAxisCombPin2Max->setValue(str.toInt());
}
*/

void OSHStudio::comboBoxPaintA0() {
    ui->comboBoxA0->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA0->currentIndex()));
    ui->comboBoxA0->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA1() {
    ui->comboBoxA1->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA1->currentIndex()));
    ui->comboBoxA1->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA2() {
    ui->comboBoxA2->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA2->currentIndex()));
    ui->comboBoxA2->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA3() {
    ui->comboBoxA3->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA3->currentIndex()));
    ui->comboBoxA3->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA4() {
    ui->comboBoxA4->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA4->currentIndex()));
    ui->comboBoxA4->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA5() {
    ui->comboBoxA5->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA5->currentIndex()));
    ui->comboBoxA5->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA6() {
    ui->comboBoxA6->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA6->currentIndex()));
    ui->comboBoxA6->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA7() {
    ui->comboBoxA7->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA7->currentIndex()));
    ui->comboBoxA7->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA8() {
    ui->comboBoxA8->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA8->currentIndex()));
    ui->comboBoxA8->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA9() {
    ui->comboBoxA9->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA9->currentIndex()));
    ui->comboBoxA9->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA10() {
    ui->comboBoxA10->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA10->currentIndex()));
    ui->comboBoxA10->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA11() {
    ui->comboBoxA11->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA11->currentIndex()));
    ui->comboBoxA11->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA12() {
    ui->comboBoxA12->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA12->currentIndex()));
    ui->comboBoxA12->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintA15() {
    ui->comboBoxA15->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA15->currentIndex()));
    ui->comboBoxA15->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB0() {
    ui->comboBoxB0->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB0->currentIndex()));
    ui->comboBoxB0->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB1() {
    ui->comboBoxB1->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB1->currentIndex()));
    ui->comboBoxB1->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB3() {
    ui->comboBoxB3->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB3->currentIndex()));
    ui->comboBoxB3->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB4() {
    ui->comboBoxB4->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB4->currentIndex()));
    ui->comboBoxB4->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB5() {
    ui->comboBoxB5->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB5->currentIndex()));
    ui->comboBoxB5->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB6() {
    ui->comboBoxB6->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB6->currentIndex()));
    ui->comboBoxB6->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB7() {
    ui->comboBoxB7->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB7->currentIndex()));
    ui->comboBoxB7->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB8() {
    ui->comboBoxB8->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB8->currentIndex()));
    ui->comboBoxB8->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB9() {
    ui->comboBoxB9->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB9->currentIndex()));
    ui->comboBoxB9->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB10() {
    ui->comboBoxB10->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB10->currentIndex()));
    ui->comboBoxB10->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB11() {
    ui->comboBoxB11->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB11->currentIndex()));
    ui->comboBoxB11->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB12() {
    ui->comboBoxB12->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB12->currentIndex()));
    ui->comboBoxB12->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB13() {
    ui->comboBoxB13->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB13->currentIndex()));
    ui->comboBoxB13->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB14() {
    ui->comboBoxB14->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB14->currentIndex()));
    ui->comboBoxB14->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintB15() {
    ui->comboBoxB15->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB15->currentIndex()));
    ui->comboBoxB15->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintC13() {
    ui->comboBoxC13->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxC13->currentIndex()));
    ui->comboBoxC13->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintC14() {
    ui->comboBoxC14->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxC14->currentIndex()));
    ui->comboBoxC14->clearFocus();
    drawHelp();
}

void OSHStudio::comboBoxPaintC15() {
    ui->comboBoxC15->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxC15->currentIndex()));
    ui->comboBoxC15->clearFocus();
    drawHelp();
}




void OSHStudio::gatherAllConf()
{
    NumberAnalogInputs=0;
    Chain_PinA=0;
    Chain_PinB=0;
    Chain_Rotaries_1=0;
    Chain_Rotaries_2=0;
    Chain_Rotaries_4=0;
    Single_Rotaries_PINA_1=0;
    Single_Rotaries_PINB_1=0;
    Single_Rotaries_PINA_2=0;
    Single_Rotaries_PINB_2=0;
    Single_Rotaries_PINA_4=0;
    Single_Rotaries_PINB_4=0;
    ButtonsRows=0;
    ButtonsColumns=0;
    Buttons=0;
    RotSwitchPoles=0;
    RotSwitchWires=0;
    PINAlist.clear();
    PINBlist.clear();
    Total_Single_encoders=0;
    QStringList AxisComb1;


    uint8_t pin_number=0;
    uint8_t Single_Rotaries_PINA=0;
    uint8_t Single_Rotaries_PINB=0;

    pintype curr_pin_type;

    QString base_name_template("comboBox");
    for (char port='A'; port < 'D'; port++) {
        QString port_name_template=base_name_template + port;
        port_name_template+="%1";
        for(uint8_t i =0; i < 16; i++) {
            QComboBox *comboBox_ptr = ui->tabWidget->findChild<QComboBox *>(port_name_template.arg(i));
            if (comboBox_ptr) {
                curr_pin_type=(pintype)(comboBox_ptr->currentIndex());
                switch (curr_pin_type) {
                    case (Not_Used): break;
                    case (AnalogNoSmooth):
                    case (AnalogLowSmooth):
                    case (AnalogMedSmooth):
                    case (AnalogHighSmooth):        AxisComb1+=QChar::fromLatin1(port)+QString::number(i);
                                                    NumberAnalogInputs ++; break;
                    case (Chain_Rotary_PINA):       Chain_PinA++; break;
                    case (Chain_Rotary_PINB):       Chain_PinB++; break;
                    case (Chain_Rotary_Enc_1):      Chain_Rotaries_1++; break;
                    case (Chain_Rotary_Enc_2):      Chain_Rotaries_2++; break;
                    case (Chain_Rotary_Enc_4):      Chain_Rotaries_4++; break;
                    case (Single_Rotary_PINA_1):    single_encoders_store[Single_Rotaries_PINA].pinA=pin_number;
                                                    single_encoders_store[Single_Rotaries_PINA].pinA_type=Single_Rotary_PINA_1;
                                                    Single_Rotaries_PINA++;
                                                    Single_Rotaries_PINA_1++;
                                                    break;
                    case (Single_Rotary_PINB_1):    Single_Rotaries_PINB_1++;
                                                    single_encoders_store[Single_Rotaries_PINB].pinB=pin_number;
                                                    single_encoders_store[Single_Rotaries_PINB].pinB_type=Single_Rotary_PINA_1;
                                                    Single_Rotaries_PINB++;
                                                    break;
                    case (Single_Rotary_PINA_2):    Single_Rotaries_PINA_2++;
                                                    single_encoders_store[Single_Rotaries_PINA].pinA=pin_number;
                                                    single_encoders_store[Single_Rotaries_PINA].pinA_type=Single_Rotary_PINA_2;
                                                    Single_Rotaries_PINA++;
                                                    break;
                    case (Single_Rotary_PINB_2):    Single_Rotaries_PINB_2++;
                                                    single_encoders_store[Single_Rotaries_PINB].pinB=pin_number;
                                                    single_encoders_store[Single_Rotaries_PINB].pinB_type=Single_Rotary_PINA_2;
                                                    Single_Rotaries_PINB++;
                                                    break;
                    case (Single_Rotary_PINA_4):    Single_Rotaries_PINA_4++;
                                                    single_encoders_store[Single_Rotaries_PINA].pinA=pin_number;
                                                    single_encoders_store[Single_Rotaries_PINA].pinA_type=Single_Rotary_PINA_4;
                                                    Single_Rotaries_PINA++;
                                                    break;
                    case (Single_Rotary_PINB_4):    Single_Rotaries_PINB_4++;
                                                    single_encoders_store[Single_Rotaries_PINB].pinB=pin_number;
                                                    single_encoders_store[Single_Rotaries_PINB].pinB_type=Single_Rotary_PINA_4;
                                                    Single_Rotaries_PINB++;
                                                    break;
                    case (Button_ROW):              ButtonsRows++; break;
                    case (Button_COLUMN):           ButtonsColumns++; break;
                    case (Button):
                    case (Button_GND):              Buttons++; break;
                    case (RotSwPole):               RotSwitchPoles++; break;
                    case (RotSwWire):               RotSwitchWires++; break;
                    default:                        break;
                }
                pin_number++;
            }
        }
    }

    if (Single_Rotaries_PINA_1>Single_Rotaries_PINB_1) {
        Total_Single_encoders+=Single_Rotaries_PINB_1 ;
    }
        else {
        Total_Single_encoders+=Single_Rotaries_PINA_1 ;
    }

    if (Single_Rotaries_PINA_2>Single_Rotaries_PINB_2) {
        Total_Single_encoders+=Single_Rotaries_PINB_2 ;
    }
        else {
        Total_Single_encoders+=Single_Rotaries_PINA_2 ;
    }

    if (Single_Rotaries_PINA_4>Single_Rotaries_PINB_4) {
        Total_Single_encoders+=Single_Rotaries_PINB_4 ;
    }
        else {
        Total_Single_encoders+=Single_Rotaries_PINA_4 ;
    }

    ui->comboBox_AxisCombBegin->clear();
    ui->comboBox_AxisCombEnd->clear();
    ui->comboBox_AxisCombBegin->addItems(AxisComb1);
    ui->comboBox_AxisCombEnd->addItems(AxisComb1);
    ui->comboBox_AxisCombBegin->setCurrentIndex((ui->comboBox_AxisCombBegin->count())-2);
    ui->comboBox_AxisCombEnd->setCurrentIndex((ui->comboBox_AxisCombEnd->count())-1);
    showSingleEncodersTab();
}

void OSHStudio::showSingleEncodersTab(void) {
    QString name_template_Pix("label_SE%1");
    QString name_template_CBBA("comboBox_SEA%1");
    QString name_template_CBBB("comboBox_SEB%1");
    QString name_template_Pow("label_SE%1_CPin");
    PINAlist.clear();
    PINBlist.clear();

    for(uint8_t i =1; i < 15; i++)
    {
        QLabel *SEpic_Label = ui->tabWidget->findChild<QLabel *>(name_template_Pix.arg(i));
        QLabel *SEpow_Label = ui->tabWidget->findChild<QLabel *>(name_template_Pow.arg(i));
        QComboBox *SEcbba = ui->tabWidget->findChild<QComboBox *>(name_template_CBBA.arg(i));
        QComboBox *SEcbbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBB.arg(i));
        SEpic_Label->setVisible(false);
        SEpow_Label->setVisible(false);
        SEcbba->setVisible(false);
        SEcbbb->setVisible(false);
        SEcbba->clear();
        SEcbbb->clear();
      }

    if (!Total_Single_encoders) {
        ui->label_ZeroSglEncoders->setVisible(true);
    }
        else {
        ui->label_ZeroSglEncoders->setVisible(false);
        for (uint8_t k=0; k<Total_Single_encoders; k++){
          if (single_encoders_store[k].pinA_type!=single_encoders_store[k].pinB_type) {
            for (uint8_t j=k; j<Total_Single_encoders; j++) {
              if (single_encoders_store[k].pinA_type==single_encoders_store[j].pinB_type) {
                uint8_t tmp_pin=single_encoders_store[k].pinB;
                uint8_t tmp_pintype=single_encoders_store[k].pinB_type;
                single_encoders_store[k].pinB=single_encoders_store[j].pinB;
                single_encoders_store[k].pinB_type=single_encoders_store[j].pinB_type;
                single_encoders_store[j].pinB=tmp_pin;
                single_encoders_store[j].pinB_type=tmp_pintype;
                j=Total_Single_encoders;
                }
            }
          }
        }
        for (uint8_t k=0; k<Total_Single_encoders; k++){
            QString tmp_str;
            switch (single_encoders_store[k].pinA_type) {
                case (Single_Rotary_PINA_1): tmp_str="1/1 step - "; break;
                case (Single_Rotary_PINA_2): tmp_str="1/2 step - "; break;
                case (Single_Rotary_PINA_4): tmp_str="1/4 step - "; break;
                default:                     tmp_str=" ";
            };
         PINAlist+=(tmp_str+pin_names[single_encoders_store[k].pinA]);
         PINBlist+=(tmp_str+pin_names[single_encoders_store[k].pinB]);
        }

        for(uint8_t i =1; i <= Total_Single_encoders; i++)
        {
            QLabel *SEpic_Label = ui->tabWidget->findChild<QLabel *>(name_template_Pix.arg(i));
            QLabel *SEpow_Label = ui->tabWidget->findChild<QLabel *>(name_template_Pow.arg(i));
            QComboBox *SEcbba = ui->tabWidget->findChild<QComboBox *>(name_template_CBBA.arg(i));
            QComboBox *SEcbbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBB.arg(i));
            SEpic_Label->setVisible(true);
            SEpow_Label->setVisible(true);
            SEcbba->setVisible(true);
            SEcbbb->setVisible(true);
            SEcbba->blockSignals(true);
            SEcbbb->blockSignals(true);
            SEcbba->addItems(PINAlist);
            SEcbba->setCurrentIndex(i-1);
            SEcbbb->addItems(PINBlist);
            SEcbbb->setCurrentIndex(i-1);
            SEcbba->setStyleSheet("QComboBox { color: black; background-color: light gray; }");
            SEcbbb->setStyleSheet("QComboBox { color: black; background-color: light gray; }");
            SEcbba->blockSignals(false);
            SEcbbb->blockSignals(false);
          }

    }
}

void OSHStudio::comboBoxSEManualConfig() {
    QString name_template_CBBA("comboBox_SEA%1");
    QString name_template_CBBB("comboBox_SEB%1");
//    QString debugstr="";

    for(uint8_t i =1; i <= Total_Single_encoders; i++) {
        QComboBox *SEcbba = ui->tabWidget->findChild<QComboBox *>(name_template_CBBA.arg(i));
        QComboBox *SEcbbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBB.arg(i));
        SEcbba->setStyleSheet("QComboBox { color: black; background-color: light gray; }");
        SEcbbb->setStyleSheet("QComboBox { color: black; background-color: light gray; }");
        SEcbba->clearFocus();
        SEcbbb->clearFocus();
        QString cbb_value=SEcbba->currentText();
        QChar se_type=cbb_value.at(2);
        single_encoders_store[i-1].pinA_type=convertCharToSEType(se_type);
        QString pin_name=cbb_value.section(' ',3,3);
        single_encoders_store[i-1].pinA=convertPinnameToIndex(pin_name);
        cbb_value=SEcbbb->currentText();
        se_type=cbb_value.at(2);
        single_encoders_store[i-1].pinB_type=convertCharToSEType(se_type);
        pin_name=cbb_value.section(' ',3,3);
        single_encoders_store[i-1].pinB=convertPinnameToIndex(pin_name);
//        debugstr+= QString::number(single_encoders_store[i-1].pinA_type) + " " +
//                           QString::number(single_encoders_store[i-1].pinA) + " ; " +
//                           QString::number(single_encoders_store[i-1].pinB_type) + " " +
//                           QString::number(single_encoders_store[i-1].pinB) + "\n ";
    }
//    ui->label_2->setText(debugstr);
    drawHelpSE();
}

void OSHStudio::drawHelpSE() {
    QString name_template_CBBA("comboBox_SEA%1");
    QString name_template_CBBB("comboBox_SEB%1");
    QComboBox *SEcbb;

    for(uint8_t i =1; i < Total_Single_encoders; i++) {
        if (single_encoders_store[i-1].pinA_type != single_encoders_store[i-1].pinB_type) {
            SEcbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBA.arg(i));
            SEcbb->setStyleSheet("QComboBox { color: black; background-color: magenta; }");
            SEcbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBB.arg(i));
            SEcbb->setStyleSheet("QComboBox { color: black; background-color: magenta; }");
            SEcbb->clearFocus();
        }
        for(uint8_t j =i+1; j <= Total_Single_encoders; j++) {
            if (single_encoders_store[i-1].pinA == single_encoders_store[j-1].pinA) {
                SEcbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBA.arg(i));
                SEcbb->setStyleSheet("QComboBox { color: black; background-color: red; }");
                SEcbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBA.arg(j));
                SEcbb->setStyleSheet("QComboBox { color: black; background-color: red; }");
                SEcbb->clearFocus();
            }
            if (single_encoders_store[i-1].pinB == single_encoders_store[j-1].pinB) {
                SEcbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBB.arg(i));
                SEcbb->setStyleSheet("QComboBox { color: black; background-color: red; }");
                SEcbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBB.arg(j));
                SEcbb->setStyleSheet("QComboBox { color: black; background-color: red; }");
                SEcbb->clearFocus();
            }
        }

    }
    //and for the last one
    if (single_encoders_store[Total_Single_encoders-1].pinA_type != single_encoders_store[Total_Single_encoders-1].pinB_type) {
        SEcbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBA.arg(Total_Single_encoders));
        SEcbb->setStyleSheet("QComboBox { color: black; background-color: magenta; }");
        SEcbb = ui->tabWidget->findChild<QComboBox *>(name_template_CBBB.arg(Total_Single_encoders));
        SEcbb->setStyleSheet("QComboBox { color: black; background-color: magenta; }");
        SEcbb->clearFocus();
    }
}


uint8_t OSHStudio::convertCharToSEType (QChar ch) {
    switch (ch.toLatin1()) {
        case ('1'):   return (Single_Rotary_PINA_1);
        case ('2'):   return (Single_Rotary_PINA_2);
        case ('4'):   return (Single_Rotary_PINA_4);
        default :     return 0;
    }
}

uint8_t OSHStudio::convertPinnameToIndex (QString pname) {
    for(uint8_t i =0; i < PINS; i++) {
        if (pin_names[i]==pname) return i;
    }
    return 255;
}

void OSHStudio::drawHelp()
{
    QString HelpText;

    gatherAllConf();

    if (NumberAnalogInputs > 0) {
        HelpText = "<br />" + QString::number(NumberAnalogInputs) + " analog inputs <br />";
        if (NumberAnalogInputs > 6)
            HelpText = HelpText + "<font color='red'>Sorry, no more than 6 analog inputs</font><br />";
    }

    if ((Chain_Rotaries_1 > 0) ||(Chain_Rotaries_2 > 0) || (Chain_Rotaries_4 > 0)) {
        HelpText = HelpText + "<br />" +
                QString::number(Chain_Rotaries_1 + Chain_Rotaries_2 + Chain_Rotaries_4) + " chained rotary encoders <br />";
        if ((Chain_PinA != 1) || (Chain_PinB != 1))
            HelpText = HelpText + "<font color='red'>You have to properly configure PINA and PINB pins of chained encoders</font><br /><br />";
    }

    if (Total_Single_encoders > 0) {
        HelpText = HelpText + "<br />" + QString::number(Total_Single_encoders) + " single rotary encoders <br />";
        if ((Single_Rotaries_PINA_1 != Single_Rotaries_PINB_1) || (Single_Rotaries_PINA_2 != Single_Rotaries_PINB_2) ||
                (Single_Rotaries_PINA_4 != Single_Rotaries_PINB_4))
            HelpText = HelpText + "<font color='red'>You have to properly configure PINA and PINB pins of single encoders</font><br /><br />";
    }

    if ((ButtonsRows>0) && (ButtonsColumns>0))
        HelpText = HelpText + "<br />" + QString::number(ButtonsRows * ButtonsColumns) + " buttons in matrix <br />";

    if ((ButtonsRows>0) && (!ButtonsColumns))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 column to matrix</font><br />";

    if ((!ButtonsRows) && (ButtonsColumns>0))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 row to matrix</font><br />";

    if (Buttons>0)
        HelpText = HelpText + "<br />" + QString::number(Buttons) + " single buttons <br />";


    if ((RotSwitchWires>0) && (RotSwitchPoles>0))
        HelpText = HelpText + "<br />" + QString::number(RotSwitchWires*RotSwitchPoles) + " buttons in Rotary Switch Config <br />";

    if ((RotSwitchWires>0) && (RotSwitchPoles<1))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 Pole to Rotary Switch Config</font><br />";

    if ((RotSwitchWires<1) && (RotSwitchPoles>0))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 Wire to Rotary Switch Config</font><br />";


    ui->labelHelp->setText(HelpText);
}

