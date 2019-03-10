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

//      connect(ui->checkBox_POV1, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV1Changed(int)));
//      connect(ui->checkBox_POV2, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV2Changed(int)));
//      connect(ui->checkBox_POV3, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV3Changed(int)));
//      connect(ui->checkBox_POV4, SIGNAL(stateChanged(int)), SLOT(checkBoxPOV4Changed(int)));




      qRegisterMetaType<uint16_t>("uint16_t");
      qRegisterMetaType<uint64_t>("uint64_t");
      qRegisterMetaType<uint16_t>("uint8_t");
      qRegisterMetaType<uint16_t>("uint8_t *");



      QThread* thread = new QThread;
      Worker* worker = new Worker();
      worker->moveToThread(thread);

      connect(thread, SIGNAL(started()), worker, SLOT(processData()));
 //     connect(worker, SIGNAL(putAxis1Value(uint16_t)),
 //                           SLOT(drawAxis1Value(uint16_t)));
 //     connect(worker, SIGNAL(putAxis2Value(uint16_t)),
 //                           SLOT(drawAxis2Value(uint16_t)));
 //     connect(worker, SIGNAL(putAxis3Value(uint16_t)),
 //                           SLOT(drawAxis3Value(uint16_t)));
 //     connect(worker, SIGNAL(putAxis4Value(uint16_t)),
 //                           SLOT(drawAxis4Value(uint16_t)));
 //     connect(worker, SIGNAL(putAxis5Value(uint16_t)),
 //                           SLOT(drawAxis5Value(uint16_t)));
 //     connect(worker, SIGNAL(putAxis6Value(uint16_t)),
 //                           SLOT(drawAxis6Value(uint16_t)));
 //     connect(worker, SIGNAL(putButtons1Value(uint64_t)),
 //                           SLOT(drawButtons1Value(uint64_t)));
 //     connect(worker, SIGNAL(putButtons2Value(uint64_t)),
 //                           SLOT(drawButtons2Value(uint64_t)));
 //     connect(worker, SIGNAL(putPOVSvalue(uint64_t)),
 //                           SLOT(drawPOVSvalue(uint64_t)));
      connect(worker, SIGNAL(putGamepadPacket(uint8_t *)),
                            SLOT(getGamepadPacket(uint8_t *)));
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
      for(uint8_t i =1; i <= MAX_SINGLE_ENCODERS; i++){
          oshsingenc *SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i));
          SEwid->setVisible(false);
          connect(SEwid, SIGNAL(item_changed()),  SLOT(drawHelpSE()));
       }
       ui->label_ZeroSglEncoders->setVisible(true);

       //hide all A2B widgets
       QString name_template_A2B("widget_A2B_%1");
       for(uint8_t i =1; i <= MAX_A2B_INPUTS; i++){
           A2Bstore[i-1].widget_ptr = ui->tabWidget->findChild<osha2bw *>(name_template_A2B.arg(i));
           A2Bstore[i-1].widget_ptr->setVisible(false);
           A2Bstore[i-1].number_buttons=1;
           connect(A2Bstore[i-1].widget_ptr, SIGNAL(buttons_number_changed()), SLOT(get_all_A2B_buttons()));
        }
        ui->label_ZeroA2B->setVisible(true);
        resetAllA2B();

        //hide all buttons
        QString name_template_SB("widget_SB_%1");
        for(uint8_t i =1; i <= MAX_BUTTONS; i++){
            SBstore[i-1].SB_wid_prt = ui->tabWidget->findChild<oshbuttonw *>(name_template_SB.arg(i));
            SBstore[i-1].SB_wid_prt -> setVisible(false);
            SBstore[i-1].SB_wid_prt->set_button_type(joystick_button);
            SBstore[i-1].button_type = joystick_button;
            connect(SBstore[i-1].SB_wid_prt, SIGNAL(button_type_changed()), SLOT(get_all_SB_buttons()));
         }

       QString name_template("widget_PB%1");
       for(uint8_t i = 0; i < 32; i++) {
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
    interval=1000/interval;
    ui->label_59->setText(const_desc + QString::number(interval) + " Hz");
}

