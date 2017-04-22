#include "oshstudio.h"
#include "ui_oshstudio.h"
#include<QMessageBox>
#include<QTextEdit>


hid_device *handle_read, *handle_write;

uint8_t NumberAnalogInputs,
        PinA,
        PinB,
        Rotaries,
        ButtonsRows,
        ButtonsColumns,
        Buttons,
        RotSwitchPoles,
        RotSwitchWires;

void Worker::processData(void) {
    uint8_t buf[BUFFSIZE]={0};
//    uint8_t bufrep2[2]={3,1};
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
        emit putConnectedDeviceInfo();
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
      connect(ui->getConfig_button, SIGNAL(clicked()), SLOT(getConfig_Slot()));
      connect(ui->saveConfig_Button, SIGNAL(clicked()), SLOT(writeConfig_Slot()));

      connect(ui->comboBoxA0, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA1, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA2, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA3, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA4, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA5, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA6, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA7, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA8, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA9, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA10, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA11, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA12, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxA15, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB0, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB1, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB3, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB4, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB5, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB6, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB7, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB8, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB9, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB10, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB11, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB12, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB13, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB14, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxB15, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxC13, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxC14, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));
      connect(ui->comboBoxC15, SIGNAL(currentIndexChanged(int)),  SLOT(comboBoxPaint()));


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

      connect(ui->loadFile_Button, SIGNAL(clicked(bool)), SLOT(loadFromFile()));
      connect(ui->saveFile_Button, SIGNAL(clicked(bool)), SLOT(saveToFile()));

      connect(ui->checkBox_POV1, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV1Changed(int)));
      connect(ui->checkBox_POV2, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV2Changed(int)));
      connect(ui->checkBox_POV3, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV3Changed(int)));
      connect(ui->checkBox_POV4, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV4Changed(int)));


      qRegisterMetaType<uint16_t>("uint16_t");
      qRegisterMetaType<uint64_t>("uint64_t");

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
      connect(worker, SIGNAL(putConnectedDeviceInfo()),
                            SLOT(showConnectDeviceInfo()));
      connect(worker, SIGNAL(putDisconnectedDeviceInfo()),
                            SLOT(hideConnectDeviceInfo()));


      thread->start();



      QStringList list=(QStringList()<<"Not Used"<<"Analog No Smoothing"<<"Analog Low Smoothing"
                        <<"Analog Medium Smooth"<<"Analog High Smooting"<<"Rotary Encoder PINA"
                        <<"Rotary Encoder PINB"<<"Rotary Encoder"<<"Button Matrix ROW"
                        <<"Button Matrix COLUMN"<<"Single Button"<<"Rotary Switch Pole"
                        <<"Rotary Switch Wire");

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
}

OSHStudio::~OSHStudio()
{
    delete ui;
}


