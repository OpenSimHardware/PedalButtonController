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
    config.axes[0].axis_special = (uint8_t)ui->widget_axis1->isAutoCalibEnabled();
    config.axes[1].axis_min_calib_value = ui->widget_axis2->LeftPinValue();
    config.axes[1].axis_max_calib_value = ui->widget_axis2->RightPinValue();
    config.axes[1].axis_special = (uint8_t)ui->widget_axis2->isAutoCalibEnabled();
    config.axes[2].axis_min_calib_value = ui->widget_axis3->LeftPinValue();
    config.axes[2].axis_max_calib_value = ui->widget_axis3->RightPinValue();
    config.axes[2].axis_special = (uint8_t)ui->widget_axis3->isAutoCalibEnabled();
    config.axes[3].axis_min_calib_value = ui->widget_axis4->LeftPinValue();
    config.axes[3].axis_max_calib_value = ui->widget_axis4->RightPinValue();
    config.axes[3].axis_special = (uint8_t)ui->widget_axis4->isAutoCalibEnabled();
    config.axes[4].axis_min_calib_value = ui->widget_axis5->LeftPinValue();
    config.axes[4].axis_max_calib_value = ui->widget_axis5->RightPinValue();
    config.axes[4].axis_special = (uint8_t)ui->widget_axis5->isAutoCalibEnabled();
    config.axes[5].axis_min_calib_value = ui->widget_axis6->LeftPinValue();
    config.axes[5].axis_max_calib_value = ui->widget_axis6->RightPinValue();
    config.axes[5].axis_special = (uint8_t)ui->widget_axis6->isAutoCalibEnabled();

    config.rotary_press_time = ui->spinBox__Rot_Press_time->value();
    config.rotary_debounce_time = ui->spinBox_Rot_Debounce_time->value();
    config.button_debounce_time = ui->spinBox_Button_Debounce_time->value();
    config.usb_exchange_rate = ui->spinBox_USB_exchange->value();
    config.rotswitch_press_time = ui->spinBox_RotSwitch_Press_time->value();

    memcpy(config.usb_ps_uniq,ui->lineEdit_Device_ident->text().toLatin1(),10);

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
    if (ui->checkBox_POV1->isChecked()) config.POV_config |= 0x1;
    if (ui->checkBox_POV2->isChecked()) config.POV_config |= 0x2;
    if (ui->checkBox_POV3->isChecked()) config.POV_config |= 0x4;
    if (ui->checkBox_POV4->isChecked()) config.POV_config |= 0x8;

    config.analog_2_button_threshold = ui->horiSlider_A2B->value();
    config.rotswitch_min_time = ui->spinBox_RotSwitch_min_time->value();

    QString name_template_SE("widget_SE%1");
    oshsingenc *SEwid;
    for(int i =0; i < config.total_single_encoders; i++){
        SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i+1));
        config.single_encoder_pinA[i] = SEwid->getPinA();
        config.single_encoder_pinB[i] = SEwid->getPinB();
    }
}

