#ifndef OSHBUTTONW_H
#define OSHBUTTONW_H

#include <QWidget>
#include "../common_types/common_structs.h"

#define MENUELEM 103

struct button_namings_ {
    QString parent_menu;
    QString element_menu;
    QString short_abbr;
    button_mode button_type;
};


namespace Ui {
class oshbuttonw;
}

class oshbuttonw : public QWidget
{
    Q_OBJECT

public:
    explicit oshbuttonw(QWidget *parent = nullptr);
    ~oshbuttonw();

private slots:
    void set_button_text(QString text);
    void slotActivated(QAction* pAction);

private:
    Ui::oshbuttonw *ui;
    button_mode current_button_type;
    button_namings_ const button_namings[MENUELEM] = {
        {"Joystick", "Joystick button", "Joy",          joystick_button,},
//        {"Joystick", "Shift1 Joystick button", "JoySh1",joysticksh1_button,},
//        {"Joystick", "Shift2 Joystick button", "JoySh2",joysticksh2_button},
        {"POV", "POV1 Up", "POV1U",                     pov1up_button},
        {"POV", "POV1 Right", "POV1R",                  pov1right_button},
        {"POV", "POV1 Down", "POV1D",                   pov1down_button},
        {"POV", "POV1 Left", "POV1L",                   pov1left_button},
        {"POV", "POV2 Up", "POV2U",                     pov2up_button},
        {"POV", "POV2 Right", "POV2R",                  pov2right_button},
        {"POV", "POV2 Down", "POV2D",                   pov2down_button},
        {"POV", "POV2 Left", "POV1L",                   pov2left_button},
        {"POV", "POV3 Up", "POV3U",                     pov3up_button},
        {"POV", "POV3 Right", "POV3R",                  pov3right_button},
        {"POV", "POV3 Down", "POV3D",                   pov3down_button},
        {"POV", "POV3 Left", "POV3L",                   pov3left_button},
        {"POV", "POV4 Up", "POV4U",                     pov4up_button},
        {"POV", "POV4 Right", "POV4R",                  pov4right_button},
        {"POV", "POV4 Down", "POV4D",                   pov4down_button},
        {"POV", "POV4 Left", "POV4L",                   pov4left_button},
        {"Mouse", "Left Mouse Button", "MouseL",        mouseleft_button},
        {"Mouse", "Middle Mouse Button", "MouseM",      mousemiddle_button},
        {"Mouse", "Right Mouse Button", "MouseR",       mouseright_button},
        {"Volume", "Volume Up", "VolU",                 volumeup_button},
        {"Volume", "Volume Down", "VolD",               volumedown_button},
        {"Volume", "Volume Mute/UnMute", "VolM",        volumemute_button},
        {"Modifiers", "Left Control", "LCntl",          leftcontrol_button},
        {"Modifiers", "Left Shift", "LShft",            leftshift_button},
        {"Modifiers", "Left Alt", "LAlt",               leftalt_button},
        {"Modifiers", "Left GUI", "LGUI",               leftgui_button},
        {"Modifiers", "Right Control", "RCntl",         rightcontrol_button},
        {"Modifiers", "Right Shift", "RShft",           rightshift_button},
        {"Modifiers", "Right Alt", "RAlt",              rightalt_button},
        {"Modifiers", "Right GUI", "RGUI",              rightgui_button},
        {"F's", "F1", "F1",                             f1_button},
        {"F's", "F2", "F2",                             f2_button},
        {"F's", "F3", "F3",                             f3_button},
        {"F's", "F4", "F4",                             f4_button},
        {"F's", "F5", "F5",                             f5_button},
        {"F's", "F6", "F6",                             f6_button},
        {"F's", "F7", "F7",                             f7_button},
        {"F's", "F8", "F8",                             f8_button},
        {"F's", "F9", "F9",                             f9_button},
        {"F's", "F10", "F10",                           f10_button},
        {"F's", "F11", "F11",                           f11_button},
        {"F's", "F12", "F12",                           f12_button},
        {"Specials", "Enter", "Enter",                  enter_button},
        {"Specials", "Escape", "Esc",                   escape_button},
        {"Specials", "Backspace", "Bkspace",            backspace_button},
        {"Specials", "Tab", "Tab",                      tab_button},
        {"Specials", "Space", "Space",                  space_button},
        {"Specials", "Insert", "Insert",                insert_button},
        {"Specials", "Delete", "Delete",                delete_button},
        {"Specials", "Home", "Home",                    home_button},
        {"Specials", "End", "End",                      end_button},
        {"Specials", "Page Up", "PgUp",                 pgup_button},
        {"Specials", "Page Down", "PgDn",               pgdown_button},
        {"Specials", "Right Arrow", "RArrow",           rightarrow_button},
        {"Specials", "Left Arrow", "LArrow",            leftarrow_button},
        {"Specials", "Down Arrow", "DArrow",            downarrow_button},
        {"Specials", "Up Arrow", "UArrow",              uparrow_button},
//        {"Multimedia", "Audio Player", "Player",        player_button},
        {"Multimedia", "Play", "Play",                  play_button},
        {"Multimedia", "Stop", "Stop",                  stop_button},
//        {"Multimedia", "Eject", "Eject",                eject_button},
        {"Multimedia", "Scan Next", "Next",             next_button},
        {"Multimedia", "Scan Previous", "Prev",         prev_button},
        {"Multimedia", "Calculator", "Calc",            calc_button},
//        {"Multimedia", "Control Panel", "CPanel",       cpanel_button},
//        {"Multimedia", "Task Manager", "TaskMan",       taskman_button},
        {"Multimedia", "Explorer", "Explorer",            explorer_button},
//        {"Multimedia", "Browser", "Browser",            browser_button},
        {"Multimedia", "Browser Home", "BrowsHom",      browserhome_button},
        {"Multimedia", "Browser Back", "BrowsBak",      browserback_button},
        {"Multimedia", "Browser Forward", "BrowsFrw",   browserforward_button},
        {"Digits", "0", "0",                            d0_button},
        {"Digits", "1", "1",                            d1_button},
        {"Digits", "2", "2",                            d2_button},
        {"Digits", "3", "3",                            d3_button},
        {"Digits", "4", "4",                            d4_button},
        {"Digits", "5", "5",                            d5_button},
        {"Digits", "6", "6",                            d6_button},
        {"Digits", "7", "7",                            d7_button},
        {"Digits", "8", "8",                            d8_button},
        {"Digits", "9", "9",                            d9_button},
        {"Letters", "a", "a",                           a_button},
        {"Letters", "b", "b",                           b_button},
        {"Letters", "c", "c",                           c_button},
        {"Letters", "d", "d",                           d_button},
        {"Letters", "e", "e",                           e_button},
        {"Letters", "f", "f",                           f_button},
        {"Letters", "g", "g",                           g_button},
        {"Letters", "h", "h",                           h_button},
        {"Letters", "i", "i",                           i_button},
        {"Letters", "j", "j",                           j_button},
        {"Letters", "k", "k",                           k_button},
        {"Letters", "l", "l",                           l_button},
        {"Letters", "m", "m",                           m_button},
        {"Letters", "n", "n",                           n_button},
        {"Letters", "o", "o",                           o_button},
        {"Letters", "p", "p",                           p_button},
        {"Letters", "q", "q",                           q_button},
        {"Letters", "r", "r",                           r_button},
        {"Letters", "s", "s",                           s_button},
        {"Letters", "t", "t",                           t_button},
        {"Letters", "u", "u",                           u_button},
        {"Letters", "v", "v",                           v_button},
        {"Letters", "w", "w",                           w_button},
        {"Letters", "x", "x",                           x_button},
        {"Letters", "y", "y",                           y_button},
        {"Letters", "z", "z",                           z_button},
    };


public slots:
    void set_button_state(bool state);
    button_mode get_button_type(void);
    void set_button_type(button_mode);

signals:
    void button_type_changed();
};

#endif // OSHBUTTONW_H
