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

#include "voreen/qt/remotecontrollerqt.h"

#include "voreen/core/properties/property.h"
#include "modules/python/core/pyvoreen.h"

#include <QTcpSocket>

namespace voreen {

RemoteControllerQt::RemoteControllerQt() 
    : QObject()
    , RemoteController()
    , tcpSocket_(0)
{}

RemoteControllerQt::~RemoteControllerQt() {}

void RemoteControllerQt::initialize() {
    tcpSocket_ = new QTcpSocket(this);
    connect(tcpSocket_, SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(errorOccurred(QAbstractSocket::SocketError)));
    connect(tcpSocket_, SIGNAL(readyRead()), this, SLOT(dataAvailableForRead()));

    notifyObserversConnectionChanged(RemoteControllerObserver::ConnectionStatusDisconnected);
}

void RemoteControllerQt::deinitialize() {
    tcpSocket_->close();
}

void RemoteControllerQt::connectToAddress(const std::string& ipAddress, int port) {
    tcpSocket_->connectToHost(QString::fromStdString(ipAddress), port);
    notifyObserversConnectionChanged(RemoteControllerObserver::ConnectionStatusConnecting);
    bool success = tcpSocket_->waitForConnected(5000);
    if (success) {
        notifyObserversConnectionChanged(RemoteControllerObserver::ConnectionStatusConnected);
    }
    else
        errorOccurred(tcpSocket_->error());
}

void RemoteControllerQt::disconnect() {
    tcpSocket_->disconnectFromHost();
    notifyObserversConnectionChanged(RemoteControllerObserver::ConnectionStatusDisconnected);
}

bool RemoteControllerQt::isConnected() const {
    return tcpSocket_->state() == QAbstractSocket::ConnectedState;
}

void RemoteControllerQt::sendMessage(const std::string& msg) {
    QByteArray block(msg.c_str(), msg.size());
    tcpSocket_->write(block);
    tcpSocket_->waitForBytesWritten();
}

void RemoteControllerQt::dataAvailableForRead() {
    QByteArray block = tcpSocket_->readAll();
    const char* data = block.data();
    std::string fullStringData(data);
    receivedMessage(fullStringData);
}

void RemoteControllerQt::errorOccurred(QAbstractSocket::SocketError socketError) {
    RemoteControllerObserver::ConnectionError error;
    switch (socketError) {
     case QAbstractSocket::RemoteHostClosedError:
         error = RemoteControllerObserver::ConnectionErrorRemoteHostClosed;
         break;
     case QAbstractSocket::HostNotFoundError:
         error = RemoteControllerObserver::ConnectionErrorHostNotFound;
         break;
     case QAbstractSocket::ConnectionRefusedError:
         error = RemoteControllerObserver::ConnectionErrorConnectionRefused;
         break;
     case QAbstractSocket::SocketTimeoutError:
         error = RemoteControllerObserver::ConnectionErrorTimeOut;
         break;
     default:
         error = RemoteControllerObserver::ConnectionErrorOther;
         break;
    }

    notifyObserversErrorOccurred(error);
}

} // namespace
