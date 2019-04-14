#include "oshstudio.h"
#include "ui_oshstudio.h"
#include<QMessageBox>
#include <QMutex>

extern hid_device *handle_read;//, *handle_write;

void OSHStudio::gatherConfig_Slot(){
    config.pin[0] = ui->widget_PB0->get_current_index();
    config.pin[1] = ui->widget_PB1->get_current_index();
    config.pin[2] = ui->widget_PB2->get_current_index();
    config.pin[3] = ui->widget_PB3->get_current_index();
    config.pin[4] = ui->widget_PB4->get_current_index();
    config.pin[5] = ui->widget_PB5->get_current_index();
    config.pin[6] = ui->widget_PB6->get_current_index();
    config.pin[7] = ui->widget_PB7->get_current_index();
    config.pin[8] = ui->widget_PB8->get_current_index();
    config.pin[9] = ui->widget_PB9->get_current_index();
    config.pin[10] = ui->widget_PB10->get_current_index();
    config.pin[11] = ui->widget_PB11->get_current_index();
    config.pin[12] = ui->widget_PB12->get_current_index();
    config.pin[13] = ui->widget_PB13->get_current_index();
    config.pin[14] = ui->widget_PB14->get_current_index();
    config.pin[15] = ui->widget_PB15->get_current_index();
    config.pin[16] = ui->widget_PB16->get_current_index();
    config.pin[17] = ui->widget_PB17->get_current_index();
    config.pin[18] = ui->widget_PB18->get_current_index();
    config.pin[19] = ui->widget_PB19->get_current_index();
    config.pin[20] = ui->widget_PB20->get_current_index();
    config.pin[21] = ui->widget_PB21->get_current_index();
    config.pin[22] = ui->widget_PB22->get_current_index();
    config.pin[23] = ui->widget_PB23->get_current_index();
    config.pin[24] = ui->widget_PB24->get_current_index();
    config.pin[25] = ui->widget_PB25->get_current_index();
    config.pin[26] = ui->widget_PB26->get_current_index();
    config.pin[27] = ui->widget_PB27->get_current_index();
    config.pin[28] = ui->widget_PB28->get_current_index();
    config.pin[29] = ui->widget_PB29->get_current_index();
    config.pin[30] = ui->widget_PB30->get_current_index();
    config.pin[31] = ui->widget_PB31->get_current_index();

    config.axes[0].axis_min_calib_value = ui->widget_axis1->LeftPinValue();
    config.axes[0].axis_max_calib_value = ui->widget_axis1->RightPinValue();
    config.axes[0].axis_autocalibrate = (uint8_t)ui->widget_axis1->isAutoCalibEnabled();
    config.axes[1].axis_min_calib_value = ui->widget_axis2->LeftPinValue();
    config.axes[1].axis_max_calib_value = ui->widget_axis2->RightPinValue();
    config.axes[1].axis_autocalibrate = (uint8_t)ui->widget_axis2->isAutoCalibEnabled();
    config.axes[2].axis_min_calib_value = ui->widget_axis3->LeftPinValue();
    config.axes[2].axis_max_calib_value = ui->widget_axis3->RightPinValue();
    config.axes[2].axis_autocalibrate = (uint8_t)ui->widget_axis3->isAutoCalibEnabled();
    config.axes[3].axis_min_calib_value = ui->widget_axis4->LeftPinValue();
    config.axes[3].axis_max_calib_value = ui->widget_axis4->RightPinValue();
    config.axes[3].axis_autocalibrate = (uint8_t)ui->widget_axis4->isAutoCalibEnabled();
    config.axes[4].axis_min_calib_value = ui->widget_axis5->LeftPinValue();
    config.axes[4].axis_max_calib_value = ui->widget_axis5->RightPinValue();
    config.axes[4].axis_autocalibrate = (uint8_t)ui->widget_axis5->isAutoCalibEnabled();
    config.axes[5].axis_min_calib_value = ui->widget_axis6->LeftPinValue();
    config.axes[5].axis_max_calib_value = ui->widget_axis6->RightPinValue();
    config.axes[5].axis_autocalibrate = (uint8_t)ui->widget_axis6->isAutoCalibEnabled();

    config.rotary_press_time = ui->spinBox__Rot_Press_time->value();
    config.rotary_debounce_time = ui->spinBox_Rot_Debounce_time->value();
    config.button_debounce_time = ui->spinBox_Button_Debounce_time->value();
    config.usb_exchange_rate = ui->spinBox_USB_exchange->value();
    config.rotswitch_press_time = ui->spinBox_RotSwitch_Press_time->value();

    memcpy(config.usb_ps_uniq,ui->lineEdit_Device_ident->text().toLatin1(),ui->lineEdit_Device_ident->text().toLatin1().size());

    if (ui->checkBox_AxisComb->isChecked()) {
        config.combined_axis_enabled = 1;
        config.combined_axis1_mincalib_value = ui->widget_axisComb1->LeftPinValue();
        config.combined_axis1_maxcalib_value = ui->widget_axisComb1->RightPinValue();
        config.combined_axis2_mincalib_value = ui->widget_axisComb2->LeftPinValue();
        config.combined_axis2_maxcalib_value = ui->widget_axisComb2->RightPinValue();
        if (ui->widget_axisComb1->isAutoCalibEnabled()) config.combined_axis_pin1_autocalib = 1;
        if (ui->widget_axisComb2->isAutoCalibEnabled()) config.combined_axis_pin2_autocalib= 1;
        if (ui->radioButtonCoopwoork->isChecked()) config.combined_axis_cooperate = 1;
        if (ui->radioButtonEachonhisown->isChecked()) config.combined_axis_separate = 1;
        config.combined_axis_percent = ui->horizontalSliderAxisComb->value();
        config.combined_axis_pin1 = convertPinnameToIndex(ui->comboBox_AxisCombBegin->currentText());
        config.combined_axis_pin2 = convertPinnameToIndex(ui->comboBox_AxisCombEnd->currentText());
    } else {
        config.combined_axis_enabled = 0;
    }



    config.POV_config = 0;
//    if (ui->checkBox_POV1->isChecked()) config.POV_config |= 0x1;
//    if (ui->checkBox_POV2->isChecked()) config.POV_config |= 0x2;
//    if (ui->checkBox_POV3->isChecked()) config.POV_config |= 0x4;
//    if (ui->checkBox_POV4->isChecked()) config.POV_config |= 0x8;

    config.rotswitch_min_time = ui->spinBox_RotSwitch_min_time->value();

    config.analog_2_button_min_time = ui->spinBox_A2B_min_time->value();
    config.analog_2_button_press_time = ui->spinBox_A2B_Press_time->value();

    config.analog_2_button_inputs = Analog2Buttons_inputs;
    for (uint8_t i=0; i<Analog2Buttons_inputs; i++){
        if (i<5){
            config.a2b_1st5[i].buttons_number = A2Bstore[i].widget_ptr->getButtonsCount();
            A2Bstore[i].widget_ptr->getButtonsIntervals(config.a2b_1st5[i].buttons_intervals);
        } else {
            config.a2b_2nd5[i-(MAX_A2B_INPUTS/2)].buttons_number = A2Bstore[i].widget_ptr->getButtonsCount();
            A2Bstore[i].widget_ptr->getButtonsIntervals(config.a2b_2nd5[i-(MAX_A2B_INPUTS/2)].buttons_intervals);
        }
    }

    get_all_A2B_buttons();
    get_all_SB_buttons();

    QString name_template_SE("widget_SE%1");
    oshsingenc *SEwid;
    for(int i =0; i < config.total_single_encoders; i++){
        SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i+1));
        config.single_encoder_pinA[i] = SEwid->getPinA();
        config.single_encoder_pinB[i] = SEwid->getPinB();
    }

    QString name_template_SH("comboBox_shape_axis_%1");
    QString name_template_SW("widget_AS_%1");
    QComboBox *SHwid = nullptr;
    oshshapesw *SWwid = nullptr;
    uint8_t tmp[10] = {0};
    for(uint8_t i =0; i < MAX_AXES; i++){
        SHwid = ui->tabWidget->findChild<QComboBox *>(name_template_SH.arg(i+1));
        memcpy(config.profile_names[i],tmp,10);
        memcpy(config.profile_names[i],SHwid->itemText(i).toLatin1().data(),SHwid->itemText(i).toLatin1().size());
        SWwid = ui->tabWidget->findChild<oshshapesw *>(name_template_SW.arg(i+1));
        SWwid->getAllPoints(axes_shapes[i],SHAPEVALUES);
     }
     config.axes[0].axis_profile = ui->comboBox_shape_axis_1->currentIndex();
     config.axes[1].axis_profile = ui->comboBox_shape_axis_2->currentIndex();
     config.axes[2].axis_profile = ui->comboBox_shape_axis_3->currentIndex();
     config.axes[3].axis_profile = ui->comboBox_shape_axis_4->currentIndex();
     config.axes[4].axis_profile = ui->comboBox_shape_axis_5->currentIndex();
     config.axes[5].axis_profile = ui->comboBox_shape_axis_6->currentIndex();

    for (uint8_t i=0; i<MAX_AXES; i++) {
        for (uint8_t j=0; j<10; j++) {
            if (i<MAX_AXES/2) config.axes_shapes1[i][j] = axes_shapes[i][j];
            else config.axes_shapes2[i-MAX_AXES/2][j] = axes_shapes[i][j];
        }
    }
}