void OSHStudio::getGamepadPacket(uint8_t * buff){
    struct gamepad_report_ gamepad_report;
    memcpy(&(gamepad_report.packet_id), buff, sizeof(struct gamepad_report_));

    ui->widget_axis1->setAxisValue(gamepad_report.axis[0]);
    ui->widget_axis2->setAxisValue(gamepad_report.axis[1]);
    ui->widget_axis3->setAxisValue(gamepad_report.axis[2]);
    ui->widget_axis4->setAxisValue(gamepad_report.axis[3]);
    ui->widget_axis5->setAxisValue(gamepad_report.axis[4]);
    ui->widget_axis6->setAxisValue(gamepad_report.axis[5]);

    for(int i = 0; i < MAX_BUTTONS; i++)
    {
        if ((SBstore[i].button_type == joystick_button) && (gamepad_report.buttons & (0x1ULL<<i)))
                SBstore[i].SB_wid_prt->set_button_state(true);
        else SBstore[i].SB_wid_prt->set_button_state(false);
    }

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
    for (int i=0; i<MAX_POVS; i++) {
        QLabel *povLabel = ui->tabWidget->findChild<QLabel *>(name_template.arg(i+1));
        switch (gamepad_report.pov[i]) {
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

    get_all_A2B_buttons();
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

void OSHStudio::get_all_SB_buttons(){
    pov1=0;
    pov2=0;
    pov3=0;
    pov4=0;
    ui->label_POV1->setVisible(false);
    ui->label_POV2->setVisible(false);
    ui->label_POV3->setVisible(false);
    ui->label_POV4->setVisible(false);
    ui->label_POV1name->setVisible(false);
    ui->label_POV2name->setVisible(false);
    ui->label_POV3name->setVisible(false);
    ui->label_POV4name->setVisible(false);
    for(int i=0; i < TotalButtons; i++){
        SBstore[i].button_type = SBstore[i].SB_wid_prt->get_button_type();
        if ((SBstore[i].button_type == pov1up_button) ||
                (SBstore[i].button_type == pov1down_button) ||
                (SBstore[i].button_type == pov1left_button) ||
                (SBstore[i].button_type == pov1right_button)) pov1++;
        if ((SBstore[i].button_type == pov2up_button) ||
                (SBstore[i].button_type == pov2down_button) ||
                (SBstore[i].button_type == pov2left_button) ||
                (SBstore[i].button_type == pov2right_button)) pov2++;
        if ((SBstore[i].button_type == pov3up_button) ||
                (SBstore[i].button_type == pov3down_button) ||
                (SBstore[i].button_type == pov3left_button) ||
                (SBstore[i].button_type == pov3right_button)) pov3++;
        if ((SBstore[i].button_type == pov4up_button) ||
                (SBstore[i].button_type == pov4down_button) ||
                (SBstore[i].button_type == pov4left_button) ||
                (SBstore[i].button_type == pov4right_button)) pov4++;
        if (i<MAX_BUTTONS/2) {
            config.buttons_types1st[i] = SBstore[i].button_type;
        } else {
            config.buttons_types2nd[i-MAX_BUTTONS/2] = SBstore[i].button_type;
        }
     }
    if (pov1) {
        ui->label_POV1->setVisible(true);
        ui->label_POV1name->setVisible(true);
    }
    if (pov2) {
        ui->label_POV2->setVisible(true);
        ui->label_POV2name->setVisible(true);
    }
    if (pov3) {
        ui->label_POV3->setVisible(true);
        ui->label_POV3name->setVisible(true);
    }
    if (pov4) {
        ui->label_POV4->setVisible(true);
        ui->label_POV4name->setVisible(true);
    }
    drawHelpSB();
}

void OSHStudio::populateDefSB(){
    for(int i=0; i < MAX_BUTTONS; i++){
       // SBstore[i] -> setVisible(true);
        SBstore[i].SB_wid_prt->setVisible(false);
     }

    for(int i=0; i < TotalButtons; i++){
       // SBstore[i] -> setVisible(true);
        SBstore[i].SB_wid_prt->setVisible(true);
     }
    get_all_SB_buttons();
}

void OSHStudio::showA2Btab(){
    ui->label_ZeroA2B->setVisible(config.analog_2_button_inputs ? false : true);
   // QString name_template_A2B("widget_A2B_%1");
    for(int i=0; i < MAX_A2B_INPUTS; i++){
        A2Bstore[i].widget_ptr->setVisible(false);
     }

    for(uint8_t i=0; i<config.analog_2_button_inputs; i++){
        A2Bstore[i].widget_ptr->setVisible(true);
        A2Bstore[i].widget_ptr->setPinName(pin_names[A2Bstore[i].pin_number]);
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
    for(uint8_t i =0; i < MAX_SINGLE_ENCODERS; i++){
        oshsingenc *SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i+1));
        SEwid->setVisible(false);
        SEwid->clearPinsLists();
     }
    for(uint8_t i =0; i < config.total_single_encoders; i++){
        oshsingenc *SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i+1));
        SEwid->setVisible(true);
        for (uint8_t i=0; i<config.total_single_encoders; i++){
            SEwid->addPins2Lists(config.single_encoder_pinA[i], config.single_encoder_pinB[i],
                                 config.pin[config.single_encoder_pinA[i]]);
        }
        SEwid->setPinsPair(i);
     }
}

void OSHStudio::get_all_A2B_buttons(void){
        A2BButtons = 0;

    config.analog_2_button_inputs = Analog2Buttons_inputs;
    for (uint8_t i=0; i<Analog2Buttons_inputs; i++){
        A2BButtons += A2Bstore[i].widget_ptr->getButtonsCount();
        if (i<5){
            config.a2b_1st5[i].buttons_number = A2Bstore[i].widget_ptr->getButtonsCount();
            A2Bstore[i].widget_ptr->getButtonsIntervals(config.a2b_1st5[i].buttons_intervals);
        } else {
            config.a2b_2nd5[i-(MAX_A2B_INPUTS/2)].buttons_number = A2Bstore[i].widget_ptr->getButtonsCount();
            A2Bstore[i].widget_ptr->getButtonsIntervals(config.a2b_2nd5[i-(MAX_A2B_INPUTS/2)].buttons_intervals);
        }
    }

    TotalButtons =  (ButtonsRows * ButtonsColumns) +
                    (RotSwitchPoles * RotSwitchWires) +
                    (Single_Rotaries_PINA_1*2 + Single_Rotaries_PINB_2*2 + Single_Rotaries_PINA_4*2) +
                    Chain_Rotaries_1*2 + Chain_Rotaries_2*2 +
                    A2BButtons +
                    Buttons;
    TotalButtons = (TotalButtons > MAX_BUTTONS) ? MAX_BUTTONS : TotalButtons;
    populateDefSB();
    drawHelp();
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
    populateDefSB();
    drawHelp();
}
