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

#ifndef VRN_GRAYSCALE_CL_H
#define VRN_GRAYSCALE_CL_H

#include "voreen/core/processors/renderprocessor.h"
#include "modules/opencl/utils/clwrapper.h"

#include "voreen/core/ports/renderport.h"
#include "voreen/core/properties/floatproperty.h"

namespace voreen {

/**
 * Simple color to grayscale image processor using OpenCL.
 */
class GrayscaleCL : public RenderProcessor {
public:
    GrayscaleCL();
    virtual Processor* create() const;

    virtual std::string getCategory() const  { return "Image Processing"; }
    virtual std::string getClassName() const { return "GrayscaleCL"; }
    virtual CodeState getCodeState() const   { return CODE_STATE_EXPERIMENTAL; }

protected:
    virtual void process();
    virtual void initialize() throw (tgt::Exception);
    virtual void deinitialize() throw (tgt::Exception);

    FloatProperty saturation_;

    RenderPort inport_;
    RenderPort outport_;

    cl::Program* prog_;
};

} // namespace

#endif // VRN_GRAYSCALE_CL_H
