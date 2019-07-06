#include "oshbuttonw.h"
#include "ui_oshbuttonw.h"
#include <QMenu>
#include <QPainter>

oshbuttonw::oshbuttonw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oshbuttonw)
{
    ui->setupUi(this);

    QMenu *xmenu = new QMenu();
        QMenu* submenuJ = xmenu->addMenu( "Joystick" );
        QMenu* submenuP = xmenu->addMenu( "POV" );
        QMenu* submenuM = xmenu->addMenu( "Mouse" );
        QMenu* submenuV = xmenu->addMenu( "Volume" );
        QMenu* submenuMM = xmenu->addMenu( "Multimedia" );
        QMenu* submenuK = xmenu->addMenu( "Keyboard" );
        QMenu* submenuKM = submenuK->addMenu( "Modifiers" );
        QMenu* submenuKF = submenuK->addMenu( "F's" );
        QMenu* submenuKS = submenuK->addMenu( "Specials" );
        QMenu* submenuKD = submenuK->addMenu( "Digits" );
        QMenu* submenuKL = submenuK->addMenu( "Letters" );
        for (uint8_t i=0; i<MENUELEM; ++i){
            if (button_namings[i].parent_menu == "Joystick") submenuJ->addAction(button_namings[i].element_menu);
            if (button_namings[i].parent_menu == "POV") submenuP->addAction(button_namings[i].element_menu);
            if (button_namings[i].parent_menu == "Mouse") submenuM->addAction(button_namings[i].element_menu);
            if (button_namings[i].parent_menu == "Volume") submenuV->addAction(button_namings[i].element_menu);
            if (button_namings[i].parent_menu == "Multimedia") submenuMM->addAction(button_namings[i].element_menu);
            if (button_namings[i].parent_menu == "Modifiers") submenuKM->addAction(button_namings[i].element_menu);
            if (button_namings[i].parent_menu == "F's") submenuKF->addAction(button_namings[i].element_menu);
            if (button_namings[i].parent_menu == "Specials") submenuKS->addAction(button_namings[i].element_menu);
            if (button_namings[i].parent_menu == "Digits") submenuKD->addAction(button_namings[i].element_menu);
            if (button_namings[i].parent_menu == "Letters") submenuKL->addAction(button_namings[i].element_menu);
        }
    ui->pushButton->setMenu(xmenu);
    set_button_state(false);
    set_button_type(joystick_button);
    connect(xmenu, SIGNAL(triggered(QAction*)), SLOT(slotActivated(QAction*)));
}

oshbuttonw::~oshbuttonw()
{
    delete ui;
}

void oshbuttonw::set_button_state(bool state)
{
    if (state) {
        ui->pushButton->setStyleSheet("QPushButton::menu-indicator{ image: none; width: 0px; }"
                                      "QPushButton {background-image: url(:/Images/ON_small_t.png); color: yellow; padding-bottom: 8px;}");
    } else {
        ui->pushButton->setStyleSheet("QPushButton::menu-indicator{ image: none; width: 0px; }"
                                      "QPushButton {background-image: url(:/Images/OFF_small_t.png); color: yellow; padding-bottom: 8px;}");
    }
}

void oshbuttonw::set_button_text(QString text){
    ui->pushButton->setText(text);
}

button_mode oshbuttonw::get_button_type(void){
    return current_button_type;
}

void oshbuttonw::set_button_type(button_mode type){
    for (uint8_t i=0; i<MENUELEM; ++i){
        if (type == button_namings[i].button_type) {
            ui->pushButton->setText(button_namings[i].short_abbr);
            ui->pushButton->setToolTip(button_namings[i].element_menu);
        }
    }
    current_button_type = type;
  //  emit button_type_changed();
}

void oshbuttonw::slotActivated(QAction* pAction)
{
    QString text_selected = pAction->text().remove("&");
    for (uint8_t i=0; i<MENUELEM; ++i){
        if (text_selected == button_namings[i].element_menu) {
            set_button_type(button_namings[i].button_type);
        }
    }
    emit button_type_changed();
}
