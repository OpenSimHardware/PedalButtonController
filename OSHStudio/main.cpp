#include "oshstudio.h"
#include <QApplication>

void ParseState(void);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("Hardware.ico"));
    OSHStudio w;
    w.show();

    return a.exec();
}

