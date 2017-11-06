#include "oshstudio.h"
#include "ui_oshstudio.h"
#include <windows.h>

extern hid_device *handle_read;//, *handle_write;
extern uint8_t AxisComb_StartPin, AxisComb_EndPin, AxisComb_Percent;
extern struct single_encoders_pins single_encoders_store[14];
extern uint8_t Total_Single_encoders;
extern uint8_t AxisComb_StartPin, AxisComb_EndPin, AxisComb_Percent;
extern QString pin_names[PINS];

/*uint8_t NumberAnalogInputs,
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
*/


void OSHStudio::writeConfig_Slot()
{
    uint8_t buf[BUFFSIZE]={2,1,0};
    uint8_t res=0;

    //gather pins config
    buf[2]=ui->comboBoxA0->currentIndex();
    buf[3]=ui->comboBoxA1->currentIndex();
    buf[4]=ui->comboBoxA2->currentIndex();
    buf[5]=ui->comboBoxA3->currentIndex();
    buf[6]=ui->comboBoxA4->currentIndex();
    buf[7]=ui->comboBoxA5->currentIndex();
    buf[8]=ui->comboBoxA6->currentIndex();
    buf[9]=ui->comboBoxA7->currentIndex();
    buf[10]=ui->comboBoxA8->currentIndex();
    buf[11]=ui->comboBoxA9->currentIndex();
    buf[12]=ui->comboBoxA10->currentIndex();
    buf[13]=ui->comboBoxA11->currentIndex();
    buf[14]=ui->comboBoxA12->currentIndex();
    buf[15]=ui->comboBoxA15->currentIndex();
    buf[16]=ui->comboBoxB0->currentIndex();
    buf[17]=ui->comboBoxB1->currentIndex();
    buf[18]=ui->comboBoxB3->currentIndex();
    buf[19]=ui->comboBoxB4->currentIndex();
    buf[20]=ui->comboBoxB5->currentIndex();
    buf[21]=ui->comboBoxB6->currentIndex();
    buf[22]=ui->comboBoxB7->currentIndex();
    buf[23]=ui->comboBoxB8->currentIndex();
    buf[24]=ui->comboBoxB9->currentIndex();
    buf[25]=ui->comboBoxB10->currentIndex();
    buf[26]=ui->comboBoxB11->currentIndex();
    buf[27]=ui->comboBoxB12->currentIndex();
    buf[28]=ui->comboBoxB13->currentIndex();
    buf[29]=ui->comboBoxB14->currentIndex();
    buf[30]=ui->comboBoxB15->currentIndex();
    buf[31]=ui->comboBoxC13->currentIndex();
    buf[32]=ui->comboBoxC14->currentIndex();
    buf[33]=ui->comboBoxC15->currentIndex();


    //gather axises config
    buf[34]=LOBYTE(ui->widget_axis1->LeftPinValue());
    buf[35]=HIBYTE(ui->widget_axis1->LeftPinValue());
    buf[36]=LOBYTE(ui->widget_axis1->RightPinValue());
    buf[37]=HIBYTE(ui->widget_axis1->RightPinValue());
    buf[38]=(uint8_t)ui->widget_axis1->isAutoCalibEnabled();

    buf[39]=LOBYTE(ui->widget_axis2->LeftPinValue());
    buf[40]=HIBYTE(ui->widget_axis2->LeftPinValue());
    buf[41]=LOBYTE(ui->widget_axis2->RightPinValue());
    buf[42]=HIBYTE(ui->widget_axis2->RightPinValue());
    buf[43]=(uint8_t)ui->widget_axis2->isAutoCalibEnabled();

    buf[44]=LOBYTE(ui->widget_axis3->LeftPinValue());
    buf[45]=HIBYTE(ui->widget_axis3->LeftPinValue());
    buf[46]=LOBYTE(ui->widget_axis3->RightPinValue());
    buf[47]=HIBYTE(ui->widget_axis3->RightPinValue());
    buf[48]=(uint8_t)ui->widget_axis3->isAutoCalibEnabled();

    buf[49]=LOBYTE(ui->widget_axis4->LeftPinValue());
    buf[50]=HIBYTE(ui->widget_axis4->LeftPinValue());
    buf[51]=LOBYTE(ui->widget_axis4->RightPinValue());
    buf[52]=HIBYTE(ui->widget_axis4->RightPinValue());
    buf[53]=(uint8_t)ui->widget_axis4->isAutoCalibEnabled();

    buf[54]=LOBYTE(ui->widget_axis5->LeftPinValue());
    buf[55]=HIBYTE(ui->widget_axis5->LeftPinValue());
    buf[56]=LOBYTE(ui->widget_axis5->RightPinValue());
    buf[57]=HIBYTE(ui->widget_axis5->RightPinValue());
    buf[58]=(uint8_t)ui->widget_axis5->isAutoCalibEnabled();

    buf[59]=LOBYTE(ui->widget_axis6->LeftPinValue());
    buf[60]=HIBYTE(ui->widget_axis6->LeftPinValue());
    buf[61]=LOBYTE(ui->widget_axis6->RightPinValue());
    buf[62]=HIBYTE(ui->widget_axis6->RightPinValue());
    buf[63]=(uint8_t)ui->widget_axis6->isAutoCalibEnabled();

//    send_write_packet(buf);

//        for (uint8_t i=0; i<BUFFSIZE; i++){
//            buf[i]=0;
//        }

    res=hid_write(handle_read, buf, BUFFSIZE);

    Sleep(100);



    buf[1]=2;
    buf[2]=LOBYTE(ui->spinBox__Rot_Press_time->value());
    buf[3]=HIBYTE(ui->spinBox__Rot_Press_time->value());
    buf[4]=LOBYTE(ui->spinBox_Rot_Debounce_time->value());
    buf[5]=HIBYTE(ui->spinBox_Rot_Debounce_time->value());
    buf[6]=LOBYTE(ui->spinBox_Button_Debounce_time->value());
    buf[7]=HIBYTE(ui->spinBox_Button_Debounce_time->value());
    buf[8]=ui->spinBox_USB_exchange->value();
    buf[9]=LOBYTE(ui->spinBox_RotSwitch_Press_time->value());
    buf[10]=HIBYTE(ui->spinBox_RotSwitch_Press_time->value());

    QString USB_PS_Uniq =ui->lineEdit_Device_ident->text();
    for(uint8_t i=0; i <10; i++){
        if (USB_PS_Uniq.at(i) != 0) {
          buf[11+i] = (uint8_t)USB_PS_Uniq.at(i).toLatin1();
        } else {
            buf[11+i] = 0;
            }
    }


    buf[21]=0;
    if (ui->checkBox_AxisComb->isChecked()) {
        buf[21]=1;
        buf[22]=LOBYTE(ui->widget_axisComb1->LeftPinValue());
        buf[23]=HIBYTE(ui->widget_axisComb1->LeftPinValue());
        buf[24]=LOBYTE(ui->widget_axisComb1->RightPinValue());
        buf[25]=HIBYTE(ui->widget_axisComb1->RightPinValue());
        buf[26]=LOBYTE(ui->widget_axisComb2->LeftPinValue());
        buf[27]=HIBYTE(ui->widget_axisComb2->LeftPinValue());
        buf[28]=LOBYTE(ui->widget_axisComb2->RightPinValue());
        buf[29]=HIBYTE(ui->widget_axisComb2->RightPinValue());
        buf[30]=0;
        if (ui->widget_axisComb1->isAutoCalibEnabled()) buf[30]|=0x1;
        if (ui->widget_axisComb2->isAutoCalibEnabled()) buf[30]|=0x2;
        if (ui->radioButtonCoopwoork->isChecked()) buf[30]|=0x4;
//        if (ui->radioButtonEachonhisown->isChecked()) buf[30]|=0x8;
        buf[61]=ui->horizontalSliderAxisComb->value();
        buf[62]=convertPinnameToIndex(ui->comboBox_AxisCombBegin->currentText());
        buf[63]=convertPinnameToIndex(ui->comboBox_AxisCombEnd->currentText());
    }



    buf[31] = Total_Single_encoders;
    for (uint8_t i=0; i<14; i++) {
        buf[32+(i*2)] = single_encoders_store[i].pinA;
        buf[33+(i*2)] = single_encoders_store[i].pinB;
    }

    buf[60]=0;
    if (ui->checkBox_POV1->isChecked()) buf[60]|=0x1;
    if (ui->checkBox_POV2->isChecked()) buf[60]|=0x2;
    if (ui->checkBox_POV3->isChecked()) buf[60]|=0x4;
    if (ui->checkBox_POV4->isChecked()) buf[60]|=0x8;


//    send_write_packet(buf);
    res=hid_write(handle_read, buf, BUFFSIZE);

    Sleep(100);

    buf[1]=3;
    buf[2]=LOBYTE(ui->horiSlider_A2B->value());
    buf[3]=HIBYTE(ui->horiSlider_A2B->value());

    res=hid_write(handle_read, buf, BUFFSIZE);
}

