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

#include "plotprocessorwidgetfactory.h"

#include "voreen/qt/widgets/processor/qprocessorwidget.h"
#include "voreen/qt/voreenapplicationqt.h"

#include "plotdataprocessorwidget.h"
#include "plotdataselectwidget.h"
#include "plotdatagroupwidget.h"
#include "plotdatafitfunctionwidget.h"
#include "plotdatamergewidget.h"
#include "plotprocessorwidget.h"

#include <QWidget>
#include <QMainWindow>

namespace voreen {

ProcessorWidget* PlotProcessorWidgetFactory::createWidget(Processor* processor) const {

    if (!VoreenApplicationQt::qtApp()) {
        LERRORC("voreen.plotting.PlotProcessorWidgetFactory", "VoreenApplicationQt not instantiated");
        return 0;
    }
    QWidget* parent = VoreenApplicationQt::qtApp()->getMainWindow();

    if (dynamic_cast<PlotDataSelect*>(processor))
       return new PlotDataSelectWidget(parent, static_cast<PlotDataSelect*>(processor));
    else if (dynamic_cast<PlotDataGroup*>(processor))
       return new PlotDataGroupWidget(parent, static_cast<PlotDataGroup*>(processor));
    else if (dynamic_cast<PlotDataFitFunction*>(processor))
       return new PlotDataFitFunctionWidget(parent, static_cast<PlotDataFitFunction*>(processor));
    else if (dynamic_cast<PlotDataMerge*>(processor))
       return new PlotDataMergeWidget(parent, static_cast<PlotDataMerge*>(processor));
    else if (dynamic_cast<PlotProcessor*>(processor))
       return new PlotProcessorWidget(parent, static_cast<PlotProcessor*>(processor));

    return 0;
}
} // namespace voreen