void OSHStudio::writeConfig_Slot()
{
    uint8_t buf[BUFFSIZE]={2,0};
    uint8_t res=0;

    //gather pins config
    buf[1]=ui->comboBoxA0->currentIndex();
    buf[2]=ui->comboBoxA1->currentIndex();
    buf[3]=ui->comboBoxA2->currentIndex();
    buf[4]=ui->comboBoxA3->currentIndex();
    buf[5]=ui->comboBoxA4->currentIndex();
    buf[6]=ui->comboBoxA5->currentIndex();
    buf[7]=ui->comboBoxA6->currentIndex();
    buf[8]=ui->comboBoxA7->currentIndex();
    buf[9]=ui->comboBoxA8->currentIndex();
    buf[10]=ui->comboBoxA9->currentIndex();
    buf[11]=ui->comboBoxA10->currentIndex();
    buf[12]=ui->comboBoxA11->currentIndex();
    buf[13]=ui->comboBoxA12->currentIndex();
    buf[14]=ui->comboBoxA15->currentIndex();
    buf[15]=ui->comboBoxB0->currentIndex();
    buf[16]=ui->comboBoxB1->currentIndex();
    buf[17]=ui->comboBoxB3->currentIndex();
    buf[18]=ui->comboBoxB4->currentIndex();
    buf[19]=ui->comboBoxB5->currentIndex();
    buf[20]=ui->comboBoxB6->currentIndex();
    buf[21]=ui->comboBoxB7->currentIndex();
    buf[22]=ui->comboBoxB8->currentIndex();
    buf[23]=ui->comboBoxB9->currentIndex();
    buf[24]=ui->comboBoxB10->currentIndex();
    buf[25]=ui->comboBoxB11->currentIndex();
    buf[26]=ui->comboBoxB12->currentIndex();
    buf[27]=ui->comboBoxB13->currentIndex();
    buf[28]=ui->comboBoxB14->currentIndex();
    buf[29]=ui->comboBoxB15->currentIndex();
    buf[30]=ui->comboBoxC13->currentIndex();
    buf[31]=ui->comboBoxC14->currentIndex();
    buf[32]=ui->comboBoxC15->currentIndex();


    //gather axises config
    buf[33]=LOBYTE(ui->horiSliderAxis1Min->value());
    buf[34]=HIBYTE(ui->horiSliderAxis1Min->value());
    buf[35]=LOBYTE(ui->horiSliderAxis1Max->value());
    buf[36]=HIBYTE(ui->horiSliderAxis1Max->value());
    buf[37]=0; //Reserved
    buf[38]=LOBYTE(ui->horiSliderAxis2Min->value());
    buf[39]=HIBYTE(ui->horiSliderAxis2Min->value());
    buf[40]=LOBYTE(ui->horiSliderAxis2Max->value());
    buf[41]=HIBYTE(ui->horiSliderAxis2Max->value());
    buf[42]=0; //Reserved
    buf[43]=LOBYTE(ui->horiSliderAxis3Min->value());
    buf[44]=HIBYTE(ui->horiSliderAxis3Min->value());
    buf[45]=LOBYTE(ui->horiSliderAxis3Max->value());
    buf[46]=HIBYTE(ui->horiSliderAxis3Max->value());
    buf[47]=0; //Reserved
    buf[48]=LOBYTE(ui->horiSliderAxis4Min->value());
    buf[49]=HIBYTE(ui->horiSliderAxis4Min->value());
    buf[50]=LOBYTE(ui->horiSliderAxis4Max->value());
    buf[51]=HIBYTE(ui->horiSliderAxis4Max->value());
    buf[52]=0; //Reserved
    buf[53]=LOBYTE(ui->horiSliderAxis5Min->value());
    buf[54]=HIBYTE(ui->horiSliderAxis5Min->value());
    buf[55]=LOBYTE(ui->horiSliderAxis5Max->value());
    buf[56]=HIBYTE(ui->horiSliderAxis5Max->value());
    buf[57]=0; //Reserved
    buf[58]=LOBYTE(ui->horiSliderAxis6Min->value());
    buf[59]=HIBYTE(ui->horiSliderAxis6Min->value());
    buf[60]=LOBYTE(ui->horiSliderAxis6Max->value());
    buf[61]=HIBYTE(ui->horiSliderAxis6Max->value());
    buf[62]=0; //Reserved

    if (ui->checkBox_POV1->isChecked()) buf[63]|=0x1;
    if (ui->checkBox_POV2->isChecked()) buf[63]|=0x2;
    if (ui->checkBox_POV3->isChecked()) buf[63]|=0x4;
    if (ui->checkBox_POV4->isChecked()) buf[63]|=0x8;

//    buf[63]=(uint8_t)(ui->label_POV1->isEnabled())    ||
//                     (ui->label_POV2->isEnabled())<<1 ||
//                     (ui->label_POV3->isEnabled())<<2 ||
//                     (ui->label_POV4->isEnabled())<<3 ;

    res=hid_write(handle_read, buf, BUFFSIZE);

}

