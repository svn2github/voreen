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

#include "modules/flowreen/flowreenmodule.h"

// processors
#include "processors/flowmagnitudes3d.h"
#include "processors/floworthogonalslicerenderer.h"
#include "processors/flowreenadapter.h"
#include "processors/flowslicerenderer2d.h"
#include "processors/flowslicerenderer3d.h"
#include "processors/flowstreamlinestexture3d.h"
#include "processors/pathlinerenderer3d.h"
#include "processors/streamlinerenderer3d.h"

// I/O
#include "modules/flowreen/io/flowreader.h"

// VolumeOperators
#include "modules/flowreen/datastructures/volumeoperatorintensitymask.h"

namespace voreen {

FlowreenModule::FlowreenModule()
    : VoreenModule()
{
    setName("Flowreen");
    setXMLFileName("flowreen/flowreenmodule.xml");

    // processors
    addProcessor(new FlowMagnitudes3D());
    addProcessor(new FlowOrthogonalSliceRenderer());
    addProcessor(new FlowSliceRenderer2D());
    addProcessor(new FlowSliceRenderer3D());
    addProcessor(new FlowStreamlinesTexture3D());
    addProcessor(new FlowreenAdapter());
    addProcessor(new PathlineRenderer3D());
    addProcessor(new StreamlineRenderer3D());

    // I/O
    addVolumeReader(new FlowReader());

    addShaderPath(getModulesPath("flowreen/glsl"));

    INST_SCALAR_TYPES(VolumeOperatorIntensityMask, VolumeOperatorIntensityMaskGeneric)
}

} // namespace