void OSHStudio::writeConfig_Slot()
{
    uint8_t buf[BUFFSIZE]={0};

    gatherConfig_Slot();

    config.packet_id1 = 2;
    config.operation_code1 = 1;
    config_mode = true;

    memcpy(buf, &(config.packet_id1), BUFFSIZE);
    hid_write(handle_read, buf, BUFFSIZE);
}

void OSHStudio::setConfig_Slot(){

    QString name_template("widget_PB%1");
    for(int i = 0; i < 32; i++) {
       oshpincombobox *pinComboBox = ui->tabWidget->findChild<oshpincombobox *>(name_template.arg(i));
       pinComboBox->blockSignals(true);
       pinComboBox->set_current_index(config.pin[i]);
       pinComboBox->blockSignals(false);
    }

        ui->widget_axis1->setMinCalibValue(config.axes[0].axis_min_calib_value);
        ui->widget_axis1->setMaxCalibValue(config.axes[0].axis_max_calib_value);
        ui->widget_axis1->setAutoCalib(config.axes[0].axis_autocalibrate);

        ui->widget_axis2->setMinCalibValue(config.axes[1].axis_min_calib_value);
        ui->widget_axis2->setMaxCalibValue(config.axes[1].axis_max_calib_value);
        ui->widget_axis2->setAutoCalib(config.axes[1].axis_autocalibrate);

        ui->widget_axis3->setMinCalibValue(config.axes[2].axis_min_calib_value);
        ui->widget_axis3->setMaxCalibValue(config.axes[2].axis_max_calib_value);
        ui->widget_axis3->setAutoCalib(config.axes[2].axis_autocalibrate);

        ui->widget_axis4->setMinCalibValue(config.axes[3].axis_min_calib_value);
        ui->widget_axis4->setMaxCalibValue(config.axes[3].axis_max_calib_value);
        ui->widget_axis4->setAutoCalib(config.axes[3].axis_autocalibrate);

        ui->widget_axis5->setMinCalibValue(config.axes[4].axis_min_calib_value);
        ui->widget_axis5->setMaxCalibValue(config.axes[4].axis_max_calib_value);
        ui->widget_axis5->setAutoCalib(config.axes[4].axis_autocalibrate);

        ui->widget_axis6->setMinCalibValue(config.axes[5].axis_min_calib_value);
        ui->widget_axis6->setMaxCalibValue(config.axes[5].axis_max_calib_value);
        ui->widget_axis6->setAutoCalib(config.axes[5].axis_autocalibrate);

        ui->spinBox__Rot_Press_time->setValue(config.rotary_press_time);
        ui->spinBox_Rot_Debounce_time->setValue(config.rotary_debounce_time);
        ui->spinBox_Button_Debounce_time->setValue(config.button_debounce_time);
        ui->spinBox_USB_exchange->setValue(config.usb_exchange_rate);
        ui->spinBox_RotSwitch_Press_time->setValue(config.rotswitch_press_time);

        ui->lineEdit_Device_ident->setText(QString::fromLocal8Bit((char*)config.usb_ps_uniq,10));

        if (config.combined_axis_enabled){
            ui->widget_axisComb1->setMinCalibValue(config.combined_axis1_mincalib_value);
            ui->widget_axisComb1->setMaxCalibValue(config.combined_axis1_maxcalib_value);
            ui->widget_axisComb2->setMinCalibValue(config.combined_axis2_mincalib_value);
            ui->widget_axisComb2->setMaxCalibValue(config.combined_axis2_maxcalib_value);

            ui->widget_axisComb1->setAutoCalib(config.combined_axis_pin1_autocalib);
            ui->widget_axisComb2->setAutoCalib(config.combined_axis_pin2_autocalib);
            if (config.combined_axis_cooperate) ui->radioButtonCoopwoork->setChecked(true);
                else ui->radioButtonEachonhisown->setChecked(true);
            ui->horizontalSliderAxisComb->setValue(config.combined_axis_percent);
            ui->comboBox_AxisCombBegin->setCurrentText(pin_names[config.combined_axis_pin1]);
            ui->comboBox_AxisCombEnd->setCurrentText(pin_names[config.combined_axis_pin2]);
            ui->checkBox_AxisComb->setChecked(true);
        } else {
            ui->checkBox_AxisComb->setChecked(false);
        }


//        if (config.POV_config & 0x1) ui->checkBox_POV1->setChecked(true);
//            else ui->checkBox_POV1->setChecked(false);
//        if (config.POV_config & 0x2) ui->checkBox_POV2->setChecked(true);
//            else ui->checkBox_POV2->setChecked(false);
//        if (config.POV_config & 0x4) ui->checkBox_POV3->setChecked(true);
//            else ui->checkBox_POV3->setChecked(false);
//        if (config.POV_config & 0x8) ui->checkBox_POV4->setChecked(true);
//            else ui->checkBox_POV4->setChecked(false);


        ui->spinBox_RotSwitch_min_time->setValue(config.rotswitch_min_time);

        ui->spinBox_A2B_min_time->setValue(config.analog_2_button_min_time);
        ui->spinBox_A2B_Press_time->setValue(config.analog_2_button_press_time);

        for (uint8_t i=0;i<MAX_BUTTONS/2;i++){
            SBstore[i].button_type=(button_mode)config.buttons_types1st[i];
        }
        for (uint8_t i=MAX_BUTTONS/2;i<MAX_BUTTONS;i++){
            SBstore[i].button_type=(button_mode)config.buttons_types2nd[i-MAX_BUTTONS/2];
        }
        for (uint8_t i=0; i<MAX_BUTTONS; i++){
            SBstore[i].SB_wid_prt->set_button_type(SBstore[i].button_type);
        }

        for (uint8_t i=0; i<MAX_AXES; i++) {
            for (uint8_t j=0; j<10; j++) {
                if (i<MAX_AXES/2) axes_shapes[i][j] = config.axes_shapes1[i][j];
                        else axes_shapes[i][j] = config.axes_shapes2[i-MAX_AXES/2][j];
            }
        }

        setShapesW();
        ui->comboBox_shape_axis_1->setCurrentIndex(config.axes[0].axis_profile);
        ui->comboBox_shape_axis_2->setCurrentIndex(config.axes[1].axis_profile);
        ui->comboBox_shape_axis_3->setCurrentIndex(config.axes[2].axis_profile);
        ui->comboBox_shape_axis_4->setCurrentIndex(config.axes[3].axis_profile);
        ui->comboBox_shape_axis_5->setCurrentIndex(config.axes[4].axis_profile);
        ui->comboBox_shape_axis_6->setCurrentIndex(config.axes[5].axis_profile);

        gatherPinsConf();
        showSingleEncodersTab();
        showA2Btab();
        drawHelp();

        // show stored config version
        QString firmware_correctness="";
        if (!config.config_version) ui->label_Firmware_Vers->setText("") ;
                 else ui->label_Firmware_Vers->setText("0."+QString::number(config.config_version));
         if (config.config_version == OSHSTUDIOVERSION) {
             firmware_correctness="color : green";
         } else {
             firmware_correctness="color : red";
             }
         ui->label_Firmware_Vers->setStyleSheet(firmware_correctness);
         ui->label_58->setStyleSheet(firmware_correctness);
         ui->label_34->setStyleSheet(firmware_correctness);
         ui->label_Stud_version->setStyleSheet(firmware_correctness);

}

