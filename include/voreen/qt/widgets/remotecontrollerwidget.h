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

#ifndef VRN_REMOTECONTROLLERWIDGET_H
#define VRN_REMOTECONTROLLERWIDGET_H

#include <QWidget>

#include "voreen/core/remote/remotecontroller.h"
#include "voreen/qt/voreenqtdefine.h"

class QLabel;
class QLineEdit;
class QListWidget;
class QPushButton;

namespace voreen {

class VRN_QT_API RemoteControllerWidget : public QWidget, public RemoteControllerObserver {
Q_OBJECT
public:
    RemoteControllerWidget(QWidget* parent = 0);
    ~RemoteControllerWidget();

    void connectionStatusChanged(ConnectionStatus newStatus);
    void errorOccurred(ConnectionError error);
    void receivedWorkspaceList(const std::string& list);

private slots:
    void connectButtonPressed();
    void loadRemoteWorkspaceButtonPressed();
    void sendActiveNetworkButtonPressed();

private:
    QLineEdit* ipAddressEdit_;
    QLineEdit* portEdit_;
    QLabel* connectionStatusLabel_;
    QPushButton* connectButton_;
    QListWidget* workspacesListWidget_;

    QString ipAddress_;
};


} // namespace

#endif // VRN_REMOTECONTROLLERWIDGET_H
