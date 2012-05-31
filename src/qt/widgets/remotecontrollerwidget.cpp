/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Created between 2005 and 2012 by The Voreen Team                   *
 * as listed in CREDITS.TXT <http://www.voreen.org>                   *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

#include "voreen/qt/widgets/remotecontrollerwidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace voreen {

RemoteControllerWidget::RemoteControllerWidget(QWidget* parent)     
    : QWidget(parent) 
{
    RemoteController* controller = VoreenApplication::app()->getRemoteController();
    controller->addObserver(this);

    QBoxLayout* layout = new QVBoxLayout(this);

    QGroupBox* topGroupBox = new QGroupBox(tr("Server"));
    QGridLayout* topGroupLayout = new QGridLayout(topGroupBox);
    QLabel* ipAddressLabel = new QLabel(tr("IP Address"));
    topGroupLayout->addWidget(ipAddressLabel, 0, 0);
    ipAddressEdit_ = new QLineEdit("127.0.0.1");
    topGroupLayout->addWidget(ipAddressEdit_, 0, 1);
    portEdit_ = new QLineEdit("20500");
    topGroupLayout->addWidget(portEdit_, 0, 2, 1, 1, Qt::AlignLeft);
    connectionStatusLabel_ = new QLabel;
    topGroupLayout->addWidget(connectionStatusLabel_, 1, 0, 1, 3);
    connectButton_ = new QPushButton(tr("Connect"));
    topGroupLayout->addWidget(connectButton_, 2, 0, 1, 3);
    connect(connectButton_, SIGNAL(clicked(bool)), this, SLOT(connectButtonPressed()));
    layout->addWidget(topGroupBox);

    QGroupBox* workspacesGroupBox = new QGroupBox(tr("Workspaces"));
    QGridLayout* workspacesLayout = new QGridLayout(workspacesGroupBox);
    workspacesListWidget_ = new QListWidget;
    workspacesLayout->addWidget(workspacesListWidget_, 0, 0, 1, 3);

    QPushButton* sendActiveNetworkButton = new QPushButton(tr("Send active Network"));
    connect(sendActiveNetworkButton, SIGNAL(clicked(bool)), this, SLOT(sendActiveNetworkButtonPressed()));
    workspacesLayout->addWidget(sendActiveNetworkButton, 1, 0, 1, 1, Qt::AlignLeft);

    QPushButton* loadWorkspaceButton = new QPushButton(tr("Load"));
    connect(loadWorkspaceButton, SIGNAL(clicked(bool)), this, SLOT(loadRemoteWorkspaceButtonPressed()));
    workspacesLayout->addWidget(loadWorkspaceButton, 1, 2, 1, 1, Qt::AlignRight);

    layout->addWidget(workspacesGroupBox);

    layout->addStretch();
}

RemoteControllerWidget::~RemoteControllerWidget() {
    RemoteController* controller = VoreenApplication::app()->getRemoteController();
    controller->removeObserver(this);
}

void RemoteControllerWidget::connectButtonPressed() {
    RemoteController* controller = VoreenApplication::app()->getRemoteController();
    if (controller->isConnected()) {
        controller->disconnect();
    }
    else {
        ipAddress_ = ipAddressEdit_->text();
        std::string ipAddress = ipAddress_.toStdString();
        int port = portEdit_->text().toInt();
        controller->connectToAddress(ipAddress, port);
    }
}

void RemoteControllerWidget::loadRemoteWorkspaceButtonPressed() {
    QListWidgetItem* currentItem =  workspacesListWidget_->currentItem();

    if (currentItem) {
        QString workspace =currentItem->text();
        RemoteController* controller = VoreenApplication::app()->getRemoteController();
        controller->loadRemoteWorkspace(workspace.toStdString());
    }
}

void RemoteControllerWidget::sendActiveNetworkButtonPressed() {
    RemoteController* controller = VoreenApplication::app()->getRemoteController();
    controller->loadActiveNetworkSource();
}

void RemoteControllerWidget::connectionStatusChanged(ConnectionStatus newStatus) {
    RemoteController* controller = VoreenApplication::app()->getRemoteController();
    switch (newStatus) {
    case ConnectionStatusConnecting:
        connectionStatusLabel_->setText(tr("Connecting..."));
        connectButton_->setText(tr("Disconnect"));
        break;
    case ConnectionStatusConnected:
        connectionStatusLabel_->setText(tr("Connected to ") + ipAddress_);
        connectButton_->setText(tr("Disconnect"));
        controller->retrieveWorkspaceList();
        break;
    case ConnectionStatusDisconnected:
        connectionStatusLabel_->setText("");
        connectButton_->setText(tr("Connect"));
        workspacesListWidget_->clear();
        break;
    }
}

void RemoteControllerWidget::errorOccurred(ConnectionError error) {
    connectButton_->setText(tr("Connect"));
    switch (error) {
    case ConnectionErrorRemoteHostClosed:
        connectionStatusLabel_->setText(tr("Connection Error: Remote Host Closed"));
        break;
    case ConnectionErrorHostNotFound:
        connectionStatusLabel_->setText(tr("Connection Error: Host Not Found"));
        break;
    case ConnectionErrorConnectionRefused:
        connectionStatusLabel_->setText(tr("Connection Error: Connection Refused"));
        break;
    case ConnectionErrorTimeOut:
        connectionStatusLabel_->setText(tr("Connection Error: Socket Timeout"));
        break;
    case ConnectionErrorOther:
        connectionStatusLabel_->setText(tr("Connection Error: Unknown Error"));
        break;
    }
    workspacesListWidget_->clear();
}

void RemoteControllerWidget::receivedWorkspaceList(const std::string& list) {
    std::stringstream stream(list);
    QStringList workspaces;
    std::string token;
    while (stream >> token)
        workspaces.append(QString::fromStdString(token));


    workspaces.sort();

    workspacesListWidget_->addItems(workspaces);
}

} // namespace