void OSHStudio::resetConfig_Slot(){

    for (uint8_t i=0; i<USEDPINS; i++){
        config.pin[i] = Not_Used;
    }

    resetConfigValues();
    setConfig_Slot();
}

void OSHStudio::restoreConfig_Slot(){

    config.pin[0] = AnalogMedSmooth;
    config.pin[1] = AnalogMedSmooth;
    config.pin[2] = AnalogMedSmooth;
    config.pin[3] = AnalogMedSmooth;
    config.pin[4] = AnalogMedSmooth;
    config.pin[5] = AnalogMedSmooth;
    config.pin[6] = Chain_Rotary_Enc_1;
    config.pin[7] = Button_COLUMN;
    config.pin[8] = Chain_Rotary_Enc_1;
    config.pin[9] = Chain_Rotary_Enc_1;
    config.pin[10] = Chain_Rotary_Enc_1;
    config.pin[11] = Not_Used;
    config.pin[12] = Not_Used;
    config.pin[13] = Chain_Rotary_Enc_1;
    config.pin[14] = Chain_Rotary_Enc_1;
    config.pin[15] = Chain_Rotary_Enc_1;
    config.pin[16] = Button_COLUMN;
    config.pin[17] = Button_ROW;
    config.pin[18] = Button_ROW;
    config.pin[19] = Button_ROW;
    config.pin[20] = Button_ROW;
    config.pin[21] = Button_ROW;
    config.pin[22] = Button_ROW;
    config.pin[23] = Chain_Rotary_PINA;
    config.pin[24] = Chain_Rotary_PINB;
    config.pin[25] = Button_COLUMN;
    config.pin[26] = Chain_Rotary_Enc_1;
    config.pin[27] = Chain_Rotary_Enc_1;
    config.pin[28] = Chain_Rotary_Enc_1;
    config.pin[29] = Button_COLUMN;
    config.pin[30] = Button_COLUMN;
    config.pin[31] = Button_COLUMN;

    resetConfigValues();
    setConfig_Slot();
}

