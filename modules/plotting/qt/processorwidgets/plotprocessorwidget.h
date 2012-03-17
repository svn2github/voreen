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

#ifndef VRN_PLOTPROCESSORWIDGET_H
#define VRN_PLOTPROCESSORWIDGET_H

#include "../../processors/plotprocessor.h"
#include "voreen/qt/widgets/processor/qprocessorwidget.h"

class QPushButton;
class QFileDialog;
class QLabel;
class QComboBox;
class QCheckBox;

namespace voreen {


class PlotProcessorWidget : public QProcessorWidget {
    Q_OBJECT
public:
    PlotProcessorWidget(QWidget* parent, PlotProcessor* PlotProcessor);
    virtual ~PlotProcessorWidget();

    void initialize();

    virtual void updateFromProcessor();

private:

    QLabel* switchLabel_;
    QComboBox* switchBox_;
    QPushButton* saveFile_;
    QFileDialog* file_;
    QPushButton* updateFile_;
    QLabel* fileLabel_;
    QCheckBox* viewportClipping_;

    std::string svgFileName_;

private slots:

    void savereleased();
    void updateFileReleased();
    void updateObjectSwitch(int index);
    void changeViewPortClipping(int state);

};

} // namespace voreen

#endif // VRN_PLOTDATAFITFUNCTIONWIDGET_H

