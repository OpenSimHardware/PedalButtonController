#include "oshstudio.h"
#include "ui_oshstudio.h"
#include "worker.h"
#include<QTextEdit>
#include<QMessageBox>

hid_device *handle_read, *handle_write;

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

      connect(ui->lineEdit_Device_ident, SIGNAL(textChanged(QString)), SLOT(show_USB_ident_uniq(QString)));
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




      qRegisterMetaType<uint16_t>("uint16_t");
      qRegisterMetaType<uint64_t>("uint64_t");
      qRegisterMetaType<uint16_t>("uint8_t");
      qRegisterMetaType<uint16_t>("uint8_t *");



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
      connect(worker, SIGNAL(putConfigPacket(uint8_t *)),
                            SLOT(getConfigPacket(uint8_t *)));
      connect(worker, SIGNAL(putACKpacket(uint8_t)),
                            SLOT(getACKpacket(uint8_t)));


      thread->start();

      //hide all single encoders config for now
      QString name_template_SE("widget_SE%1");
      for(int i =1; i <= MAX_SINGLE_ENCODERS; i++){
          oshsingenc *SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i));
          SEwid->setVisible(false);
          connect(SEwid, SIGNAL(item_changed()),  SLOT(drawHelpSE()));
       }
       ui->label_ZeroSglEncoders->setVisible(true);

       //hide all A2B widgets
       QString name_template_A2B("widget_A2B_%1");
       for(int i =1; i <= MAX_A2B_INPUTS; i++){
           A2Bstore[i-1].widget_ptr = ui->tabWidget->findChild<osha2bw *>(name_template_A2B.arg(i));
           A2Bstore[i-1].widget_ptr->setVisible(false);
           A2Bstore[i-1].number_buttons=1;
        }
        ui->label_ZeroA2B->setVisible(true);
        resetAllA2B();


       QString name_template("widget_PB%1");
       for(int i = 0; i < 32; i++) {
          oshpincombobox *pinComboBox = ui->tabWidget->findChild<oshpincombobox *>(name_template.arg(i));
          pinComboBox->set_pin_number(i);
          connect(pinComboBox, SIGNAL(item_changed()),  SLOT(pinConfChanged()));
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

      resetConfig_Slot();
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
    config.combined_axis_pin1=convertPinnameToIndex(pinname);
}

void OSHStudio::showPin2AxisComb(QString pinname){
    ui->label_AxisCombPin2->setText(pinname);
    config.combined_axis_pin2=convertPinnameToIndex(pinname);
}

void OSHStudio::gatherPinsConf()
{
    //TODO - eliminate these ugly globals
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
    QStringList AxisComb1;
    Analog2Buttons_inputs = 0;


    uint8_t pin_number=0;

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
                case (Analog2Button):           A2Bstore[Analog2Buttons_inputs++].pin_number=pin_number; break;
                case (Chain_Rotary_PINA):       Chain_PinA++; break;
                case (Chain_Rotary_PINB):       Chain_PinB++; break;
                case (Chain_Rotary_Enc_1):      Chain_Rotaries_1++; break;
                case (Chain_Rotary_Enc_2):      Chain_Rotaries_2++; break;
                case (Chain_Rotary_Enc_4):      Chain_Rotaries_4++; break;
                case (Single_Rotary_PINA_1):    single_encoders_1_store[Single_Rotaries_PINA_1++].pinA=pin_number;
                                                break;
                case (Single_Rotary_PINB_1):    single_encoders_1_store[Single_Rotaries_PINB_1++].pinB=pin_number;
                                                break;
                case (Single_Rotary_PINA_2):    single_encoders_2_store[Single_Rotaries_PINA_2++].pinA=pin_number;
                                                break;
                case (Single_Rotary_PINB_2):    single_encoders_2_store[Single_Rotaries_PINB_2++].pinB=pin_number;
                                                break;
                case (Single_Rotary_PINA_4):    single_encoders_4_store[Single_Rotaries_PINA_4++].pinA=pin_number;
                                                break;
                case (Single_Rotary_PINB_4):    single_encoders_4_store[Single_Rotaries_PINB_4++].pinB=pin_number;
                                                break;
                case (Button_ROW):              ButtonsRows++; break;
                case (Button_COLUMN):           ButtonsColumns++; break;
                case (Button):
                case (Button_GND):              Buttons++; break;
                case (RotSwPole):               RotSwitchPoles++; break;
                case (RotSwWire):               RotSwitchWires++; break;
                default:                        break;
                }
                config.pin[pin_number++] = curr_pin_type;
        }
    }

    ui->comboBox_AxisCombBegin->clear();
    ui->comboBox_AxisCombEnd->clear();
    ui->comboBox_AxisCombBegin->addItems(AxisComb1);
    ui->comboBox_AxisCombEnd->addItems(AxisComb1);
    ui->comboBox_AxisCombBegin->setCurrentIndex((ui->comboBox_AxisCombBegin->count())-2);
    ui->comboBox_AxisCombEnd->setCurrentIndex((ui->comboBox_AxisCombEnd->count())-1);
}

