/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2008 Visualization and Computer Graphics Group, *
 * Department of Computer Science, University of Muenster, Germany.   *
 * <http://viscg.uni-muenster.de>                                     *
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

#include "voreen/core/io/volumereader.h"

#include <fstream>

#include "voreen/core/io/ioprogress.h"
#include "voreen/core/volume/volume.h"


namespace voreen {

const std::string VolumeReader::loggerCat_("voreen.io.VolumeReader");

VolumeReader::VolumeReader(IOProgress* progress /*= 0*/)
  : progress_(progress)
{}

const std::vector<std::string>& VolumeReader::getExtensions() const {
    return extensions_;
}

void VolumeReader::read(Volume* volume, std::fstream& fin) {
    if (progress_) {
        int max = tgt::max( volume->getDimensions() );
        progress_->setNumSteps(max);
        size_t sizeStep = volume->getNumBytes() / max; // here does not occur a rest, because max is a dim

        for (size_t i = 0; i < size_t(max); ++i) {
            fin.read( reinterpret_cast<char*>(volume->getData()) + sizeStep * i, sizeStep );
            progress_->set(i);
        }
    }
    else
        fin.read( reinterpret_cast<char*>(volume->getData()), volume->getNumBytes() );
}

} // namespace voreen