void OSHStudio::getConfig_Slot()
{
    uint8_t buf[BUFFSIZE]={0};
    uint8_t bufrep2[2]={3,1};
    uint8_t res=0,j=0;

    do {
        res=hid_write(handle_read, bufrep2, 2);
        res=hid_read(handle_read, buf, BUFFSIZE);
//        res=hid_read_timeout(handle_read, buf, BUFFSIZE,100);
//        ui->textEdit->append(QString::number(buf[0]));
        j++;
       } while ((buf[0] != 4) || j<50 );

        ui->comboBoxA0->setCurrentIndex(buf[1]);
        ui->comboBoxA1->setCurrentIndex(buf[2]);
        ui->comboBoxA2->setCurrentIndex(buf[3]);
        ui->comboBoxA3->setCurrentIndex(buf[4]);
        ui->comboBoxA4->setCurrentIndex(buf[5]);
        ui->comboBoxA5->setCurrentIndex(buf[6]);
        ui->comboBoxA6->setCurrentIndex(buf[7]);
        ui->comboBoxA7->setCurrentIndex(buf[8]);
        ui->comboBoxA8->setCurrentIndex(buf[9]);
        ui->comboBoxA9->setCurrentIndex(buf[10]);
        ui->comboBoxA10->setCurrentIndex(buf[11]);
        ui->comboBoxA11->setCurrentIndex(buf[12]);
        ui->comboBoxA12->setCurrentIndex(buf[13]);
        ui->comboBoxA15->setCurrentIndex(buf[14]);
        ui->comboBoxB0->setCurrentIndex(buf[15]);
        ui->comboBoxB1->setCurrentIndex(buf[16]);
        ui->comboBoxB3->setCurrentIndex(buf[17]);
        ui->comboBoxB4->setCurrentIndex(buf[18]);
        ui->comboBoxB5->setCurrentIndex(buf[19]);
        ui->comboBoxB6->setCurrentIndex(buf[20]);
        ui->comboBoxB7->setCurrentIndex(buf[21]);
        ui->comboBoxB8->setCurrentIndex(buf[22]);
        ui->comboBoxB9->setCurrentIndex(buf[23]);
        ui->comboBoxB10->setCurrentIndex(buf[24]);
        ui->comboBoxB11->setCurrentIndex(buf[25]);
        ui->comboBoxB12->setCurrentIndex(buf[26]);
        ui->comboBoxB13->setCurrentIndex(buf[27]);
        ui->comboBoxB14->setCurrentIndex(buf[28]);
        ui->comboBoxB15->setCurrentIndex(buf[29]);
        ui->comboBoxC13->setCurrentIndex(buf[30]);
        ui->comboBoxC14->setCurrentIndex(buf[31]);
        ui->comboBoxC15->setCurrentIndex(buf[32]);

        ui->horiSliderAxis1Min->setValue((buf[34]<<8) | buf[33]);
        ui->horiSliderAxis1Max->setValue((buf[36]<<8) | buf[35]);

        ui->horiSliderAxis2Min->setValue((buf[39]<<8) | buf[38]);
        ui->horiSliderAxis2Max->setValue((buf[41]<<8) | buf[40]);

        ui->horiSliderAxis3Min->setValue((buf[44]<<8) | buf[43]);
        ui->horiSliderAxis3Max->setValue((buf[46]<<8) | buf[45]);

        ui->horiSliderAxis4Min->setValue((buf[49]<<8) | buf[48]);
        ui->horiSliderAxis4Max->setValue((buf[51]<<8) | buf[50]);

        ui->horiSliderAxis5Min->setValue((buf[54]<<8) | buf[53]);
        ui->horiSliderAxis5Max->setValue((buf[56]<<8) | buf[55]);

        ui->horiSliderAxis6Min->setValue((buf[59]<<8) | buf[58]);
        ui->horiSliderAxis6Max->setValue((buf[61]<<8) | buf[60]);

        if (buf[63] & 0x1) ui->checkBox_POV1->setChecked(true);
                else ui->checkBox_POV1->setChecked(false);
        if (buf[63] & 0x2) ui->checkBox_POV2->setChecked(true);
                else ui->checkBox_POV2->setChecked(false);
        if (buf[63] & 0x4) ui->checkBox_POV3->setChecked(true);
                else ui->checkBox_POV3->setChecked(false);
        if (buf[63] & 0x8) ui->checkBox_POV4->setChecked(true);
                else ui->checkBox_POV4->setChecked(false);

}