void OSHStudio::populateDefA2B(){
  //  resetAllA2B();

    config.analog_2_button_inputs = Analog2Buttons_inputs;
    ui->label_ZeroA2B->setVisible(config.analog_2_button_inputs ? false : true);

     for(int i=0; i < Analog2Buttons_inputs; i++){
         A2Bstore[i].widget_ptr->setVisible(true);
//         A2Bstore[i].widget_ptr->setPinName(pin_names[A2Bstore[i].pin_number]);
      }
     showA2Btab();
}

void OSHStudio::showA2Btab(){
    ui->label_ZeroA2B->setVisible(config.analog_2_button_inputs ? false : true);
    QString name_template_A2B("widget_A2B_%1");
    for(int i=0; i < MAX_A2B_INPUTS; i++){
        A2Bstore[i].widget_ptr->setVisible(false);
     }

    for(uint8_t i=0; i<config.analog_2_button_inputs; i++){
        A2Bstore[i].widget_ptr->setVisible(true);
        A2Bstore[i].widget_ptr->setPinName(pin_names[A2Bstore[i].pin_number]);
        if (i<5){
            A2Bstore[i].widget_ptr->setButtonsCount(config.a2b_1st5[i].buttons_number);
            A2Bstore[i].widget_ptr->setButtonsIntervals(config.a2b_1st5[i].buttons_intervals);
        } else {
            A2Bstore[i].widget_ptr->setButtonsCount(config.a2b_2nd5[i-(MAX_A2B_INPUTS/2)].buttons_number);
            A2Bstore[i].widget_ptr->setButtonsIntervals(config.a2b_2nd5[i-(MAX_A2B_INPUTS/2)].buttons_intervals);
        }
    }
}

void OSHStudio::resetAllA2B(){
    QString name_template_A2B("widget_A2B_%1");
    for(int i=0; i < MAX_A2B_INPUTS; i++){
        A2Bstore[i].widget_ptr->setVisible(false);
        A2Bstore[i].number_buttons=1;
        A2Bstore[i].widget_ptr->setButtonsCount(1);
     }
    for (uint8_t i=0; i<MAX_A2B_INPUTS/2;i++){
        config.a2b_1st5[i].buttons_number = 1;
        config.a2b_1st5[i].buttons_intervals[0] = 127;
        config.a2b_2nd5[i].buttons_number = 1;
        config.a2b_2nd5[i].buttons_intervals[0] = 127;
    }
}

void OSHStudio::populateDefSE(){
    single_encoders_1 = (Single_Rotaries_PINA_1>Single_Rotaries_PINB_1) ? Single_Rotaries_PINB_1 : Single_Rotaries_PINA_1;
    single_encoders_2 = (Single_Rotaries_PINA_2>Single_Rotaries_PINB_2) ? Single_Rotaries_PINB_2 : Single_Rotaries_PINA_2;
    single_encoders_4 = (Single_Rotaries_PINA_4>Single_Rotaries_PINB_4) ? Single_Rotaries_PINB_4 : Single_Rotaries_PINA_4;
    for (uint8_t i=0; i<single_encoders_1; i++){
        config.single_encoder_pinA[i] = single_encoders_1_store[i].pinA;
        config.single_encoder_pinB[i] = single_encoders_1_store[i].pinB;
    }
    for (uint8_t i=0; i<single_encoders_2; i++){
        config.single_encoder_pinA[i+single_encoders_1] = single_encoders_2_store[i].pinA;
        config.single_encoder_pinB[i+single_encoders_1] = single_encoders_2_store[i].pinB;
    }
    for (uint8_t i=0; i<single_encoders_4; i++){
        config.single_encoder_pinA[i+single_encoders_1+single_encoders_2] = single_encoders_4_store[i].pinA;
        config.single_encoder_pinB[i+single_encoders_1+single_encoders_2] = single_encoders_4_store[i].pinB;
    }
    config.total_single_encoders = single_encoders_1 + single_encoders_2 + single_encoders_4;
    showSingleEncodersTab();
}