void OSHStudio::resetConfigValues(void){
    config.config_version = OSHSTUDIOVERSION;
    for (uint8_t i=0; i<MAX_AXES; i++){
        config.axes[i].axis_min_calib_value = 0;
        config.axes[i].axis_max_calib_value = 4095;
        config.axes[i].axis_autocalibrate = 0;
        config.axes[i].axis_profile = 0;
    }

    config.rotary_press_time = 100;
    config.rotary_debounce_time = 50;
    config.rotswitch_press_time = 100;
    config.button_debounce_time = 50;
    config.combined_axis1_mincalib_value = 0;
    config.combined_axis1_maxcalib_value = 4095;
    config.combined_axis2_mincalib_value = 0;
    config.combined_axis2_maxcalib_value = 4095;

    for (uint8_t i=0;i<10;++i){
        config.usb_ps_uniq[i] = 0;
    }

    config.usb_exchange_rate = 16;
    config.combined_axis_enabled = 0;
    config.combined_axis_cooperate = 1;
    config.combined_axis_separate = 0;
    config.combined_axis_pin1_autocalib = 0;
    config.combined_axis_pin2_autocalib = 0;

    config.total_single_encoders = 0;
    for (uint8_t i=0;i<MAX_SINGLE_ENCODERS;++i){
        config.single_encoder_pinA[i] = 0;
        config.single_encoder_pinB[i] = 0;
    }


    config.POV_config = 0;
    config.combined_axis_percent = 50;
    config.combined_axis_pin1 = 4;
    config.combined_axis_pin2 = 5;

    config.analog_2_button_inputs = 0;
    config.analog_2_button_min_time = 0;
    config.analog_2_button_press_time = 100;
    resetAllA2B();
    config.rotswitch_min_time = 0;

    for (uint8_t i=0; i<MAX_BUTTONS/2; i++){
        config.buttons_types1st[i] = joystick_button;
    }
    for (uint8_t i=0; i<MAX_BUTTONS/2; i++){
        config.buttons_types2nd[i] = joystick_button;
    }

    uint8_t tmp_profile_names[MAX_AXES][10] = {
        {'L','i','n','e','a','r',0},
        {'E','x','p','o','n','e','n','t','1',0},
        {'E','x','p','o','n','e','n','t','2',0},
        {'S','h','a','p','e','1',0},
        {'S','h','a','p','e','2',0},
        {'I','n','v','e','r','t','e','d',0},
    };
    uint16_t tmp_axes_shapes[MAX_AXES][SHAPEVALUES] = {
        {0x000, 0x1D0, 0x3A0, 0x550, 0x720, 0x8C0, 0xAA0, 0xC40, 0xE40, 0xFFF}, //linear
        {0x000, 0x580, 0x9C0, 0xC40, 0xE10, 0xF10, 0xF80, 0xFFF, 0xFFF, 0xFFF}, //exp1
        {0x000, 0x000, 0x000, 0x000, 0x060, 0x130, 0x270, 0x440, 0x860, 0xFFF}, //exp2
        {0x000, 0x000, 0x060, 0x1A0, 0x4B0, 0xB70, 0xE40, 0xFB0, 0xFFF, 0xFFF}, //shape1
        {0x000, 0x440, 0x650, 0x780, 0x7C0, 0x7F0, 0x860, 0x960, 0xBD0, 0xFFF}, //shape2
        {0xFFF, 0xE40, 0xC40, 0xAA0, 0x8C0, 0x720, 0x550, 0x3A0, 0x1D0, 0x000}, //inverted
    };

    for (uint8_t i=0; i<MAX_AXES; i++) {
        for (uint8_t j=0; j<10; j++) {
            config.profile_names[i][j] = tmp_profile_names[i][j];
            axes_shapes[i][j] = tmp_axes_shapes[i][j];
            if (i<MAX_AXES/2) config.axes_shapes1[i][j] = tmp_axes_shapes[i][j];
            else config.axes_shapes2[i-MAX_AXES/2][j] = tmp_axes_shapes[i][j];
        }
    }
}