QString OSHStudio::DrawTypeComboBox(pintype i) {
    switch (i) {
        case AnalogNoSmooth:    return "QComboBox { color: white; background-color: black; }";
        case AnalogLowSmooth:   return "QComboBox { color: white; background-color: black; }";
        case AnalogMedSmooth:   return "QComboBox { color: white; background-color: black; }";
        case AnalogHighSmooth:  return "QComboBox { color: white; background-color: black; }";
        case Rotary_PINA:       return "QComboBox { color: white; background-color: darkRed; }";
        case Rotary_PINB:       return "QComboBox { color: white; background-color: darkRed; }";
        case Rotary_Enc:        return "QComboBox { color: black; background-color: red; }";
        case Button_ROW:        return "QComboBox { color: white; background-color: green; }";
        case Button_COLUMN:     return "QComboBox { color: white; background-color: darkGreen; }";
        case Button:            return "QComboBox { color: white; background-color: blue; }";
        case RotSwPole:         return "QComboBox { color: white; background-color: magenta; }";
        case RotSwWire:         return "QComboBox { color: white; background-color: darkMagenta; }";
        case Not_Used:          return "QComboBox { color: black; background-color: light gray; }";
    }
    return ("Non valid pin type");
}


void OSHStudio::drawAxis1Value(uint16_t axis_value) {
    ui->progressBarAxis1->setValue(axis_value);
}

void OSHStudio::drawAxis2Value(uint16_t axis_value) {
    ui->progressBarAxis2->setValue(axis_value);
}

void OSHStudio::drawAxis3Value(uint16_t axis_value) {
    ui->progressBarAxis3->setValue(axis_value);
}

void OSHStudio::drawAxis4Value(uint16_t axis_value) {
    ui->progressBarAxis4->setValue(axis_value);
}

void OSHStudio::drawAxis5Value(uint16_t axis_value) {
    ui->progressBarAxis5->setValue(axis_value);
}

