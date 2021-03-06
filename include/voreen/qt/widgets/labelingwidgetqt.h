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

#ifndef LABELINGWIDGETQT_H
#define LABELINGWIDGETQT_H

#include "modules/base/processors/image/labeling.h"

#include <QTabWidget>
#include <QListWidget>

namespace voreen {

class LabelingWidgetQt : public QWidget, LabelingWidget {
    Q_OBJECT
public:
    LabelingWidgetQt(QWidget* parent=0);
    std::string showInputDialog(const std::string &title,
                                const std::string &label,
                                const std::string &text);

public slots:
    void selectionChanged(QListWidgetItem* item=0);

protected:
    virtual void createWidgets();
    virtual void createConnections();

    QTabWidget* tabWidget_;
    std::vector<QListWidget*> listWidgets_;
};

}
#endif