void OSHStudio::getConfig_Slot()
{
    uint8_t bufrep2[2]={3,1};
    config_mode = true;

    hid_write(handle_read, bufrep2, 2);
}


void OSHStudio::getConfigPacket(uint8_t * buf){
    uint8_t next_req[BUFFSIZE]={3,0};
    static QMutex mutex_for_load;

    if (buf[0] == 4) {
        switch (buf[1]){
        case (sizeof(total_config_)/BUFFSIZE): {
            memcpy((&(config.packet_id1)+(BUFFSIZE*(buf[1]-1))), buf, BUFFSIZE);
            next_req[1]=0xFF; // EOT flag
            hid_write(handle_read, next_req, BUFFSIZE);
            config_mode = false;
            if(mutex_for_load.tryLock()) {
                if (config.config_version != OSHSTUDIOVERSION) {
                    QMessageBox::warning(this, tr("Nope!"),
                                     tr("It seems the board has wrong FW version"));
                } else {
                    setConfig_Slot();
                    QMessageBox::information(this, tr("Success!"),
                                         tr("Board's config loaded successfully."));
                }
                mutex_for_load.unlock();
                }
            }
            break;
        default: {
            if (buf[1] < sizeof(total_config_)/BUFFSIZE) {
                memcpy((&(config.packet_id1)+(BUFFSIZE*(buf[1]-1))), buf, BUFFSIZE);
                next_req[1]=buf[1]+1;
                hid_write(handle_read, next_req, BUFFSIZE);
                }
            }
        break;
        }
    }
}

