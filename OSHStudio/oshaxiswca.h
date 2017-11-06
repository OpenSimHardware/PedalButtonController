#ifndef OSHAXISWCA_H
#define OSHAXISWCA_H

#include <QWidget>

namespace Ui {
class OSHaxiswca;
}

class OSHaxiswca : public QWidget
{
    Q_OBJECT

public:
    explicit OSHaxiswca(QWidget *parent = 0);
    ~OSHaxiswca();
    uint16_t LeftPinValue(void);
    uint16_t RightPinValue(void);
    bool isAutoCalibEnabled(void);
    void setMinCalibValue(uint16_t value);
    void setMaxCalibValue(uint16_t value);
    void setPinsEnabled(bool);
    void setAxisValue(uint16_t value);
    void setAutoCalib(uint8_t state);


private slots:
    void MaxCalibCanged(QString text);
    void MinCalibCanged(QString text);
    void AutoCalibToggled(bool state);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void drawPin(QPoint pinpos);
    void fillPolygonArray(uint16_t value, char WhichPin);
    uint16_t checkPinValue(uint16_t pinvalue, char WhichPin);

    Ui::OSHaxiswca *ui;
    QPoint Lpoints[4]={
        QPoint(5,2),
        QPoint(5,9),
        QPoint(12,15),
        QPoint(12,2),
    };
    QPoint Rpoints[4]={
        QPoint(12,2),
        QPoint(12,9),
        QPoint(5,15),
        QPoint(5,2),
    };
    uint16_t LeftPinPosX, RightPinPosX;
    QPolygon LeftPinPoly, RightPinPoly;
    QColor LeftpinColor, RightpinColor;
    bool LeftPinDrag, RightPinDrag;
    const uint16_t MaxScaleValue=4095;
    bool AutoCalibEnabled;
    uint16_t PRbar_offset;
    bool ParentWidgetEnabled;
};

#endif // OSHAXISWCA_H
