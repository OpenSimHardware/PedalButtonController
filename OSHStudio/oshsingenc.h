#ifndef OSHSINGENC_H
#define OSHSINGENC_H

#include <QWidget>
#include <..\common_types\common_structs.h>

namespace Ui {
class oshsingenc;
}

struct sing_enc_store {
    uint8_t pinA;
    uint8_t pinB;
    uint8_t type;
};

const QString pin_names[] = {
 {"A0"},
 {"A1"},
 {"A2"},
 {"A3"},
 {"A4"},
 {"A5"},
 {"A6"},
 {"A7"},
 {"A8"},
 {"A9"},
 {"A10"},
 {"A11"},
 {"A12"},
 {"A15"},
 {"B0"},
 {"B1"},
 {"B3"},
 {"B4"},
 {"B5"},
 {"B6"},
 {"B7"},
 {"B8"},
 {"B9"},
 {"B10"},
 {"B11"},
 {"B12"},
 {"B13"},
 {"B14"},
 {"B15"},
 {"C13"},
 {"C14"},
 {"C15"},
};


class oshsingenc : public QWidget
{
    Q_OBJECT

public:
    explicit oshsingenc(QWidget *parent = 0);
    ~oshsingenc();
    void setPinsPair(uint8_t pin_index);
    void clearPinsLists(void);
    void addPins2Lists(uint8_t pinA, uint8_t pinB, uint8_t type);
    uint8_t getPinA(void);
    uint8_t getPinB(void);
    void setAlarmPinA(bool alarm);
    void setAlarmPinB(bool alarm);

private:
    void showCurrentPair(uint8_t pin_index);
    Ui::oshsingenc *ui;
    uint8_t pinA;
    uint8_t pinB;
    uint8_t type;
    sing_enc_store all_enc_pins[USEDPINS];
    uint8_t pins_pairs_total;
    QStringList PinsA;
    QStringList PinsB;

signals:
    void item_changed();
private slots:
    void on_comboBox_SEA_highlighted(int index);
    void on_comboBox_SEB_highlighted(int index);
};

#endif // OSHSINGENC_H
