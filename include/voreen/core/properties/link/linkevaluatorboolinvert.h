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

#ifndef VRN_LINKEVALUATORBOOLINVERT_H
#define VRN_LINKEVALUATORBOOLINVERT_H

#include "voreen/core/properties/link/linkevaluatorbase.h"
#include "voreen/core/voreencoredefine.h"

namespace voreen {

/**
 * Propagates an inverted boolean value.
 */
class VRN_CORE_API LinkEvaluatorBoolInvert : public LinkEvaluatorBase {
public:
    void eval(Property* src, Property* dst) throw (VoreenException);

    std::string getClassName() const { return "LinkEvaluatorBoolInvert"; }
    LinkEvaluatorBase* create() const { return new LinkEvaluatorBoolInvert(); }

    virtual bool arePropertiesLinkable(const Property* p1, const Property* p2) const;
};

} // namespace

#endif // VRN_LINKEVALUATORBOOLINVERT_H
