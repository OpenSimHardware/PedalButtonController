#include "oshshapesw.h"
#include "ui_oshshapesw.h"
#include <QPainter>
#include <QMouseEvent>


oshshapesw::oshshapesw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oshshapesw)
{
    ui->setupUi(this);
    for (int i=0; i<SHAPEVALUES; i++) {
        shape_values[i].X_value = 0;
        shape_values[i].Y_value = 0;
        shape_values[i].drag_state = false;
    }
    repaintit();
}

oshshapesw::~oshshapesw()
{
    delete ui;
}

void oshshapesw::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    uint8_t j=0;
    int current_part = 0;
    int x = 0;
    int y = 0;

    painter.begin(this);
    painter.setPen(Qt::lightGray);

    for (uint8_t i=0; i<=NETYROWS; i++){
        painter.drawLine(slider_radius,(widget_height+slider_radius) -((widget_height*i)/NETYROWS),
                         widget_width+slider_radius,(widget_height+slider_radius)-((widget_height*i)/NETYROWS));
    }
    for (uint8_t i=1; i<=((SHAPEVALUES-1)*2); i++){
        painter.setPen(Qt::lightGray);
        painter.drawLine(slider_radius+((widget_width*i)/((SHAPEVALUES-1)*2)),slider_radius,
                         slider_radius+((widget_width*i)/((SHAPEVALUES-1)*2)),widget_height+slider_radius);
        if (j++%2){
            painter.setPen(net_odd_color);
            painter.drawLine(slider_radius+((widget_width*i)/((SHAPEVALUES-1)*2)),slider_radius,
                         slider_radius+((widget_width*i)/((SHAPEVALUES-1)*2)),widget_height+slider_radius);
        }
    }
    painter.setPen(Qt::black);
    painter.drawLine(slider_radius,slider_radius,slider_radius,(widget_height+slider_radius));

 //   painter.setBrush(QColor(1,119,215));
    painter.setPen(Qt::gray);
    for (uint8_t i=0; i<SHAPEVALUES; i++){
        painter.setBrush(shape_values[i].knob_color);
        painter.drawEllipse(shape_values[i].knob_area);
        painter.setBrush(Qt::lightGray);
        painter.drawEllipse(shape_values[i].knob_area.x()+slider_radius/4,
                            shape_values[i].knob_area.y()+slider_radius/4,
                            slider_radius/2, slider_radius/2);
    }

    painter.setPen(curve_color);
    for (int i=0; i<MAX_ADC_RES; ++i){
        current_part = i/(MAX_ADC_RES/SHAPEVALUES);

          x = getSplinePoint(shape_values[current_part].X_value + slider_radius/2,
                                 shape_values[current_part+1].X_value + slider_radius/2, i%(MAX_ADC_RES/SHAPEVALUES));
          y = getSplinePoint(shape_values[current_part].Y_value + slider_radius/2,
                                 shape_values[current_part+1].Y_value + slider_radius/2, i%(MAX_ADC_RES/SHAPEVALUES));

        painter.drawPoint(x,y);
    }

   painter.end();
}

void oshshapesw::mouseMoveEvent(QMouseEvent *event)
{

    if (rw_mode){
        for (int i = 0; i < SHAPEVALUES; ++i) {
            if (shape_values[i].knob_area.contains(event->pos())) {
                shape_values[i].knob_color = knob_active_color;
            } else {
                shape_values[i].knob_color = knob_inactive_color;
            }

            if ((event->buttons() & Qt::LeftButton) &&
                (event->pos().y() > slider_radius) &&
                (event->pos().y() < widget_height + slider_radius) &&
                (shape_values[i].drag_state)) {
                    shape_values[i].knob_color = knob_move_color;
                    shape_values[i].knob_area.moveTop(event->pos().y() - slider_radius/2);
                    shape_values[i].Y_value = event->pos().y() - slider_radius/2;
                    shape_values[i].orig_value = ((MAX_ADC_RES-1) *  (widget_height - shape_values[i].Y_value + slider_radius/2)) /  widget_height;
                    emit knob_moved();
            }
        }

        update();
    }
}

void oshshapesw::mousePressEvent(QMouseEvent *event) {
    for (int i = 0; i < SHAPEVALUES; ++i) {
        if (shape_values[i].knob_area.contains(event->pos())) {
            shape_values[i].drag_state = true;
        }
    }
}

void oshshapesw::mouseReleaseEvent(QMouseEvent *event) {
    for (int i = 0; i < SHAPEVALUES; ++i) {
       shape_values[i].drag_state = false;
    }
}

int oshshapesw::getSplinePoint(int p1, int p2, int distance){
    return (p1 + ((p2 - p1)*distance)/(MAX_ADC_RES/SHAPEVALUES));
}

void oshshapesw::getAllPoints(uint16_t * array, uint8_t num_elements){
    if (num_elements > SHAPEVALUES) num_elements = SHAPEVALUES;

    for (int i = 0; i < num_elements; ++i) {
        array[i] = shape_values[i].orig_value;
    }
}

void oshshapesw::setAllPoints(uint16_t * array, uint8_t num_elements){
    if (num_elements > SHAPEVALUES) num_elements = SHAPEVALUES;

    for (int i = 0; i < num_elements; ++i) {
        shape_values[i].orig_value = array[i];
        shape_values[i].Y_value = ((((MAX_ADC_RES-1) - shape_values[i].orig_value) * widget_height) / (MAX_ADC_RES-1)) + slider_radius/2;
        if (shape_values[i].Y_value > (widget_height + slider_radius/2)) shape_values[i].Y_value = widget_height + slider_radius/2;
        if (shape_values[i].Y_value < 0) shape_values[i].Y_value = 0;
        shape_values[i].knob_area.moveTop(shape_values[i].Y_value);
    }
    update();
}

void oshshapesw::resizeEvent(QResizeEvent *event){
    repaintit();

}

void oshshapesw::repaintit() {
    slider_radius = (this->width() < 200) ? 1 : 16;
    widget_width = this->width() - (slider_radius + slider_radius);
    widget_height = this->height() - (slider_radius + slider_radius);

   for (uint8_t i=0; i<SHAPEVALUES; i++){
        shape_values[i].X_value = slider_radius/2 + ((widget_width*i)/(SHAPEVALUES-1));
        shape_values[i].Y_value = ((((MAX_ADC_RES-1) - shape_values[i].orig_value) * widget_height) / (MAX_ADC_RES-1)) + slider_radius/2;
        if (shape_values[i].Y_value > (widget_height + slider_radius/2)) shape_values[i].Y_value = widget_height + slider_radius/2;
        if (shape_values[i].Y_value < 0) shape_values[i].Y_value = 0;
        shape_values[i].knob_area.setRect(shape_values[i].X_value, shape_values[i].Y_value,
                                      slider_radius,slider_radius);
        shape_values[i].knob_color = knob_inactive_color;
        shape_values[i].drag_state = false;
    }

}

void oshshapesw::setReadOnlyMode(bool mode){
    if (mode) {
        rw_mode = false;
        curve_color = Qt::black;
        net_odd_color = Qt::lightGray;
    } else {
        rw_mode = true;
        curve_color = QColor(1,119,215);
        net_odd_color = Qt::black;
    }
    update();
}
