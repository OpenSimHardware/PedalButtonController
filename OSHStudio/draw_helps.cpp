#include "oshstudio.h"
#include "ui_oshstudio.h"

void OSHStudio::drawHelpSE() {
    struct se_store {
        uint8_t pina;
        uint8_t pinb;
        oshsingenc *SEwid;
    };
    se_store temp_store[MAX_SINGLE_ENCODERS];

    QString name_template_SE("widget_SE%1");
    QString SEHelp_text;

    // populate temp array
    for(int i =0; i < config.total_single_encoders; i++){
        temp_store[i].SEwid = ui->tabWidget->findChild<oshsingenc *>(name_template_SE.arg(i+1));
        temp_store[i].pina = temp_store[i].SEwid->getPinA();
        temp_store[i].pinb = temp_store[i].SEwid->getPinB();
        temp_store[i].SEwid->setAlarmPinA(false);
        temp_store[i].SEwid->setAlarmPinB(false);
 //       SEHelp_text = SEHelp_text + "Pin A - " + QString::number(temp_store[i].pina) + "type - " + QString::number(config.pin[temp_store[i].pina]) +
 //               ", Pin B - " + QString::number(temp_store[i].pinb) + "type - " + QString::number(config.pin[temp_store[i].pinb]) + "<br />";
        // check for type equality
        if (((config.pin[temp_store[i].pina] == Single_Rotary_PINA_1) &&
                (config.pin[temp_store[i].pinb] != Single_Rotary_PINB_1)) ||
            ((config.pin[temp_store[i].pina] == Single_Rotary_PINA_2) &&
                (config.pin[temp_store[i].pinb] != Single_Rotary_PINB_2)) ||
            ((config.pin[temp_store[i].pina] == Single_Rotary_PINA_4) &&
                (config.pin[temp_store[i].pinb] != Single_Rotary_PINB_4)))
        {
            temp_store[i].SEwid->setAlarmPinA(true);
            temp_store[i].SEwid->setAlarmPinB(true);
        }

    }

    // check for pins differentiality
    for(int i =0; i < config.total_single_encoders - 1; i++){
        for(int j =i +1; j < config.total_single_encoders; j++){
            if (temp_store[i].pina == temp_store[j].pina){
                temp_store[i].SEwid->setAlarmPinA(true);
                temp_store[j].SEwid->setAlarmPinA(true);
            }
            if (temp_store[i].pinb == temp_store[j].pinb){
                temp_store[i].SEwid->setAlarmPinB(true);
                temp_store[j].SEwid->setAlarmPinB(true);
            }
        }
    }

 //   ui->label_SEHelp->setText(SEHelp_text);
}


void OSHStudio::drawHelp()
{
    QString HelpText;

    if (NumberAnalogInputs) {
        HelpText = "<br />" + QString::number(NumberAnalogInputs) + " analog inputs <br />";
        if (NumberAnalogInputs > 7)
            HelpText = HelpText + "<font color='red'>Max 7 analog inputs (2 in combined axis)</font><br />";
    }

    if (Analog2Buttons_inputs)
        HelpText += "<br />" + QString::number(A2BButtons) + " buttons in "+  QString::number(Analog2Buttons_inputs) + " analog to buttons inputs <br />";

    if ((Chain_Rotaries_1 > 0) ||(Chain_Rotaries_2 > 0) || (Chain_Rotaries_4 > 0)) {
        HelpText = HelpText + "<br />" +
                QString::number(Chain_Rotaries_1 + Chain_Rotaries_2 + Chain_Rotaries_4) + " chained rotary encoders <br />";
        if ((Chain_PinA != 1) || (Chain_PinB != 1))
            HelpText = HelpText + "<font color='red'>You have to properly configure PINA and PINB pins of chained encoders</font><br /><br />";
    }

    if (config.total_single_encoders > 0) {
        HelpText = HelpText + "<br />" + QString::number(config.total_single_encoders) + " single rotary encoders <br />";
        if ((Single_Rotaries_PINA_1 != Single_Rotaries_PINB_1) || (Single_Rotaries_PINA_2 != Single_Rotaries_PINB_2) ||
                (Single_Rotaries_PINA_4 != Single_Rotaries_PINB_4))
            HelpText = HelpText + "<font color='red'>You have to properly configure PINA and PINB pins of single encoders</font><br /><br />";
    }

    if ((ButtonsRows>0) && (ButtonsColumns>0))
        HelpText = HelpText + "<br />" +
                QString::number((ButtonsRows * ButtonsColumns > MAX_BUTTONS) ? MAX_BUTTONS : ButtonsRows * ButtonsColumns) +
                " buttons in matrix <br />";

    if (ButtonsRows * ButtonsColumns > MAX_BUTTONS)
        HelpText = HelpText + "<font color='red'>No more than "+ QString::number(MAX_BUTTONS) + " buttons</font><br />";

    if ((ButtonsRows>0) && (!ButtonsColumns))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 column to matrix</font><br />";

    if ((!ButtonsRows) && (ButtonsColumns>0))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 row to matrix</font><br />";

    if (Buttons>0)
        HelpText = HelpText + "<br />" + QString::number(Buttons) + " single buttons <br />";


    if ((RotSwitchWires>0) && (RotSwitchPoles>0))
        HelpText = HelpText + "<br />" + QString::number(RotSwitchWires*RotSwitchPoles) + " buttons in Rotary Switch Config <br />";

    if ((RotSwitchWires>0) && (RotSwitchPoles<1))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 Pole to Rotary Switch Config</font><br />";

    if ((RotSwitchWires<1) && (RotSwitchPoles>0))
        HelpText = HelpText + "<font color='red'>You have to add at least 1 Wire to Rotary Switch Config</font><br />";


    ui->labelHelp->setText(HelpText);
}