void OSHStudio::setConfig_Slot(uint8_t buf[BUFFSIZE], uint8_t op_code){
    wchar_t tmp[10];
    wchar_t * USB_PS_Uniq;
//    wchar_t * USB_SN_Uniq;
//    struct sgl_enc_pins {
//        uint8_t pinA;
//        uint8_t pinB;
//        uint8_t pinA_type;
//        uint8_t pinB_type;
    struct single_encoders_pins sgl_enc_tmp[14]={0,0,0,0};

    if (op_code == 1) {
        ui->comboBoxA0->setCurrentIndex(buf[2]);
        ui->comboBoxA1->setCurrentIndex(buf[3]);
        ui->comboBoxA2->setCurrentIndex(buf[4]);
        ui->comboBoxA3->setCurrentIndex(buf[5]);
        ui->comboBoxA4->setCurrentIndex(buf[6]);
        ui->comboBoxA5->setCurrentIndex(buf[7]);
        ui->comboBoxA6->setCurrentIndex(buf[8]);
        ui->comboBoxA7->setCurrentIndex(buf[9]);
        ui->comboBoxA8->setCurrentIndex(buf[10]);
        ui->comboBoxA9->setCurrentIndex(buf[11]);
        ui->comboBoxA10->setCurrentIndex(buf[12]);
        ui->comboBoxA11->setCurrentIndex(buf[13]);
        ui->comboBoxA12->setCurrentIndex(buf[14]);
        ui->comboBoxA15->setCurrentIndex(buf[15]);
        ui->comboBoxB0->setCurrentIndex(buf[16]);
        ui->comboBoxB1->setCurrentIndex(buf[17]);
        ui->comboBoxB3->setCurrentIndex(buf[18]);
        ui->comboBoxB4->setCurrentIndex(buf[19]);
        ui->comboBoxB5->setCurrentIndex(buf[20]);
        ui->comboBoxB6->setCurrentIndex(buf[21]);
        ui->comboBoxB7->setCurrentIndex(buf[22]);
        ui->comboBoxB8->setCurrentIndex(buf[23]);
        ui->comboBoxB9->setCurrentIndex(buf[24]);
        ui->comboBoxB10->setCurrentIndex(buf[25]);
        ui->comboBoxB11->setCurrentIndex(buf[26]);
        ui->comboBoxB12->setCurrentIndex(buf[27]);
        ui->comboBoxB13->setCurrentIndex(buf[28]);
        ui->comboBoxB14->setCurrentIndex(buf[29]);
        ui->comboBoxB15->setCurrentIndex(buf[30]);
        ui->comboBoxC13->setCurrentIndex(buf[31]);
        ui->comboBoxC14->setCurrentIndex(buf[32]);
        ui->comboBoxC15->setCurrentIndex(buf[33]);

        ui->widget_axis1->setMinCalibValue((buf[35]<<8) | buf[34]);
        ui->widget_axis1->setMaxCalibValue((buf[37]<<8) | buf[36]);
        ui->widget_axis1->setAutoCalib(buf[38]);

        ui->widget_axis2->setMinCalibValue((buf[40]<<8) | buf[39]);
        ui->widget_axis2->setMaxCalibValue((buf[42]<<8) | buf[41]);
        ui->widget_axis2->setAutoCalib(buf[43]);

        ui->widget_axis3->setMinCalibValue((buf[45]<<8) | buf[44]);
        ui->widget_axis3->setMaxCalibValue((buf[47]<<8) | buf[46]);
        ui->widget_axis3->setAutoCalib(buf[48]);

        ui->widget_axis4->setMinCalibValue((buf[50]<<8) | buf[49]);
        ui->widget_axis4->setMaxCalibValue((buf[52]<<8) | buf[51]);
        ui->widget_axis4->setAutoCalib(buf[53]);

        ui->widget_axis5->setMinCalibValue((buf[55]<<8) | buf[54]);
        ui->widget_axis5->setMaxCalibValue((buf[57]<<8) | buf[56]);
        ui->widget_axis5->setAutoCalib(buf[58]);

        ui->widget_axis6->setMinCalibValue((buf[60]<<8) | buf[59]);
        ui->widget_axis6->setMaxCalibValue((buf[62]<<8) | buf[61]);
        ui->widget_axis6->setAutoCalib(buf[63]);
    }

    if (op_code == 2) {
        ui->spinBox__Rot_Press_time->setValue((buf[3]<<8)+buf[2]);
        ui->spinBox_Rot_Debounce_time->setValue((buf[5]<<8)+buf[4]);
        ui->spinBox_Button_Debounce_time->setValue((buf[7]<<8)+buf[6]);
        ui->spinBox_USB_exchange->setValue(buf[8]);
        ui->spinBox_RotSwitch_Press_time->setValue((buf[10]<<8)+buf[9]);


        for (uint8_t i=0; i<10; i++) {
            tmp[i]=(wchar_t)buf[11+i];
        }
        USB_PS_Uniq=tmp;
        ui->lineEdit_Device_ident->setText(QString::fromWCharArray(USB_PS_Uniq));

        ui->widget_axisComb1->setMinCalibValue((buf[23]<<8)+buf[22]);
        ui->widget_axisComb1->setMaxCalibValue((buf[25]<<8)+buf[24]);
        ui->widget_axisComb2->setMinCalibValue((buf[27]<<8)+buf[26]);
        ui->widget_axisComb2->setMaxCalibValue((buf[29]<<8)+buf[28]);

        ui->widget_axisComb1->setAutoCalib(buf[30] & 0x01);
        ui->widget_axisComb2->setAutoCalib((buf[30] & 0x02)>>1);
        if (buf[30] & 0x4) ui->radioButtonCoopwoork->setChecked(true);
          else ui->radioButtonEachonhisown->setChecked(true);
//        if (buf[30] & 0b1000) ui->radioButtonEachonhisown->setChecked(true);
//          else ui->radioButtonEachonhisown->setChecked(false);

        Total_Single_encoders=buf[31];
        for (uint8_t i=0; i<14; i++) {
            sgl_enc_tmp[i].pinA=buf[32+(i*2)] ;
            sgl_enc_tmp[i].pinB=buf[33+(i*2)] ;
        }

        if (buf[60] & 0x1) ui->checkBox_POV1->setChecked(true);
            else ui->checkBox_POV1->setChecked(false);
        if (buf[60] & 0x2) ui->checkBox_POV2->setChecked(true);
            else ui->checkBox_POV2->setChecked(false);
        if (buf[60] & 0x4) ui->checkBox_POV3->setChecked(true);
            else ui->checkBox_POV3->setChecked(false);
        if (buf[60] & 0x8) ui->checkBox_POV4->setChecked(true);
            else ui->checkBox_POV4->setChecked(false);


            ui->horizontalSliderAxisComb->setValue(buf[61]);
            ui->comboBox_AxisCombBegin->setCurrentText(pin_names[buf[62]]);
            ui->comboBox_AxisCombEnd->setCurrentText(pin_names[buf[63]]);
            if (buf[21]==1) ui->checkBox_AxisComb->setChecked(true);
                else ui->checkBox_AxisComb->setChecked(false);

        for (uint8_t i=0; i<Total_Single_encoders; i++){
            for (uint8_t j=0; j<Total_Single_encoders; j++) {
                if (sgl_enc_tmp[i].pinA == single_encoders_store[j].pinA) {
                    sgl_enc_tmp[i].pinA_type=single_encoders_store[j].pinA_type;
                }
                if (sgl_enc_tmp[i].pinB == single_encoders_store[j].pinB) {
                    sgl_enc_tmp[i].pinB_type=single_encoders_store[j].pinB_type;
                }
            }
        }
        for (uint8_t i=0; i<Total_Single_encoders; i++) {
            single_encoders_store[i].pinA=sgl_enc_tmp[i].pinA;
            single_encoders_store[i].pinB=sgl_enc_tmp[i].pinB;
            single_encoders_store[i].pinA_type=sgl_enc_tmp[i].pinA_type;
            single_encoders_store[i].pinB_type=sgl_enc_tmp[i].pinB_type;
        }
        showSingleEncodersTab();

    }


    if (op_code == 3) {
        ui->horiSlider_A2B->setValue((buf[3]<<8)+buf[2]);
    }

    buf[2]=LOBYTE(ui->horiSlider_A2B->value());
    buf[3]=HIBYTE(ui->horiSlider_A2B->value());


}