void OSHStudio::showSingleEncodersTab(void) {
    ui->label_ZeroSglEncoders->setVisible(config.total_single_encoders ? false : true);
    QString name_template_SE("widget_SE%1");
    for(int i =0; i < MAX_SINGLE_ENCODERS; i++){
        oshsingenc *SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i+1));
        SEwid->setVisible(false);
        SEwid->clearPinsLists();
     }
    for(int i =0; i < config.total_single_encoders; i++){
        oshsingenc *SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i+1));
        SEwid->setVisible(true);
        for (uint8_t i=0; i<config.total_single_encoders; i++){
            SEwid->addPins2Lists(config.single_encoder_pinA[i], config.single_encoder_pinB[i],
                                 config.pin[config.single_encoder_pinA[i]]);
        }
        SEwid->setPinsPair(i);
     }
}


void OSHStudio::drawHelpSE() {
    struct se_store {
        uint8_t pina;
        uint8_t pinb;
        oshsingenc *SEwid;
    };
    se_store temp_store[MAX_SINGLE_ENCODERS];

    QString name_template_SE("widget_SE%1");
    QString SEHelp_text;

    // populate temp array
    for(int i =0; i < config.total_single_encoders; i++){
        temp_store[i].SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i+1));
        temp_store[i].pina = temp_store[i].SEwid->getPinA();
        temp_store[i].pinb = temp_store[i].SEwid->getPinB();
        temp_store[i].SEwid->setAlarmPinA(false);
        temp_store[i].SEwid->setAlarmPinB(false);
 //       SEHelp_text = SEHelp_text + "Pin A - " + QString::number(temp_store[i].pina) + "type - " + QString::number(config.pin[temp_store[i].pina]) +
 //               ", Pin B - " + QString::number(temp_store[i].pinb) + "type - " + QString::number(config.pin[temp_store[i].pinb]) + "<br />";
        // check for type equality
        if (((config.pin[temp_store[i].pina] == Single_Rotary_PINA_1) &&
                (config.pin[temp_store[i].pinb] != Single_Rotary_PINB_1)) ||
            ((config.pin[temp_store[i].pina] == Single_Rotary_PINA_2) &&
                (config.pin[temp_store[i].pinb] != Single_Rotary_PINB_2)) ||
            ((config.pin[temp_store[i].pina] == Single_Rotary_PINA_4) &&
                (config.pin[temp_store[i].pinb] != Single_Rotary_PINB_4)))
        {
            temp_store[i].SEwid->setAlarmPinA(true);
            temp_store[i].SEwid->setAlarmPinB(true);
        }

    }

    // check for pins differentiality
    for(int i =0; i < config.total_single_encoders - 1; i++){
        for(int j =i +1; j < config.total_single_encoders; j++){
            if (temp_store[i].pina == temp_store[j].pina){
                temp_store[i].SEwid->setAlarmPinA(true);
                temp_store[j].SEwid->setAlarmPinA(true);
            }
            if (temp_store[i].pinb == temp_store[j].pinb){
                temp_store[i].SEwid->setAlarmPinB(true);
                temp_store[j].SEwid->setAlarmPinB(true);
            }
        }
    }

 //   ui->label_SEHelp->setText(SEHelp_text);
}

uint8_t OSHStudio::convertPinnameToIndex (QString pname) {
    for(uint8_t i =0; i < USEDPINS; i++) {
        if (pin_names[i]==pname) return i;
    }
    return 255;
}

void OSHStudio::pinConfChanged(){
    gatherPinsConf();
    populateDefSE();
    populateDefA2B();
    drawHelp();
}

void OSHStudio::drawHelp()
{
    QString HelpText;

    if (NumberAnalogInputs) {
        HelpText = "<br />" + QString::number(NumberAnalogInputs) + " analog inputs <br />";
        if (NumberAnalogInputs > 7)
            HelpText = HelpText + "<font color='red'>Max 7 analog inputs (2 in combined axis)</font><br />";
    }

    if (Analog2Buttons_inputs) HelpText += "<br />" + QString::number(Analog2Buttons_inputs) + " analog to buttons inputs <br />";

    if ((Chain_Rotaries_1 > 0) ||(Chain_Rotaries_2 > 0) || (Chain_Rotaries_4 > 0)) {
        HelpText = HelpText + "<br />" +
                QString::number(Chain_Rotaries_1 + Chain_Rotaries_2 + Chain_Rotaries_4) + " chained rotary encoders <br />";
        if ((Chain_PinA != 1) || (Chain_PinB != 1))
            HelpText = HelpText + "<font color='red'>You have to properly configure PINA and PINB pins of chained encoders</font><br /><br />";
    }

    if (config.total_single_encoders > 0) {
        HelpText = HelpText + "<br />" + QString::number(config.total_single_encoders) + " single rotary encoders <br />";
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