void OSHStudio::drawAxis6Value(uint16_t axis_value) {
    ui->progressBarAxis6->setValue(axis_value);
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


    for(int i =32; i < 64; ++i)
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


    for(int i = 0; i < 32; ++i)
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




void OSHStudio::showConnectDeviceInfo() {
    ui->label_DevDescImg->setVisible(true);
    ui->label_DevDesc->setVisible(true);
    ui->getConfig_button->setEnabled(true);
    ui->saveConfig_Button->setEnabled(true);

}

void OSHStudio::hideConnectDeviceInfo() {
    ui->label_DevDescImg->setVisible(false);
    ui->label_DevDesc->setVisible(false);
    ui->getConfig_button->setEnabled(false);
    ui->saveConfig_Button->setEnabled(false);
}

QString OSHStudio::convertIntToString(int i) {
    return QString::number(i);
}

int OSHStudio::convertStringToInt(QString str) {
    return str.toInt();
}

void OSHStudio::lineEditAxis1Min_Slot(int i) {
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
}

void OSHStudio::comboBoxPaint() {
    ui->comboBoxA0->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA0->currentIndex()));
    ui->comboBoxA0->clearFocus();
    ui->comboBoxA1->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA1->currentIndex()));
    ui->comboBoxA1->clearFocus();
    ui->comboBoxA2->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA2->currentIndex()));
    ui->comboBoxA2->clearFocus();
    ui->comboBoxA3->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA3->currentIndex()));
    ui->comboBoxA3->clearFocus();
    ui->comboBoxA4->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA4->currentIndex()));
    ui->comboBoxA4->clearFocus();
    ui->comboBoxA5->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA5->currentIndex()));
    ui->comboBoxA5->clearFocus();
    ui->comboBoxA6->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA6->currentIndex()));
    ui->comboBoxA6->clearFocus();
    ui->comboBoxA7->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA7->currentIndex()));
    ui->comboBoxA7->clearFocus();
    ui->comboBoxA8->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA8->currentIndex()));
    ui->comboBoxA8->clearFocus();
    ui->comboBoxA9->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA9->currentIndex()));
    ui->comboBoxA9->clearFocus();
    ui->comboBoxA10->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA10->currentIndex()));
    ui->comboBoxA10->clearFocus();
    ui->comboBoxA11->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA11->currentIndex()));
    ui->comboBoxA11->clearFocus();
    ui->comboBoxA12->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA12->currentIndex()));
    ui->comboBoxA12->clearFocus();
    ui->comboBoxA15->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxA15->currentIndex()));
    ui->comboBoxA15->clearFocus();
    ui->comboBoxB0->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB0->currentIndex()));
    ui->comboBoxB0->clearFocus();
    ui->comboBoxB1->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB1->currentIndex()));
    ui->comboBoxB1->clearFocus();
    ui->comboBoxB3->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB3->currentIndex()));
    ui->comboBoxB3->clearFocus();
    ui->comboBoxB4->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB4->currentIndex()));
    ui->comboBoxB4->clearFocus();
    ui->comboBoxB5->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB5->currentIndex()));
    ui->comboBoxB5->clearFocus();
    ui->comboBoxB6->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB6->currentIndex()));
    ui->comboBoxB6->clearFocus();
    ui->comboBoxB7->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB7->currentIndex()));
    ui->comboBoxB7->clearFocus();
    ui->comboBoxB8->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB8->currentIndex()));
    ui->comboBoxB8->clearFocus();
    ui->comboBoxB9->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB9->currentIndex()));
    ui->comboBoxB9->clearFocus();
    ui->comboBoxB10->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB10->currentIndex()));
    ui->comboBoxB10->clearFocus();
    ui->comboBoxB11->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB11->currentIndex()));
    ui->comboBoxB11->clearFocus();
    ui->comboBoxB12->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB12->currentIndex()));
    ui->comboBoxB12->clearFocus();
    ui->comboBoxB13->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB13->currentIndex()));
    ui->comboBoxB13->clearFocus();
    ui->comboBoxB14->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB14->currentIndex()));
    ui->comboBoxB14->clearFocus();
    ui->comboBoxB15->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxB15->currentIndex()));
    ui->comboBoxB15->clearFocus();
    ui->comboBoxC13->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxC13->currentIndex()));
    ui->comboBoxC13->clearFocus();
    ui->comboBoxC14->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxC14->currentIndex()));
    ui->comboBoxC14->clearFocus();
    ui->comboBoxC15->setStyleSheet(DrawTypeComboBox((pintype)ui->comboBoxC15->currentIndex()));
    ui->comboBoxC15->clearFocus();

    drawHelp();
}

void OSHStudio::loadFromFile()
{
    QString line;
    QString value;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Config File"), "",
        tr("OSH Config Files (*.osh);;All Files (*)"));

    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
                if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
                }
            QTextStream in(&file);

            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA0->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA1->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA2->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA3->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA4->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA5->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA6->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA7->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA8->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA9->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA10->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA11->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA12->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxA15->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB0->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB1->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB3->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB4->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB5->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB6->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB7->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB8->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB9->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB10->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB11->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB12->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB13->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB14->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxB15->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxC13->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxC14->setCurrentIndex(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->comboBoxC15->setCurrentIndex(value.toUInt());


            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis1Min->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis1Max->setValue(value.toUInt());
            line = in.readLine(); //"Reserved="

            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis2Min->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis2Max->setValue(value.toUInt());
            line = in.readLine(); // "Reserved="

            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis3Min->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis3Max->setValue(value.toUInt());
            line = in.readLine(); // "Reserved="

            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis4Min->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis4Max->setValue(value.toUInt());
            line = in.readLine(); // "Reserved="

            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis5Min->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis5Max->setValue(value.toUInt());
            line = in.readLine(); // "Reserved="

            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis6Min->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSliderAxis6Max->setValue(value.toUInt());
            line = in.readLine(); // "Reserved="

            line = in.readLine();
            value = line.section('=',1,1);
            if (value.toUInt() & 0x1) ui->checkBox_POV1->setChecked(true);
                    else ui->checkBox_POV1->setChecked(false);
            if (value.toUInt() & 0x2) ui->checkBox_POV2->setChecked(true);
                    else ui->checkBox_POV2->setChecked(false);
            if (value.toUInt() & 0x4) ui->checkBox_POV3->setChecked(true);
                    else ui->checkBox_POV3->setChecked(false);
            if (value.toUInt() & 0x8) ui->checkBox_POV4->setChecked(true);
                    else ui->checkBox_POV4->setChecked(false);


            file.close();
    }
}