void OSHStudio::resetConfig_Slot(){
    uint8_t buf[BUFFSIZE]={0};

    setConfig_Slot(buf,1);
//    setConfig_Slot(buf,2);
}

void OSHStudio::restoreConfig_Slot(){
    uint8_t buf[BUFFSIZE]={0};

    for (uint8_t i=2; i<8; i++){
        buf[i]=AnalogMedSmooth;
    }
    buf[8]=Chain_Rotary_Enc_1;
    buf[9]=Button_COLUMN;
    buf[10]=Chain_Rotary_Enc_1;
    buf[11]=Chain_Rotary_Enc_1;
    buf[12]=Chain_Rotary_Enc_1;
    buf[15]=Chain_Rotary_Enc_1;
    buf[16]=Chain_Rotary_Enc_1;
    buf[17]=Chain_Rotary_Enc_1;
    buf[18]=Button_COLUMN;
    for (uint8_t i=19; i<25; i++){
        buf[i]=Button_ROW;
    }
    buf[25]=Chain_Rotary_PINA;
    buf[26]=Chain_Rotary_PINB;
    buf[27]=Button_COLUMN;
    buf[28]=Chain_Rotary_Enc_1;
    buf[29]=Chain_Rotary_Enc_1;
    buf[30]=Chain_Rotary_Enc_1;
    buf[31]=Button_COLUMN;
    buf[32]=Button_COLUMN;
    buf[33]=Button_COLUMN;

    buf[34]=0;
    buf[35]=0;
    buf[36]=0xFF;
    buf[37]=0x0F;

    buf[39]=0;
    buf[40]=0;
    buf[41]=0xFF;
    buf[42]=0x0F;

    buf[44]=0;
    buf[45]=0;
    buf[46]=0xFF;
    buf[47]=0x0F;

    buf[49]=0;
    buf[50]=0;
    buf[51]=0xFF;
    buf[52]=0x0F;

    buf[54]=0;
    buf[55]=0;
    buf[56]=0xFF;
    buf[57]=0x0F;

    buf[59]=0;
    buf[60]=0;
    buf[61]=0xFF;
    buf[62]=0x0F;

 //   buf[63]=0;

    setConfig_Slot(buf,1);

    for (uint8_t i=0; i<BUFFSIZE; i++){
        buf[i]=0;
    }

    buf[2]=50;
    buf[3]=0;
    buf[4]=10;
    buf[5]=0;
    buf[6]=50;
    buf[7]=0;
    buf[8]=0x10;
    buf[9]=100;
    buf[10]=0;
    buf[11]=0;

    buf[21]=0;
    buf[22]=0;
    buf[23]=0;
    buf[24]=0xFF;
    buf[25]=0x0F;
    buf[26]=0;
    buf[27]=0;
    buf[28]=0xFF;
    buf[29]=0x0F;
    buf[30]=4;

    buf[61]=50;
    buf[62]=4;
    buf[63]=5;

    setConfig_Slot(buf,2);

    buf[2] = 0x00;
    buf[3] = 0x08;

    setConfig_Slot(buf,3);

}

