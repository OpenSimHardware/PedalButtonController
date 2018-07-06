#include "oshstudio.h"
#include "ui_oshstudio.h"

void OSHStudio::showBoardType(int boardtype) {

const  struct pin_comp_geometry pin_components[3][32] = {
    {
    {"label_A0",20,110,"comboBoxA0",60,110},
    {"label_A1",20,130,"comboBoxA1",60,130},
    {"label_A2",20,150,"comboBoxA2",60,150},
    {"label_A3",20,170,"comboBoxA3",60,170},
    {"label_A4",20,190,"comboBoxA4",60,190},
    {"label_A5",20,210,"comboBoxA5",60,210},
    {"label_A6",20,230,"comboBoxA6",60,230},
    {"label_A7",20,250,"comboBoxA7",60,250},
    {"label_A8",550,320,"comboBoxA8",400,320},
    {"label_A9",550,300,"comboBoxA9",400,300},
    {"label_A10",550,280,"comboBoxA10",400,280},
    {"label_A11",550,260,"comboBoxA11",400,260},
    {"label_A12",550,240,"comboBoxA12",400,240},
    {"label_A15",550,220,"comboBoxA15",400,220},
    {"label_B0",20,270,"comboBoxB0",60,270},
    {"label_B1",20,290,"comboBoxB1",60,290},
    {"label_B3",550,200,"comboBoxB3",400,200},
    {"label_B4",550,180,"comboBoxB4",400,180},
    {"label_B5",550,160,"comboBoxB5",400,160},
    {"label_B6",550,140,"comboBoxB6",400,140},
    {"label_B7",550,120,"comboBoxB7",400,120},
    {"label_B8",550,100,"comboBoxB8",400,100},
    {"label_B9",550,80,"comboBoxB9",400,80},
    {"label_B10",20,310,"comboBoxB10",60,310},
    {"label_B11",20,330,"comboBoxB11",60,330},
    {"label_B12",550,400,"comboBoxB12",400,400},
    {"label_B13",550,380,"comboBoxB13",400,380},
    {"label_B14",550,360,"comboBoxB14",400,360},
    {"label_B15",550,340,"comboBoxB15",400,340},
    {"label_C13",20,50,"comboBoxC13",60,50},
    {"label_C14",20,70,"comboBoxC14",60,70},
    {"label_C15",20,90,"comboBoxC15",60,90},
},{
{"label_A0",550,290,"comboBoxA0",400,290},
{"label_A1",550,270,"comboBoxA1",400,270},
{"label_A2",550,250,"comboBoxA2",400,250},
{"label_A3",550,230,"comboBoxA3",400,230},
{"label_A4",550,210,"comboBoxA4",400,210},
{"label_A5",550,190,"comboBoxA5",400,190},
{"label_A6",550,170,"comboBoxA6",400,170},
{"label_A7",550,150,"comboBoxA7",400,150},
{"label_A8",20,140,"comboBoxA8",60,140},
{"label_A9",20,160,"comboBoxA9",60,160},
{"label_A10",20,180,"comboBoxA10",60,180},
{"label_A11",20,200,"comboBoxA11",60,200},
{"label_A12",20,220,"comboBoxA12",60,220},
{"label_A15",20,240,"comboBoxA15",60,240},
{"label_B0",550,130,"comboBoxB0",400,130},
{"label_B1",550,110,"comboBoxB1",400,110},
{"label_B3",20,260,"comboBoxB3",60,260},
{"label_B4",20,280,"comboBoxB4",60,280},
{"label_B5",20,300,"comboBoxB5",60,300},
{"label_B6",20,320,"comboBoxB6",60,320},
{"label_B7",20,340,"comboBoxB7",60,340},
{"label_B8",560,350,"comboBoxB8",400,350},
{"label_B9",560,330,"comboBoxB9",400,330},
{"label_B10",550,90,"comboBoxB10",400,90},
{"label_B11",550,70,"comboBoxB11",400,70},
{"label_B12",20,60,"comboBoxB12",60,60},
{"label_B13",20,80,"comboBoxB13",60,80},
{"label_B14",20,100,"comboBoxB14",60,100},
{"label_B15",20,120,"comboBoxB15",60,120},
{"label_C13",550,310,"comboBoxC13",400,310},
{"label_C14",20,420,"comboBoxC14",60,420},
{"label_C15",20,400,"comboBoxC15",60,400},
},
                                                    };

    QString name_template("widget_PB%1");

    for (uint8_t i=0; i<32; i++){
        oshpincombobox *comboBox_ptr = ui->tabWidget->findChild<oshpincombobox *>(name_template.arg(i));
        comboBox_ptr->setVisible(false);
        QLabel *label_ptr = ui->tabWidget->findChild<QLabel *>(pin_components[0][i].Label_name);
        label_ptr->setVisible(false);

        comboBox_ptr->move(pin_components[boardtype][i].ComboBox_X,pin_components[boardtype][i].ComboBox_Y);
        comboBox_ptr->setVisible(true);
        label_ptr->move(pin_components[boardtype][i].Label_X,pin_components[boardtype][i].Label_Y);
        label_ptr->setVisible(true);
    }
/*
    for (uint8_t i=0; i<32; i++){
        QComboBox *comboBox_ptr = ui->tabWidget->findChild<QComboBox *>(pin_components[boardtype][i].ComboBox_name);
        comboBox_ptr->move(pin_components[boardtype][i].ComboBox_X,pin_components[boardtype][i].ComboBox_Y);
        comboBox_ptr->setVisible(true);
        QLabel *label_ptr = ui->tabWidget->findChild<QLabel *>(pin_components[boardtype][i].Label_name);
        label_ptr->move(pin_components[boardtype][i].Label_X,pin_components[boardtype][i].Label_Y);
        label_ptr->setVisible(true);
    }
*/
    switch (boardtype) {
        case 0: ui->label->setPixmap(QPixmap(":/Images/MDB_pic.jpg"));
                break;
        case 1: ui->label_C14->setVisible(false);
                ui->label_C15->setVisible(false);
                //ui->comboBoxC14->setVisible(false);
                //ui->comboBoxC15->setVisible(false);
                ui->widget_PB30->setVisible(false);
                ui->widget_PB31->setVisible(false);
                ui->label->setPixmap(QPixmap(":/Images/boardTypeII.jpg"));
                break;
        }

}

