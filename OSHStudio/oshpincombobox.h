#ifndef OSHPINCOMBOBOX_H
#define OSHPINCOMBOBOX_H

#include <QWidget>
#include "../common_types/common_structs.h"

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

};

#endif // OSHPINCOMBOBOX_H
