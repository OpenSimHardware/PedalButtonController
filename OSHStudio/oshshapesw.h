#ifndef OSHSHAPESW_H
#define OSHSHAPESW_H

#include <QWidget>
#include <QRect>
#include "../common_types/common_defines.h"

#define NETXCOLUMNS 7
#define NETYROWS 9

//#define SLIDERRADIUS 16
//#define OUTERKNOBRADIUS 8
//#define XOFFSET (SLIDERRADIUS/2)
//#define YOFFSET (SLIDERRADIUS/2)


namespace Ui {
class oshshapesw;
}

class oshshapesw : public QWidget
{
    Q_OBJECT

public:
    explicit oshshapesw(QWidget *parent = nullptr);
    ~oshshapesw();
    void getAllPoints(uint16_t * array, uint8_t num_elements=SHAPEVALUES);
    void setAllPoints(uint16_t * array, uint8_t num_elements=SHAPEVALUES);
    void setReadOnlyMode(bool mode);

private:
    Ui::oshshapesw *ui;
    int widget_width;
    int widget_height;
    struct {
        int X_value;
        int Y_value;
        uint16_t orig_value;
        bool drag_state;
        QRect knob_area;
        QColor knob_color;
    } shape_values[SHAPEVALUES];
    QColor const knob_inactive_color = QColor(1,119,215);
    QColor const knob_active_color = Qt::black;
    QColor const knob_move_color = Qt::lightGray;
    QColor curve_color = QColor(1,119,215);
    QColor net_odd_color = Qt::black;
    uint8_t slider_radius = 16;
    bool rw_mode = true;

private slots:
//    void drawSpline(void);
    int getSplinePoint(int p1, int p2, int distance);
    void repaintit();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
    void knob_moved(void);
};

#endif // OSHSHAPESW_H