void OSHStudio::writeConfig_Slot()
{
    uint8_t buf[BUFFSIZE]={0};

    gatherConfig_Slot();

    config.packet_id1 = 2;
    config.operation_code1 = 1;

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
        ui->widget_axis1->setAutoCalib(config.axes[0].axis_special);

        ui->widget_axis2->setMinCalibValue(config.axes[1].axis_min_calib_value);
        ui->widget_axis2->setMaxCalibValue(config.axes[1].axis_max_calib_value);
        ui->widget_axis2->setAutoCalib(config.axes[1].axis_special);

        ui->widget_axis3->setMinCalibValue(config.axes[2].axis_min_calib_value);
        ui->widget_axis3->setMaxCalibValue(config.axes[2].axis_max_calib_value);
        ui->widget_axis3->setAutoCalib(config.axes[2].axis_special);

        ui->widget_axis4->setMinCalibValue(config.axes[3].axis_min_calib_value);
        ui->widget_axis4->setMaxCalibValue(config.axes[3].axis_max_calib_value);
        ui->widget_axis4->setAutoCalib(config.axes[3].axis_special);

        ui->widget_axis5->setMinCalibValue(config.axes[4].axis_min_calib_value);
        ui->widget_axis5->setMaxCalibValue(config.axes[4].axis_max_calib_value);
        ui->widget_axis5->setAutoCalib(config.axes[4].axis_special);

        ui->widget_axis6->setMinCalibValue(config.axes[5].axis_min_calib_value);
        ui->widget_axis6->setMaxCalibValue(config.axes[5].axis_max_calib_value);
        ui->widget_axis6->setAutoCalib(config.axes[5].axis_special);

        ui->spinBox__Rot_Press_time->setValue(config.rotary_press_time);
        ui->spinBox_Rot_Debounce_time->setValue(config.rotary_debounce_time);
        ui->spinBox_Button_Debounce_time->setValue(config.button_debounce_time);
        ui->spinBox_USB_exchange->setValue(config.usb_exchange_rate);
        ui->spinBox_RotSwitch_Press_time->setValue(config.rotswitch_press_time);

        ui->lineEdit_Device_ident->setText(QString::fromLocal8Bit((char*)config.usb_ps_uniq));

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


        if (config.POV_config & 0x1) ui->checkBox_POV1->setChecked(true);
            else ui->checkBox_POV1->setChecked(false);
        if (config.POV_config & 0x2) ui->checkBox_POV2->setChecked(true);
            else ui->checkBox_POV2->setChecked(false);
        if (config.POV_config & 0x4) ui->checkBox_POV3->setChecked(true);
            else ui->checkBox_POV3->setChecked(false);
        if (config.POV_config & 0x8) ui->checkBox_POV4->setChecked(true);
            else ui->checkBox_POV4->setChecked(false);


        ui->horiSlider_A2B->setValue(config.analog_2_button_threshold);
        ui->spinBox_RotSwitch_min_time->setValue(config.rotswitch_min_time);

        gatherPinsConf();
        showSingleEncodersTab();
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
    config.config_version = OSHSTUDIOVERSION;
    for (uint8_t i=0; i<MAX_AXES; i++){
        config.axes[i].axis_min_calib_value = 0;
        config.axes[i].axis_max_calib_value = 4095;
        config.axes[i].axis_special = 0;
    }

    for (uint8_t i=0; i<USEDPINS; i++){
        config.pin[i] = Not_Used;
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

    config.analog_2_button_threshold = 2048;
    config.rotswitch_min_time = 0;

    setConfig_Slot();
}

void OSHStudio::restoreConfig_Slot(){
    config.config_version = OSHSTUDIOVERSION;
    for (uint8_t i=0;i<MAX_AXES;i++){
        config.axes[i].axis_min_calib_value = 0;
        config.axes[i].axis_max_calib_value = 4095;
        config.axes[i].axis_special = 0;
    }

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

    config.analog_2_button_threshold = 2048;
    config.rotswitch_min_time = 0;

    setConfig_Slot();
}

void OSHStudio::getConfig_Slot()
{
    uint8_t bufrep2[2]={3,1};

    hid_write(handle_read, bufrep2, 2);
}


void OSHStudio::getConfigPacket(uint8_t * buf){
    uint8_t next_req[BUFFSIZE]={3,0};
    static QMutex mutex_for_load;
    switch (buf[1]){
    case 1: {
        memcpy(&(config.packet_id1), buf, BUFFSIZE);
        next_req[1]=2;
        hid_write(handle_read, next_req, BUFFSIZE);
        break;
        }
    case 2: {
        memcpy(&(config.packet_id2), buf, BUFFSIZE);
        next_req[1]=3;
        hid_write(handle_read, next_req, BUFFSIZE);
        break;
        }
    case 3: {
        memcpy(&(config.packet_id3), buf, BUFFSIZE);
        next_req[1]=0xFF; // EOT flag
        hid_write(handle_read, next_req, BUFFSIZE);
        if(mutex_for_load.tryLock()) {
            if (config.config_version != OSHSTUDIOVERSION) {
                QMessageBox::warning(this, tr("Nope!"),
                                     tr("Its seems board has wrong FW version"));
            } else {
                setConfig_Slot();
                QMessageBox::information(this, tr("Success!"),
                                         tr("Board's config loaded successfully."));
                }
            mutex_for_load.unlock();
            }
        break;
        }
    }
}

void OSHStudio::getACKpacket(uint8_t confirmed_packet){
    uint8_t buf[BUFFSIZE] = {0};
    static QMutex mutex_for_save;

    config.packet_id1 = 2;
    config.packet_id2 = 2;
    config.packet_id3 = 2;
    config.operation_code1 = 1;
    config.operation_code2 = 2;
    config.operation_code3 = 3;

    switch(confirmed_packet){
    case 1: memcpy(buf, &(config.packet_id2), BUFFSIZE);
            hid_write(handle_read, buf, BUFFSIZE);
            break;
    case 2: memcpy(buf, &(config.packet_id3), BUFFSIZE);
            hid_write(handle_read, buf, BUFFSIZE);
            break;
    case 3: buf[0] = 2;
            buf[1] = 255; //EOT marker
            hid_write(handle_read, buf, BUFFSIZE);
            if(mutex_for_save.tryLock()) {
                QMessageBox::information(this, tr("Success!"),
                                         tr("Config saved successfully to the board"));
                mutex_for_save.unlock();
            }
            break;
    }
}