void OSHStudio::getConfig_Slot()
{
    uint8_t buf[BUFFSIZE]={0};
    uint8_t bufrep2[2]={3,1};
    uint8_t res=0,j=0;


    do {
        res=hid_write(handle_read, bufrep2, 2);
        res=hid_read(handle_read, buf, BUFFSIZE);
        j++;
       } while ((buf[0] != 4) || j<100 );
//    if (buf[1] == 1) {
        setConfig_Slot(buf,1);
//    }

    for (uint8_t i=1; i<BUFFSIZE; i++) {
        buf[i]=0;
    }

    bufrep2[1]=2;
    j=0;
    do {
        res=hid_write(handle_read, bufrep2, 2);
        res=hid_read(handle_read, buf, BUFFSIZE);
        j++;
       } while ((buf[0] != 4) || j<100 );
//    if (buf[1] == 2) {
        setConfig_Slot(buf,2);
//    }

        bufrep2[1]=3;
        j=0;
        do {
            res=hid_write(handle_read, bufrep2, 2);
            res=hid_read(handle_read, buf, BUFFSIZE);
            j++;
           } while ((buf[0] != 4) || j<100 );
    //    if (buf[1] == 2) {
            setConfig_Slot(buf,3);
    //    }

}


void OSHStudio::send_write_packet(uint8_t buf[BUFFSIZE])
{
    uint8_t answer[BUFFSIZE]={0};
    uint8_t res=0;
    uint8_t j=0;

    do {
        res=hid_write(handle_read, buf, BUFFSIZE);
        res=hid_read(handle_read, answer, BUFFSIZE);
        j++;
        Sleep(1);
       } while ((answer[0] != 4) || j<50 );
    if (answer[1] == 255) return;
}
