#include "oshstudio.h"
#include <QApplication>
#include <QLibraryInfo>

void ParseState(void);

int main(int argc, char *argv[])
{
    QString executable = argv[0];
    QString executablePath = executable.mid(0,executable.lastIndexOf("\\"));
    QString installPathPlugins = QLibraryInfo::location(QLibraryInfo::PluginsPath);
    QCoreApplication::removeLibraryPath(installPathPlugins);
    QCoreApplication::addLibraryPath(installPathPlugins);
    QCoreApplication::addLibraryPath(executablePath);

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("Hardware.ico"));
    OSHStudio w;
    w.show();

    return a.exec();
}

