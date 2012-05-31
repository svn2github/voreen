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

#include "voreen/core/remote/remotecontroller.h"

#include "voreen/core/network/networkevaluator.h"
#include "voreen/core/network/processornetwork.h"

using std::stringstream;
using std::string;

namespace voreen {

RemoteController::RemoteController() {}

RemoteController::~RemoteController() {}

void RemoteController::initialize() {}

void RemoteController::deinitialize() {}

void RemoteController::transmitPropertyChange(Property* property) {
    if (isConnected()) {
        stringstream stream;
        stream << CommandPrefixPython;
        stream << "voreen.setPropertyValue(\"" << property->getOwner()->getName() << "\",\"" << property->getID() << "\",";
        Variant v = property->getVariant();
        stream << v.getPythonString() << ");\r\n";
        string result = stream.str();

        sendMessage(result);
    }
}

void RemoteController::retrieveWorkspaceList() {
    if (isConnected()) {
        stringstream stream;
        stream << CommandPrefixRequestWorkspaceList << "\r\n";
        string result = stream.str();

        sendMessage(result);
    }
}

void RemoteController::loadRemoteWorkspace(const std::string& workspace) {
    if (isConnected()) {
        stringstream stream;
        stream << CommandPrefixLoadWorkspaceFile;
        stream << workspace << "\r\n";
        string result = stream.str();

        sendMessage(result);
    }
}

void RemoteController::loadActiveNetworkSource() {
    const ProcessorNetwork* network = VoreenApplication::app()->getNetworkEvaluator()->getProcessorNetwork();
    XmlSerializer s;
    s.serialize("ProcessorNetwork", network);
    std::stringstream stream;
    s.write(stream);
    std::string source = stream.str();
    loadNetworkSource(source);
}

void RemoteController::loadNetworkSource(const std::string& networkSource) {
    if (isConnected()) {
        stringstream stream;
        stream << CommandPrefixLoadNetworkSource;
        stream << networkSource << "\r\n";
        string result = stream.str();

        sendMessage(result);
    }
}

void RemoteController::receivedMessage(string msg) {
    const char* msgC = msg.c_str();
    if (msgC[0] == 19) // SGCT "connected" signal
        return; 
    if (msgC[0] == 'O' && msgC[1] == 'K' && msgC[2] == '\r' && msgC[3] == '\n') // ACK signal
        return; // we can't test for equality because there might be multiple "OK"s in the stream

    stringstream stream(msg);
    char commandCodeChar;
    stream >> commandCodeChar;
    int commandCode = atoi(&commandCodeChar);
    int totalSize = 0;
    for (int i = 7; i >= 0; --i) {
        char v;
        stream >> v;
        int vInt = atoi(&v);
        totalSize += static_cast<int>(vInt * pow(10.f, i));
    }

    LINFOC("voreen.RemoteController", "Message Length (msg): " << msg.size());
    LINFOC("voreen.RemoteController", "Message Length (hdr): " << totalSize);
    switch (commandCode) {
    case CommandPrefixRequestWorkspaceList:
        notifyObserversWorkspaceList(msg.substr(9));
        break;
    case CommandPrefixPropertyList:
        break;
    default:
#ifdef VRN_DEBUG
        LINFOC("voreen.RemoteController", "Unknown Command Code: " << commandCode);
        LINFOC("voreen.RemoteController", "Message: " << msg);
#endif
        break;
    }
}

void RemoteController::notifyObserversWorkspaceList(const std::string& msg) {
    const std::vector<RemoteControllerObserver*>& observers = getObservers();
    for (size_t i = 0; i < observers.size(); ++i) {
        RemoteControllerObserver* observer = observers[i];
        observer->receivedWorkspaceList(msg);
    }

}

void RemoteController::notifyObserversConnectionChanged(RemoteControllerObserver::ConnectionStatus status) {
    const std::vector<RemoteControllerObserver*>& observers = getObservers();
    for (size_t i = 0; i < observers.size(); ++i) {
        RemoteControllerObserver* observer = observers[i];
        observer->connectionStatusChanged(status);
    }
}

void RemoteController::notifyObserversErrorOccurred(RemoteControllerObserver::ConnectionError error) {
    const std::vector<RemoteControllerObserver*>& observers = getObservers();
    for (size_t i = 0; i < observers.size(); ++i) {
        observers[i]->errorOccurred(error);
    }
}

} // namespace
