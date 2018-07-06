#ifndef OSHPINCOMBOBOX_H
#define OSHPINCOMBOBOX_H

#include <QWidget>

namespace Ui {
class oshpincombobox;
}

class oshpincombobox : public QWidget
{
    Q_OBJECT

public:
    explicit oshpincombobox(QWidget *parent = 0);
    ~oshpincombobox();

signals:
    void item_changed();

public slots:
    void set_pin_number(uint8_t);
    uint8_t get_current_index(void);
    void set_current_index(uint8_t);


private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::oshpincombobox *ui;

    typedef enum {
        Not_Used = 0,
        AnalogNoSmooth = 1,
        AnalogLowSmooth = 2,
        AnalogMedSmooth = 3,
        AnalogHighSmooth = 4,
        Analog2Button = 5,
        Chain_Rotary_PINA = 6,
        Chain_Rotary_PINB = 7,
        Chain_Rotary_Enc_1 = 8,
        Chain_Rotary_Enc_2 = 9,
        Chain_Rotary_Enc_4 = 10,
        Single_Rotary_PINA_1 = 11,
        Single_Rotary_PINB_1 = 12,
        Single_Rotary_PINA_2 = 13,
        Single_Rotary_PINB_2 = 14,
        Single_Rotary_PINA_4 = 15,
        Single_Rotary_PINB_4 = 16,
        Button_ROW = 17,
        Button_COLUMN = 18,
        Button = 19,
        Button_GND = 20,
        RotSwPole = 21,
        RotSwWire = 22,
  } pintype;

};

#endif // OSHPINCOMBOBOX_H
