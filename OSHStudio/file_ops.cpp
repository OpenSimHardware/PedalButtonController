#include "oshstudio.h"
#include "ui_oshstudio.h"
#include<QMessageBox>

extern uint8_t Total_Single_encoders;
extern struct single_encoders_pins single_encoders_store[14];

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
            ui->widget_axis1->setMinCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis1->setMaxCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis1->setAutoCalib(value.toUInt());

            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis2->setMinCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis2->setMaxCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis2->setAutoCalib(value.toUInt());

            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis3->setMinCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis3->setMaxCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis3->setAutoCalib(value.toUInt());

            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis4->setMinCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis4->setMaxCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis4->setAutoCalib(value.toUInt());

            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis5->setMinCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis5->setMaxCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis5->setAutoCalib(value.toUInt());

            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis6->setMinCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis6->setMaxCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axis6->setAutoCalib(value.toUInt());

            line = in.readLine();
            value = line.section('=',1,1);
            ui->checkBox_AxisComb->setChecked(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axisComb1->setMinCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axisComb1->setMaxCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axisComb2->setMinCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axisComb2->setMaxCalibValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axisComb1->setAutoCalib(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->widget_axisComb2->setAutoCalib(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->radioButtonCoopwoork->setChecked(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->radioButtonEachonhisown->setChecked(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->horizontalSliderAxisComb->setValue(value.toUInt());

            line = in.readLine();
            value = line.section('=',1,1);
            ui->horiSlider_A2B->setValue(value.toUInt());


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

            line = in.readLine();
            value = line.section('=',1,1);
            ui->lineEdit_Device_ident->setText(value);
            line = in.readLine();
            value = line.section('=',1,1);
//            ui->lineEdit_Serial_Number->setText(value);
            line = in.readLine();
            value = line.section('=',1,1);
            ui->spinBox_USB_exchange->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->spinBox__Rot_Press_time->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->spinBox_RotSwitch_Press_time->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->spinBox_Rot_Debounce_time->setValue(value.toUInt());
            line = in.readLine();
            value = line.section('=',1,1);
            ui->spinBox_Button_Debounce_time->setValue(value.toUInt());

            line = in.readLine();
            value = line.section('=',1,1);
            Total_Single_encoders=value.toUInt();
            for (uint8_t i=0; i<14; i++) {
                line = in.readLine();
                value = line.section('=',1,1);
                single_encoders_store[i].pinA=value.toUInt();
                line = in.readLine();
                value = line.section('=',1,1);
                single_encoders_store[i].pinB=value.toUInt();
            }
            showSingleEncodersTab();

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

        << "Axis1Min=" << ui->widget_axis1->LeftPinValue() << "\n"
        << "Axis1Max=" << ui->widget_axis1->RightPinValue() << "\n"
        << "Axis1Func=" << ui->widget_axis1->isAutoCalibEnabled()  << "\n"

        << "Axis2Min=" << ui->widget_axis2->LeftPinValue() << "\n"
        << "Axis2Max=" << ui->widget_axis2->RightPinValue() << "\n"
        << "Axis2Func=" << ui->widget_axis2->isAutoCalibEnabled()  << "\n"

        << "Axis3Min=" << ui->widget_axis3->LeftPinValue() << "\n"
        << "Axis3Max=" << ui->widget_axis3->RightPinValue() << "\n"
        << "Axis3Func="<< ui->widget_axis3->isAutoCalibEnabled()   << "\n"

        << "Axis4Min=" << ui->widget_axis4->LeftPinValue() << "\n"
        << "Axis4Max=" << ui->widget_axis4->RightPinValue() << "\n"
        << "Axis4Func="<< ui->widget_axis4->isAutoCalibEnabled()   << "\n"

        << "Axis5Min=" << ui->widget_axis5->LeftPinValue() << "\n"
        << "axis5Max=" << ui->widget_axis5->RightPinValue() << "\n"
        << "Axis5Func="<< ui->widget_axis5->isAutoCalibEnabled()   << "\n"

        << "Axis6Min=" << ui->widget_axis6->LeftPinValue() << "\n"
        << "Axis6Max=" << ui->widget_axis6->RightPinValue() << "\n"
        << "Axis6Func="<< ui->widget_axis6->isAutoCalibEnabled()   << "\n"

        << "ComboAxis=" << ui->checkBox_AxisComb->isChecked() << "\n"
        << "ComboAxisPin1Min=" << ui->widget_axisComb1->LeftPinValue() << "\n"
        << "ComboAxisPin1Max=" << ui->widget_axisComb1->RightPinValue() << "\n"
        << "ComboAxisPin2Min=" << ui->widget_axisComb2->LeftPinValue() << "\n"
        << "ComboAxisPin2Max=" << ui->widget_axisComb2->RightPinValue() << "\n"
        << "ComboAxisPin1AC=" << ui->widget_axisComb1->isAutoCalibEnabled() << "\n"
        << "ComboAxisPin2AC=" << ui->widget_axisComb2->isAutoCalibEnabled() << "\n"
        << "ComboAxisCoop=" << ui->radioButtonCoopwoork->isChecked() << "\n"
        << "ComboAxisSep=" << ui->radioButtonEachonhisown->isChecked() << "\n"
        << "ComboAxisSlid=" << ui->horizontalSliderAxisComb->value() << "\n"
        << "Analog2ButtonThresh" << ui->horiSlider_A2B->value() << "\n";

    int POVConf=0;
    if (ui->checkBox_POV1->isChecked()) POVConf|=0x1;
    if (ui->checkBox_POV2->isChecked()) POVConf|=0x2;
    if (ui->checkBox_POV3->isChecked()) POVConf|=0x4;
    if (ui->checkBox_POV4->isChecked()) POVConf|=0x8;
     out << "POVConfig=" << POVConf << "\n";

     out << "USB_custom_string=" << ui->lineEdit_Device_ident->text() << "\n"
//         << "USB_serial_number=" << ui->lineEdit_Serial_Number->text() << "\n"
         << "USB_poll_interval=" << ui->spinBox_USB_exchange->value() << "\n"
         << "Encoders_press_time=" << ui->spinBox__Rot_Press_time->value() << "\n"
         << "RotSwitch_press_time="<< ui->spinBox_RotSwitch_Press_time->value() << "\n"
         << "Encoders_debounce=" << ui->spinBox_Rot_Debounce_time->value() << "\n"
         << "Buttons_debounce=" << ui->spinBox_Button_Debounce_time->value() << "\n";

     out << "Total_Single_Encoders=" << Total_Single_encoders << "\n"
         << "1st_pinA=" << single_encoders_store[0].pinA << "\n"
         << "1st_pinB=" << single_encoders_store[0].pinB << "\n"
         << "2nd_pinA=" << single_encoders_store[1].pinA << "\n"
         << "2nd_pinB=" << single_encoders_store[1].pinB << "\n"
         << "3rd_pinA=" << single_encoders_store[2].pinA << "\n"
         << "3rd_pinB=" << single_encoders_store[2].pinB << "\n"
         << "4th_pinA=" << single_encoders_store[3].pinA << "\n"
         << "4th_pinB=" << single_encoders_store[3].pinB << "\n"
         << "5th_pinA=" << single_encoders_store[4].pinA << "\n"
         << "5th_pinB=" << single_encoders_store[4].pinB << "\n"
         << "6th_pinA=" << single_encoders_store[5].pinA << "\n"
         << "6th_pinB=" << single_encoders_store[5].pinB << "\n"
         << "7th_pinA=" << single_encoders_store[6].pinA << "\n"
         << "7th_pinB=" << single_encoders_store[6].pinB << "\n"
         << "8th_pinA=" << single_encoders_store[7].pinA << "\n"
         << "8th_pinB=" << single_encoders_store[7].pinB << "\n"
         << "9th_pinA=" << single_encoders_store[8].pinA << "\n"
         << "9th_pinB=" << single_encoders_store[8].pinB << "\n"
         << "10th_pinA=" << single_encoders_store[9].pinA << "\n"
         << "10th_pinB=" << single_encoders_store[9].pinB << "\n"
         << "11th_pinA=" << single_encoders_store[10].pinA << "\n"
         << "11th_pinB=" << single_encoders_store[10].pinB << "\n"
         << "12th_pinA=" << single_encoders_store[11].pinA << "\n"
         << "12th_pinB=" << single_encoders_store[11].pinB << "\n"
         << "13th_pinA=" << single_encoders_store[12].pinA << "\n"
         << "13th_pinB=" << single_encoders_store[12].pinB << "\n"
         << "14th_pinA=" << single_encoders_store[13].pinA << "\n"
         << "14th_pinB=" << single_encoders_store[13].pinB << "\n";

       file.close();
    }
}
