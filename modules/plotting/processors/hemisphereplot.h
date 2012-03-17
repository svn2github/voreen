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

#ifndef VRN_HEMISPHEREPLOT_H
#define VRN_HEMISPHEREPLOT_H

#include "surfaceplot.h"

#include "voreen/core/properties/floatproperty.h"
#include "voreen/core/properties/intproperty.h"

#include "../ext/triangle/include/del_interface.hpp"

#include <vector>
#include <list>

namespace voreen {

/**
 * This processor is able to create 3D surface plots.
 */
class HemispherePlot : public SurfacePlot {
public:
    HemispherePlot();

    virtual Processor* create() const;
    virtual std::string getClassName() const { return "HemispherePlot"; }
    virtual CodeState getCodeState() const { return Processor::CODE_STATE_TESTING; }

protected:
    virtual void initialize() throw (tgt::Exception);
    virtual void deinitialize() throw (tgt::Exception);

    virtual void readFromInport();
    virtual void generateDelaunay();
    virtual void calcDomains();
    virtual void setPlotStatus();
    
    //virtual void selectDataFromFunction();
    static const std::string loggerCat_;
};

}   //namespace

#endif // VRN_HEMISPHEREPLOT_H
