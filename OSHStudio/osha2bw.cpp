#include "osha2bw.h"
#include "ui_osha2bw.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPolygon>



osha2bw::osha2bw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::osha2bw)
{
    ui->setupUi(this);
    buttonsCount=1;

    sliders[0].IntLabel = ui->label_1;
    sliders[1].IntLabel = ui->label_2;
    sliders[2].IntLabel = ui->label_3;
    sliders[3].IntLabel = ui->label_4;
    sliders[4].IntLabel = ui->label_5;
    sliders[5].IntLabel = ui->label_6;
    sliders[6].IntLabel = ui->label_7;
    sliders[7].IntLabel = ui->label_8;
    sliders[8].IntLabel = ui->label_9;
    sliders[9].IntLabel = ui->label_10;

    for (uint8_t i=0;i<MAX_A2B_BUTTONS;i++){
        sliders[i].PinPoly << points[0] << points[1] << points[2] << points[3] << points[4];
        sliders[i].PinColor = QColor(1,119,215);
        sliders[i].PinDrag = false;
        sliders[i].PinPosX = offset;
        sliders[i].IntLabel->setVisible(false);
    }

    draw_default_sliders(buttonsCount);
}

osha2bw::~osha2bw()
{
    delete ui;
}

void osha2bw::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    int width,tmp;


    width = ui->AxisValue->width();
    tmp = width/20;

    painter.begin(this);
    painter.setPen(Qt::lightGray);
    painter.drawRect(QRect(offset,7,width,2));
    for (uint8_t i=0; i<21; i++){
        painter.drawLine((i*tmp)+offset,15,(i*tmp)+offset,18);
    }
    for (uint8_t i=0; i<buttonsCount;i++){
        painter.setBrush(sliders[i].PinColor);
        painter.setPen(sliders[i].PinColor);
        painter.drawPolygon(sliders[i].PinPoly, Qt::WindingFill);
    }
    painter.end();
}

void osha2bw::mouseMoveEvent(QMouseEvent *event)
{
    for (uint8_t i=0;i<buttonsCount;i++){
        if (sliders[i].PinPoly.containsPoint(event->pos(),Qt::WindingFill)) {
                sliders[i].PinColor = Qt::black;
        } else sliders[i].PinColor = QColor(1,119,215);

        if (event->buttons() & Qt::LeftButton)
            drawPin(event->pos(), i);

        if (sliders[i].PinDrag) {
            sliders[i].PinColor=Qt::lightGray;
        }
    }
    update();
}

void osha2bw::drawPin(QPoint pinpos, uint8_t slider) {
    uint16_t pinvalue=0;

    if ((pinpos.x()<offset) || pinpos.x()>ui->AxisValue->width()+offset) {
        return;
    }

    if ((sliders[slider].PinDrag) && pinpos.x()<(ui->AxisValue->width()+offset)) {
        pinvalue = checkPinValue(pinpos.x(), slider);
        fillPolygonArray(pinvalue, slider);
        sliders[slider].PinPosX = pinvalue;
        setLableValue(slider);
        return;
    }
}

void osha2bw::mousePressEvent(QMouseEvent *event) {
    for (uint8_t i=0;i<buttonsCount;i++){
        if (sliders[i].PinPoly.containsPoint(event->pos(),Qt::WindingFill)) {
            sliders[i].PinDrag = true;
        }
    }
}

void osha2bw::mouseReleaseEvent(QMouseEvent *event) {
    for (uint8_t i=0;i<buttonsCount;i++){
        sliders[i].PinDrag = false;
    }
}

void osha2bw::fillPolygonArray(uint16_t value, uint8_t whichSlider) {
        points[0].setX(value-7);
        points[1].setX(value-7);
        points[2].setX(value-3);
        points[3].setX(value);
        points[4].setX(value);
        sliders[whichSlider].PinPoly.setPoint(0, points[0]);
        sliders[whichSlider].PinPoly.setPoint(1, points[1]);
        sliders[whichSlider].PinPoly.setPoint(2, points[2]);
        sliders[whichSlider].PinPoly.setPoint(3, points[3]);
        sliders[whichSlider].PinPoly.setPoint(4, points[4]);
}

void osha2bw::setLableValue(uint8_t whichSlider){
    sliders[whichSlider].IntLabel->move(sliders[whichSlider].PinPosX-13,16);
    sliders[whichSlider].IntLabel->setText(QString::number((sliders[whichSlider].PinPosX - offset)*MAX_RESOLUTION/(ui->AxisValue->width())));
    sliders[whichSlider].IntLabel->setVisible(true);
}

uint16_t osha2bw::checkPinValue(uint16_t pinvalue, uint8_t slider_number) {
    if (pinvalue >= (ui->AxisValue->width()+offset)) pinvalue=ui->AxisValue->width()+offset;
    if (pinvalue < offset) pinvalue=offset;
    if (slider_number > 0){
        if (pinvalue < (sliders[slider_number-1].PinPosX+7)) pinvalue = sliders[slider_number-1].PinPosX+7;
    }
    if (slider_number < buttonsCount-1){
        if (pinvalue > (sliders[slider_number+1].PinPosX-7)) pinvalue = sliders[slider_number+1].PinPosX-7;
    }
    return pinvalue;
}

void osha2bw::on_spinBox_valueChanged(int arg1){
    buttonsCount = arg1;
    draw_default_sliders(buttonsCount);
    emit buttons_number_changed();
}

void osha2bw::draw_default_sliders(uint8_t sliders_number){
    for (uint8_t i=0;i<MAX_A2B_BUTTONS;i++){
        sliders[i].IntLabel->setVisible(false);
    }
    for (uint8_t i=0; i<sliders_number;i++){
        sliders[i].PinPosX = (ui->AxisValue->width()*(i+1)/(sliders_number+1)) + offset;
        fillPolygonArray(sliders[i].PinPosX, i);
        sliders[i].PinColor = QColor(1,119,215);
        sliders[i].PinDrag = false;
        setLableValue(i);
    }
    update();
}

uint8_t osha2bw::getButtonsCount(void){
    return buttonsCount;
}

void osha2bw::setButtonsCount(uint8_t number){
//    buttonsCount = number;
//    draw_default_sliders(number);
    ui->spinBox->setValue(number);
}

void osha2bw::getButtonsIntervals(uint8_t buttonsIntervals[]){
    for (uint8_t i=0;i<buttonsCount;i++){
        buttonsIntervals[i] = (sliders[i].PinPosX - offset)*MAX_RESOLUTION/(ui->AxisValue->width());
    }
}

void osha2bw::setButtonsIntervals(uint8_t buttonsIntervals[]){
    for (uint8_t i=0;i<buttonsCount;i++){
        sliders[i].PinPosX = ((ui->AxisValue->width()*buttonsIntervals[i])/MAX_RESOLUTION)+offset+1;
        fillPolygonArray(sliders[i].PinPosX, i);
        setLableValue(i);
    }
    update();
}

void osha2bw::setPinName(QString pin){
    ui->label_pinName->setText(pin);
}
