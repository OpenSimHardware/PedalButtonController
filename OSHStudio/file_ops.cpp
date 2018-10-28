#include "oshstudio.h"
#include "ui_oshstudio.h"
#include<QMessageBox>

void OSHStudio::loadFromFile()
{
    uint8_t stored_version = 0;

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Config File"), "",
        tr("OSH Config Files (*.osh);;All Files (*)"));

    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
                if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
                }
                file.seek(offsetof(total_config_, config_version));
                file.read(reinterpret_cast<char*>(&stored_version), 1);
                if (stored_version == FIRMWARERELEASE) {
                    file.seek(0);
                    file.read(reinterpret_cast<char*>(&config.packet_id1), sizeof(total_config_));
                    file.close();
                    setConfig_Slot();
                } else {
                    QMessageBox::warning(this, tr("Nope!"),
                                         tr("It seems the file has wrong FW version"));
                }
        }
}

void OSHStudio::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Config File"), "",
        tr("OSH Config Files (*.osh);;All Files (*)"));

    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
                }
            gatherConfig_Slot();
            file.write(reinterpret_cast<char*>(&config.packet_id1), sizeof(total_config_));
            file.close();
        }
}
