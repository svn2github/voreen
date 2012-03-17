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

#ifndef VRN_PLOTLIBRARYNONEFILEBASE_H
#define VRN_PLOTLIBRARYNONEFILEBASE_H

#include "plotlibrary.h"


namespace voreen {


/**
 *   This auxiliary library is a back end providing various rendering functions.
 *
 *   this ist the Generalized class for all classes who do not use output in files
 *   
 *   
 *   
 *   
 *
 **/
class PlotLibraryNoneFileBase : public PlotLibrary {
public:
    PlotLibraryNoneFileBase();

    virtual ~PlotLibraryNoneFileBase() {};

    /// this function is not used in nonfile settings
    virtual void beforeRender() {};

    /// this function is not used in nonfile settings
    virtual void afterRender() {};

    /// this function ist uesed to set the drawingcolor when the wire is to draw
    virtual void setWireColor(tgt::Color color);

private:

    static const std::string loggerCat_;
};


} // namespace voreen

#endif // VRN_PLOTLIBRARYNONEFILEBASE_H