void OSHStudio::drawHelpSB(){
    uint8_t joystick_buttons = 0;
    uint8_t joystick_shift_buttons = 0;
    uint8_t mouse_buttons = 0;
    uint8_t volume_buttons = 0;
    uint8_t POV1_buttons = 0;
    uint8_t POV2_buttons = 0;
    uint8_t POV3_buttons = 0;
    uint8_t POV4_buttons = 0;
    uint8_t keyboard_buttons = 0;
    uint8_t F_buttons = 0;
    QString HelpText;

    for(int i=0; i < TotalButtons; i++){
       switch (SBstore[i].button_type) {
       case(joystick_button):       joystick_buttons++; break;
       case(joysticksh1_button):    joystick_shift_buttons++; break;
       case(joysticksh2_button):    joystick_shift_buttons++; break;
       case(pov1up_button):
       case(pov1right_button):
       case(pov1down_button):
       case(pov1left_button):       POV1_buttons++; break;
       case(pov2up_button):
       case(pov2right_button):
       case(pov2down_button):
       case(pov2left_button):       POV2_buttons++; break;
       case(pov3up_button):
       case(pov3right_button):
       case(pov3down_button):
       case(pov3left_button):       POV3_buttons++; break;
       case(pov4up_button):
       case(pov4right_button):
       case(pov4down_button):
       case(pov4left_button):       POV4_buttons++; break;
       case(mouseleft_button):
       case(mousemiddle_button):
       case(mouseright_button):     mouse_buttons++; break;
       case(volumeup_button):
       case(volumedown_button):
       case(volumemute_button):     volume_buttons++; break;
       case(f1_button):
       case(f2_button):
       case(f3_button):
       case(f4_button):
       case(f5_button):
       case(f6_button):
       case(f7_button):
       case(f8_button):
       case(f9_button):
       case(f10_button):
       case(f11_button):
       case(f12_button):            F_buttons++; break;
       case(leftcontrol_button):
       case(leftshift_button):
       case(leftalt_button):
       case(leftgui_button):
       case(rightcontrol_button):
       case(rightshift_button):
       case(rightalt_button):
       case(rightgui_button):
       case(enter_button):
       case(escape_button):
       case(backspace_button):
       case(tab_button):
       case(space_button):
       case(insert_button):
       case(delete_button):
       case(home_button):
       case(end_button):
       case(pgup_button):
       case(pgdown_button):
       case(rightarrow_button):
       case(leftarrow_button):
       case(downarrow_button):
       case(uparrow_button):
       case(d0_button):
       case(d1_button):
       case(d2_button):
       case(d3_button):
       case(d4_button):
       case(d5_button):
       case(d6_button):
       case(d7_button):
       case(d8_button):
       case(d9_button):
       case(a_button):
       case(b_button):
       case(c_button):
       case(d_button):
       case(e_button):
       case(f_button):
       case(g_button):
       case(h_button):
       case(i_button):
       case(j_button):
       case(k_button):
       case(l_button):
       case(m_button):
       case(n_button):
       case(o_button):
       case(p_button):
       case(q_button):
       case(r_button):
       case(s_button):
       case(t_button):
       case(u_button):
       case(v_button):
       case(w_button):
       case(x_button):
       case(y_button):
       case(z_button):              keyboard_buttons++; break;
       }
     }

    if (joystick_buttons) {
        uint8_t total_joy_buttons = joystick_buttons;
        if (joystick_shift_buttons) total_joy_buttons *= (joystick_shift_buttons+1);
        HelpText = "<br />" + QString::number(total_joy_buttons) + " joystick buttons <br />";
    }

    if (POV1_buttons) {
        HelpText = HelpText + "<br />1st POV switch <br />";
        if (POV1_buttons%4) {
           HelpText = HelpText + "<font color='red'>Not complete config for POV1</font><br />";
        }
    }
    if (POV2_buttons) {
        HelpText = HelpText + "<br />2nd POV switch <br />";
        if (POV2_buttons%4) {
           HelpText = HelpText + "<font color='red'>Not complete config for POV2</font><br />";
        }
    }
    if (POV3_buttons) {
        HelpText = HelpText + "<br />3rd POV switch <br />";
        if (POV3_buttons%4) {
           HelpText = HelpText + "<font color='red'>Not complete config for POV3</font><br />";
        }
    }
    if (POV4_buttons) {
        HelpText = HelpText + "<br />4th POV switch <br />";
        if (POV4_buttons%4) {
           HelpText = HelpText + "<font color='red'>Not complete config for POV4</font><br />";
        }
    }


    if (mouse_buttons) {
        HelpText = HelpText + "<br />" + QString::number(mouse_buttons) + " mouse buttons <br />";
    }

    if (volume_buttons){
        HelpText = HelpText + "<br />" + QString::number(volume_buttons) + " volume buttons <br />";
    }

    if (F_buttons){
        HelpText = HelpText + "<br />" + QString::number(F_buttons) + " F-function buttons <br />";
    }

    if (keyboard_buttons){
        HelpText = HelpText + "<br />" + QString::number(keyboard_buttons) + " keyboard buttons <br />";
    }
    ui->labelHelp_SB->setText(HelpText);
}

