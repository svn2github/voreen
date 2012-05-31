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

#ifndef VRN_REMOTECONTROLLERQT_H
#define VRN_REMOTECONTROLLERQT_H

#include "voreen/core/remote/remotecontroller.h"
#include "voreen/qt/voreenqtdefine.h"

#include <QAbstractSocket>
#include <QObject>

class QTcpSocket;
class QNetworkSession;

namespace voreen {

class Property;

class VRN_QT_API RemoteControllerQt : public QObject, public RemoteController {
Q_OBJECT
public:
    RemoteControllerQt();
    ~RemoteControllerQt();

    void initialize();
    void deinitialize();

    bool isConnected() const;

    void connectToAddress(const std::string& ipAddress, int port);
    void disconnect();

private slots:
    void dataAvailableForRead();
    void errorOccurred(QAbstractSocket::SocketError);

private:
    void sendMessage(const std::string& msg);
    QTcpSocket* tcpSocket_;
};

} // namespace

#endif // VRN_REMOTECONTROLLERQT_H
