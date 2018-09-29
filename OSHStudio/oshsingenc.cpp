#include "oshsingenc.h"
#include "ui_oshsingenc.h"

oshsingenc::oshsingenc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oshsingenc)
{
    ui->setupUi(this);
}

oshsingenc::~oshsingenc()
{
    delete ui;
}

void oshsingenc::showCurrentPair(uint8_t pin_index){
    ui->comboBox_SEA->setCurrentIndex(pin_index);
    ui->comboBox_SEB->setCurrentIndex(pin_index);
}


void oshsingenc::setPinsPair(uint8_t pin_index) {
    pinA = all_enc_pins[pin_index].pinA;
    pinB = all_enc_pins[pin_index].pinB;
    showCurrentPair(pin_index);
}

void oshsingenc::clearPinsLists(void){
    ui->comboBox_SEA->clear();
    ui->comboBox_SEB->clear();
    pins_pairs_total = 0;
}

void oshsingenc::addPins2Lists(uint8_t pinA, uint8_t pinB, uint8_t type){
    QString ptype = "";
    all_enc_pins[pins_pairs_total].pinA = pinA;
    all_enc_pins[pins_pairs_total].pinB = pinB;
    all_enc_pins[pins_pairs_total++].type = type;
    if ((type == Single_Rotary_PINA_1) || (type == Single_Rotary_PINB_1)) ptype = "1/1";
    if ((type == Single_Rotary_PINA_2) || (type == Single_Rotary_PINB_2)) ptype = "1/2";
    if ((type == Single_Rotary_PINA_4) || (type == Single_Rotary_PINB_4)) ptype = "1/4";
    ui->comboBox_SEA->addItem(ptype + " step - " + pin_names[pinA]);
    ui->comboBox_SEB->addItem(ptype + " step - " + pin_names[pinB]);
}

uint8_t oshsingenc::getPinA(void){
    return pinA;
}

uint8_t oshsingenc::getPinB(void){
    return pinB;
}

void oshsingenc::setAlarmPinA(bool alarm){
    if (alarm) {
        ui->comboBox_SEA->setStyleSheet("QComboBox { color: white; background-color: red; }");
    } else {
        ui->comboBox_SEA->setStyleSheet("QComboBox { color: black; background-color: light gray; }");
    }
}

void oshsingenc::setAlarmPinB(bool alarm){
    if (alarm) {
        ui->comboBox_SEB->setStyleSheet("QComboBox { color: white; background-color: red; }");
    } else {
        ui->comboBox_SEB->setStyleSheet("QComboBox { color: black; background-color: light gray; }");
    }
}

void oshsingenc::on_comboBox_SEA_highlighted(int index){
    pinA = all_enc_pins[index].pinA;
    emit item_changed();
}

void oshsingenc::on_comboBox_SEB_highlighted(int index){
    pinB = all_enc_pins[index].pinB;
    emit item_changed();
}