void OSHStudio::getACKpacket(uint8_t * buf_recieved){
    uint8_t buf[BUFFSIZE] = {0};
    static QMutex mutex_for_save;

    config.packet_id1 = 2;
    config.packet_id2 = 2;
    config.packet_id3 = 2;
    config.packet_id4 = 2;
    config.packet_id5 = 2;
    config.packet_id6 = 2;
    config.packet_id7 = 2;
    config.packet_id8 = 2;
    config.packet_id9 = 2;
    config.operation_code1 = 1;
    config.operation_code2 = 2;
    config.operation_code3 = 3;
    config.operation_code4 = 4;
    config.operation_code5 = 5;
    config.operation_code6 = 6;
    config.operation_code7 = 7;
    config.operation_code8 = 8;
    config.operation_code9 = 9;

    uint8_t confirmed_packet = buf_recieved[1];
    switch(confirmed_packet){
    case (sizeof(total_config_)/BUFFSIZE): {
            buf[0] = 2;
            buf[1] = 255; //EOT marker
            hid_write(handle_read, buf, BUFFSIZE);
            config_mode = false;
            if(mutex_for_save.tryLock()) {
                QMessageBox::information(this, tr("Success!"),
                                         tr("Config saved successfully to the board"));
                mutex_for_save.unlock();
            }
            break;
        }
    default: {
            if (confirmed_packet < sizeof(total_config_)/BUFFSIZE) {
                memcpy(buf, (&(config.packet_id1)+(BUFFSIZE*confirmed_packet)), BUFFSIZE);
                hid_write(handle_read, buf, BUFFSIZE);
            }
            break;
        }
    }
}

void OSHStudio::write_config_packet(void){
    static uint8_t i=0;
    if (!config_mode){
        if (!(i++%10)){
            const uint8_t hb_packet[BUFFSIZE] = {2,254,0};
            hid_write(handle_read, hb_packet, BUFFSIZE);
        }
    }
}
