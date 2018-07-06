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

      //  cur_dev = hid_enumerate(0x1209, 0x3100);
        emit putConnectedDeviceInfo(14);
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


       QString name_template("widget_PB%1");
       for(int i = 0; i < 32; i++) {
          oshpincombobox *pinComboBox = ui->tabWidget->findChild<oshpincombobox *>(name_template.arg(i));
          pinComboBox->set_pin_number(i);
          connect(pinComboBox, SIGNAL(item_changed()),  SLOT(drawHelp()));
       }
       ui->widget_PB11->setEnabled(false);
       ui->widget_PB12->setEnabled(false);


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
    QString name_template("widget_PB%1");
    for(int i = 0; i < 32; i++) {
        oshpincombobox *comboBox_ptr = ui->tabWidget->findChild<oshpincombobox *>(name_template.arg(i));
        if (comboBox_ptr) {
            curr_pin_type=(pintype)(comboBox_ptr->get_current_index());
            switch (curr_pin_type) {
                case (Not_Used): break;
                case (AnalogNoSmooth):
                case (AnalogLowSmooth):
                case (AnalogMedSmooth):
                case (AnalogHighSmooth):        AxisComb1+='A'+QString::number(i);
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

        if (Single_Rotaries_PINA_1>Single_Rotaries_PINB_1) {
        Total_Single_encoders+=Single_Rotaries_PINA_1 ;
    }
        else {
        Total_Single_encoders+=Single_Rotaries_PINB_1 ;
    }

    if (Single_Rotaries_PINA_2>Single_Rotaries_PINB_2) {
        Total_Single_encoders+=Single_Rotaries_PINA_2 ;
    }
        else {
        Total_Single_encoders+=Single_Rotaries_PINB_2 ;
    }

    if (Single_Rotaries_PINA_4>Single_Rotaries_PINB_4) {
        Total_Single_encoders+=Single_Rotaries_PINA_4 ;
    }
        else {
        Total_Single_encoders+=Single_Rotaries_PINB_4 ;
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

