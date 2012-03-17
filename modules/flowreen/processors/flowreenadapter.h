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

#ifndef VRN_FLOWREENADAPTER_H
#define VRN_FLOWREENADAPTER_H

#include "voreen/core/processors/processor.h"
#include "voreen/core/ports/volumeport.h"
#include "flowreenprocessor.h"

#include <string>

namespace voreen {

class VolumeHandle;

class FlowreenAdapter : public Processor, private FlowreenProcessor {
public:
    FlowreenAdapter();
    virtual ~FlowreenAdapter();

    virtual Processor* create() const { return new FlowreenAdapter(); }
    virtual std::string getCategory() const { return "Flow Visualization"; }
    virtual std::string getClassName() const { return "FlowreenAdapter"; }
    virtual Processor::CodeState getCodeState() const { return CODE_STATE_STABLE; }
    virtual void process();
    virtual bool isUtility() const { return true; }

protected:
    void initialize() throw (tgt::Exception);

private:
    void calculateMagnitudes();

private:
    VolumeHandle* processedVolumeHandle_;   /** The volume containing the magnitudes. */

    VolumePort volInport_;
    VolumePort volOutport_;
};

}   //namespace

#endif