void OSHStudio::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Config File"), "",
        tr("OSH Config Files (*.osh);;All Files (*)"));

    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
                }


    QTextStream out(&file);

    out << "A0=" << ui->comboBoxA0->currentIndex() << "\n"
        << "A1=" << ui->comboBoxA1->currentIndex() << "\n"
        << "A2=" << ui->comboBoxA2->currentIndex() << "\n"
        << "A3=" << ui->comboBoxA3->currentIndex() << "\n"
        << "A4=" << ui->comboBoxA4->currentIndex() << "\n"
        << "A5=" << ui->comboBoxA5->currentIndex() << "\n"
        << "A6=" << ui->comboBoxA6->currentIndex() << "\n"
        << "A7=" << ui->comboBoxA7->currentIndex() << "\n"
        << "A8=" << ui->comboBoxA8->currentIndex() << "\n"
        << "A9=" << ui->comboBoxA9->currentIndex() << "\n"
        << "A10=" << ui->comboBoxA10->currentIndex() << "\n"
        << "A11=" << ui->comboBoxA11->currentIndex() << "\n"
        << "A12=" << ui->comboBoxA12->currentIndex() << "\n"
        << "A15=" << ui->comboBoxA15->currentIndex() << "\n"
        << "B0=" << ui->comboBoxB0->currentIndex() << "\n"
        << "B1=" << ui->comboBoxB1->currentIndex() << "\n"
        << "B3=" << ui->comboBoxB3->currentIndex() << "\n"
        << "B4=" << ui->comboBoxB4->currentIndex() << "\n"
        << "B5=" << ui->comboBoxB5->currentIndex() << "\n"
        << "B6=" << ui->comboBoxB6->currentIndex() << "\n"
        << "B7=" << ui->comboBoxB7->currentIndex() << "\n"
        << "B8=" << ui->comboBoxB8->currentIndex() << "\n"
        << "B9=" << ui->comboBoxB9->currentIndex() << "\n"
        << "B10=" << ui->comboBoxB10->currentIndex() << "\n"
        << "B11=" << ui->comboBoxB11->currentIndex() << "\n"
        << "B12=" << ui->comboBoxB12->currentIndex() << "\n"
        << "B13=" << ui->comboBoxB13->currentIndex() << "\n"
        << "B14=" << ui->comboBoxB14->currentIndex() << "\n"
        << "B15=" << ui->comboBoxB15->currentIndex() << "\n"
        << "C13=" << ui->comboBoxC13->currentIndex() << "\n"
        << "C14=" << ui->comboBoxC14->currentIndex() << "\n"
        << "C15=" << ui->comboBoxC15->currentIndex() << "\n"

        << "Axis1Min=" << ui->horiSliderAxis1Min->value() << "\n"
        << "Axis1Max=" << ui->horiSliderAxis1Max->value() << "\n"
        << "Reserved="    << "\n"
        << "Axis2Min=" << ui->horiSliderAxis2Min->value() << "\n"
        << "Axis2Max=" << ui->horiSliderAxis2Max->value() << "\n"
        << "Reserved="    << "\n"
        << "Axis3Min=" << ui->horiSliderAxis3Min->value() << "\n"
        << "Axis3Max=" << ui->horiSliderAxis3Max->value() << "\n"
        << "Reserved="   << "\n"
        << "Axis4Min=" << ui->horiSliderAxis4Min->value() << "\n"
        << "Axis4Max=" << ui->horiSliderAxis4Max->value() << "\n"
        << "Reserved="   << "\n"
        << "Axis5Min=" << ui->horiSliderAxis5Min->value() << "\n"
        << "axis5Max=" << ui->horiSliderAxis5Max->value() << "\n"
        << "Reserved="   << "\n"
        << "Axis6Min=" << ui->horiSliderAxis6Min->value() << "\n"
        << "Axis6Max=" << ui->horiSliderAxis6Max->value() << "\n"
        << "Reserved="   << "\n";

    int POVConf=0;
    if (ui->checkBox_POV1->isChecked()) POVConf|=0x1;
    if (ui->checkBox_POV2->isChecked()) POVConf|=0x2;
    if (ui->checkBox_POV3->isChecked()) POVConf|=0x4;
    if (ui->checkBox_POV4->isChecked()) POVConf|=0x8;
     out << "POVConfig=" << POVConf;

       file.close();
    }
}

