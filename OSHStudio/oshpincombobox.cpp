#include "oshpincombobox.h"
#include "ui_oshpincombobox.h"

oshpincombobox::oshpincombobox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oshpincombobox)
{
    ui->setupUi(this);

    QStringList list=(QStringList()<<"Not Used"<<"Analog No Smoothing"<<"Analog Low Smoothing"
                      <<"Analog Medium Smooth"<<"Analog High Smooting"<<"Analog to Button"
                      <<"Analog to Mouse X" << "Analog to Mouse Y" << "Analog to Mouse Wheel"
                      <<"Chd Rot Enc PINA"<<"Chd Rot Enc PINB"
                      <<"Chd Rot Enc 1/1"<<"Chd Rot Enc 1/2"
                      <<"Sng Rot Enc PINA 1/1"<<"Sng Rot Enc PINB 1/1"
                      <<"Sng Rot Enc PINA 1/2"<<"Sng Rot Enc PINB 1/2"
                      <<"Sng Rot Enc PINA 1/4"<<"Sng Rot Enc PINB 1/4"
                      <<"Button Matrix ROW"<<"Button Matrix COLUMN"
                      <<"Single Button +3.3V"<<"Single Button GND"
                      <<"Rotary Switch Pole"
                      <<"Rotary Switch Wire");
    ui->comboBox->addItems(list);
}

oshpincombobox::~oshpincombobox()
{
    delete ui;
}

void oshpincombobox::on_comboBox_currentIndexChanged(int index)
{
    QString color_scheme;

    switch ((pintype)index) {
        case AnalogNoSmooth:    color_scheme="QComboBox { color: white; background-color: #003300; }";break;
        case AnalogLowSmooth:   color_scheme="QComboBox { color: white; background-color: #003300; }";break;
        case AnalogMedSmooth:   color_scheme="QComboBox { color: white; background-color: #003300; }";break;
        case AnalogHighSmooth:  color_scheme="QComboBox { color: white; background-color: #003300; }";break;
        case Analog2Button:     color_scheme="QComboBox { color: white; background-color: #006600; }";break;
        case Analog2MouseX:     color_scheme="QComboBox { color: white; background-color: #666600; }";break;
        case Analog2MouseY:     color_scheme="QComboBox { color: white; background-color: #666600; }";break;
        case Analog2MouseWheel:     color_scheme="QComboBox { color: white; background-color: #666600; }";break;
        case Chain_Rotary_PINA: color_scheme="QComboBox { color: white; background-color: #669900; }";break;
        case Chain_Rotary_PINB: color_scheme="QComboBox { color: white; background-color: #669900; }";break;
        case Chain_Rotary_Enc_1:color_scheme="QComboBox { color: black; background-color: #669900; }";break;
        case Chain_Rotary_Enc_2:color_scheme="QComboBox { color: black; background-color: #669900; }";break;
        case Single_Rotary_PINA_1:color_scheme="QComboBox { color: black; background-color: #66cc00; }";break;
        case Single_Rotary_PINB_1:color_scheme="QComboBox { color: black; background-color: #66cc00; }";break;
        case Single_Rotary_PINA_2:color_scheme="QComboBox { color: black; background-color: #66cc33; }";break;
        case Single_Rotary_PINB_2:color_scheme="QComboBox { color: black; background-color: #66cc33; }";break;
        case Single_Rotary_PINA_4:color_scheme="QComboBox { color: black; background-color: #66cc66; }";break;
        case Single_Rotary_PINB_4:color_scheme="QComboBox { color: black; background-color: #66cc66; }";break;
        case Button_ROW:        color_scheme="QComboBox { color: white; background-color: #009900; }";break;
        case Button_COLUMN:     color_scheme="QComboBox { color: white; background-color: #00cc00; }";break;
        case Button:            color_scheme="QComboBox { color: black; background-color: #00ff00; }";break;
        case Button_GND:        color_scheme="QComboBox { color: black; background-color: #00ff00; }";break;
        case RotSwPole:         color_scheme="QComboBox { color: white; background-color: #669900; }";break;
        case RotSwWire:         color_scheme="QComboBox { color: white; background-color: #669900; }";break;
        case Not_Used:          color_scheme="QComboBox { color: black; background-color: light gray; }";break;
    default:                    break;
    }

    ui->comboBox->setStyleSheet(color_scheme);
    ui->comboBox->clearFocus();
    emit item_changed();
}

void oshpincombobox::set_pin_number(uint8_t pin_number)
{
    // disable chained 1/4 enc config
    //ui->comboBox->setItemData(10, 0, Qt::UserRole - 1);

    if ((pin_number > 8) && (pin_number !=14) && (pin_number != 15)){
        ui->comboBox->setItemData(1, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(2, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(3, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(4, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(5, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(6, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(7, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(8, 0, Qt::UserRole - 1);
    }
    if (pin_number == 29) {
        ui->comboBox->setItemData(9, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(10, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(13, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(14, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(15, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(16, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(17, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(18, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(19, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(21, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(22, 0, Qt::UserRole - 1);
        ui->comboBox->setItemData(24, 0, Qt::UserRole - 1);
    }
}

uint8_t oshpincombobox::get_current_index(void)
{
    return ui->comboBox->currentIndex();
}

void oshpincombobox::set_current_index(uint8_t pin)
{
    ui->comboBox->setCurrentIndex(pin);
}
