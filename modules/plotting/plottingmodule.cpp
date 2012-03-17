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

#include "plottingmodule.h"

#include "processors/plotdatasource.h"
#include "processors/plotfunctionsource.h"
#include "processors/lineplot.h"
#include "processors/hemisphereplot.h"
#include "processors/barplot.h"
#include "processors/scatterplot.h"
#include "processors/surfaceplot.h"
#include "processors/plotdataselect.h"
#include "processors/plotdatagroup.h"
#include "processors/plotdataexport.h"
#include "processors/plotdataexporttext.h"
#include "processors/plotdatafitfunction.h"
#include "processors/plotdatamerge.h"
#include "processors/plotfunctiondiscret.h"
#include "processors/imageanalyzer.h"

#include "utils/aggregationfunctionfactory.h"
#include "utils/plotpredicatefactory.h"

namespace voreen {

PlottingModule::PlottingModule()
    : VoreenModule()
{
    setName("Plotting");
    setXMLFileName("plotting/plottingmodule.xml");

    addProcessor(new PlotDataSource());
    addProcessor(new PlotFunctionSource());
    addProcessor(new BarPlot());
    addProcessor(new HemispherePlot());
    addProcessor(new ImageAnalyzer());
    addProcessor(new LinePlot());
    addProcessor(new PlotDataExport());
    addProcessor(new PlotDataExportText());
    addProcessor(new PlotDataFitFunction());
    addProcessor(new PlotDataGroup());
    addProcessor(new PlotDataMerge());
    addProcessor(new PlotDataSelect());
    addProcessor(new PlotFunctionDiscret());
    addProcessor(new ScatterPlot());
    addProcessor(new SurfacePlot());

    addSerializerFactory(new AggregationFunctionFactory());
    addSerializerFactory(PlotPredicateFactory::getInstance());
}

} // namespace