void OSHStudio::gatherPinConfig(pintype i)
{
    switch (i) {
        case (0): break;
        case (1):
        case (2):
        case (3):
        case (4): NumberAnalogInputs ++; break;
        case (5): PinA++; break;
        case (6): PinB++; break;
        case (7): Rotaries++; break;
        case (8): ButtonsRows++; break;
        case (9): ButtonsColumns++; break;
        case (10): Buttons++; break;
        case (11): RotSwitchPoles++; break;
        case (12): RotSwitchWires++; break;
    }
};

void OSHStudio::gatherAllConf()
{
    NumberAnalogInputs=0;
    PinA=0;
    PinB=0;
    Rotaries=0;
    ButtonsRows=0;
    ButtonsColumns=0;
    Buttons=0;
    RotSwitchPoles=0;
    RotSwitchWires=0;

    gatherPinConfig((pintype)ui->comboBoxA0->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA1->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA2->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA3->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA4->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA5->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA6->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA7->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA8->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA9->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA10->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA11->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA12->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxA15->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB0->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB1->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB3->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB4->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB5->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB6->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB7->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB8->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB9->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB10->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB11->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB12->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB13->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB14->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxB15->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxC13->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxC14->currentIndex());
    gatherPinConfig((pintype)ui->comboBoxC15->currentIndex());
}

void OSHStudio::drawHelp()
{
    QString HelpText;

    gatherAllConf();

    if (NumberAnalogInputs > 0) {
        HelpText = "<br />" + QString::number(NumberAnalogInputs) + " analog inputs <br />";
        if (NumberAnalogInputs > 6)
            HelpText = HelpText + "<font color='red'>Sorry, not more than 6 analog inputs</font><br />";
    }

    if (Rotaries > 0) {
        HelpText = HelpText + "<br />" + QString::number(Rotaries) + " rotary encoders <br />";
        if ((PinA != 1) || (PinB != 1))
            HelpText = HelpText + "<font color='red'>You have to properly configure PINA and PINB encoder's pins</font><br /><br />";
    }

    if ((ButtonsRows>0) && (ButtonsColumns>0))
        HelpText = HelpText + "<br />" + QString::number(ButtonsRows * ButtonsColumns) + " buttons in matrix <br />";

    if ((ButtonsRows>0) && (!ButtonsColumns))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 column to matrix</font><br />";

    if ((!ButtonsRows) && (ButtonsColumns>0))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 row to matrix</font><br />";

    if (Buttons>0)
        HelpText = HelpText + "<br />" + QString::number(Buttons) + " single buttons (2nd leg to +3.3V) <br />";


    if ((RotSwitchWires>0) && (RotSwitchPoles>0))
        HelpText = HelpText + "<br />" + QString::number(RotSwitchWires*RotSwitchPoles) + " buttons in Rotary Switch Config <br />";

    if ((RotSwitchWires>0) && (RotSwitchPoles<1))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 Pole to Rotary Switch Config</font><br />";

    if ((RotSwitchWires<1) && (RotSwitchPoles>0))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 Wire to Rotary Switch Config</font><br />";


    ui->labelHelp->setText(HelpText);
}
