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

#ifndef VRN_REMOTECONTROLLER_H
#define VRN_REMOTECONTROLLER_H

#include "voreen/core/utils/observer.h"
#include "voreen/core/voreencoredefine.h"

namespace voreen {

class Property;

class VRN_CORE_API RemoteControllerObserver : public Observer {
public:
    enum ConnectionStatus {
        ConnectionStatusDisconnected = 0,
        ConnectionStatusConnecting,
        ConnectionStatusConnected
    };

    enum ConnectionError {
        ConnectionErrorRemoteHostClosed = 0,
        ConnectionErrorHostNotFound,
        ConnectionErrorConnectionRefused,
        ConnectionErrorTimeOut,
        ConnectionErrorOther
    };

    virtual void connectionStatusChanged(ConnectionStatus /*newStatus*/) {};
    virtual void receivedWorkspaceList(const std::string& /*list*/) {};
    virtual void errorOccurred(ConnectionError /*error*/) {} ; 
};

class VRN_CORE_API RemoteController : public Observable<RemoteControllerObserver> {
public:
    RemoteController();
    ~RemoteController();

    virtual void initialize();
    virtual void deinitialize();

    virtual bool isConnected() const = 0;

    virtual void connectToAddress(const std::string& ipAddress, int port) = 0;
    virtual void disconnect() = 0;

    void transmitPropertyChange(Property* property);
    void retrieveWorkspaceList();
    void loadRemoteWorkspace(const std::string& workspace);
    void loadActiveNetworkSource();
    void loadNetworkSource(const std::string& networkSource);

protected:
    enum CommandPrefix {
        CommandPrefixPython = 0,
        CommandPrefixRequestWorkspaceList = 1,
        CommandPrefixLoadWorkspaceFile = 2,
        CommandPrefixPropertyList = 3,
        CommandPrefixLoadNetworkSource = 4
    };

    virtual void sendMessage(const std::string& msg) = 0;
    void receivedMessage(std::string msg);

    void notifyObserversWorkspaceList(const std::string& msg);
    void notifyObserversConnectionChanged(RemoteControllerObserver::ConnectionStatus status);
    void notifyObserversErrorOccurred(RemoteControllerObserver::ConnectionError error);
};

} // namespace

#endif // VRN_REMOTECONTROLLER_H
