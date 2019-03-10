#ifndef OSHA2BW_H
#define OSHA2BW_H

#include <QWidget>
#include <QLabel>
#include "../common_types/common_defines.h"

#define MAX_RESOLUTION 255

namespace Ui {
class osha2bw;
}


class osha2bw : public QWidget
{
    Q_OBJECT

public:
    explicit osha2bw(QWidget *parent = 0);
    ~osha2bw();
    uint8_t getButtonsCount(void);
    void setButtonsCount(uint8_t number);
    void getButtonsIntervals(uint8_t * buttonsIntervals);
    void setButtonsIntervals(uint8_t * buttonsIntervals);
    void setPinName(QString pin);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::osha2bw *ui;
    void fillPolygonArray(uint16_t value, uint8_t whichSlider);
    void drawPin(QPoint pinpos, uint8_t slider);
    uint16_t checkPinValue(uint16_t pinvalue, uint8_t slider_number);
    void draw_default_sliders(uint8_t sliders_number);
    void setLableValue(uint8_t whichSlider);

    QPoint points[5]={
        QPoint(5,2),
        QPoint(5,9),
        QPoint(8,15),
        QPoint(12,9),
        QPoint(12,2),
    };
    const uint16_t MaxScaleValue=4095;
    const uint16_t offset=60;
    uint8_t buttonsCount;
    struct A2B_params {
        uint16_t PinPosX;
        QPolygon PinPoly;
        QColor PinColor;
        bool PinDrag;
        QLabel * IntLabel;
    } sliders[MAX_A2B_BUTTONS];

signals:
    void buttons_number_changed(void);
};

#endif // OSHA2BW_H
