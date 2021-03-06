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

#include "voreen/core/properties/link/linkevaluatoridnormalized.h"
#include "voreen/core/utils/variant.h"

#include "voreen/core/properties/property.h"

namespace voreen {

void LinkEvaluatorIdNormalized::eval(Property* src, Property* dst) throw (VoreenException) {
    const Variant& srcVar = src->getVariant(true);
    dst->setVariant(srcVar, true);
}

std::string LinkEvaluatorIdNormalized::getClassName() const {
    return "LinkEvaluatorIdNormalized";
}

bool LinkEvaluatorIdNormalized::arePropertiesLinkable(const Property* src, const Property* dst) const {
    tgtAssert(src, "null pointer");
    tgtAssert(dst, "null pointer");

    return Variant::canConvert(src->getVariantType(), dst->getVariantType());
}

LinkEvaluatorBase* LinkEvaluatorIdNormalized::create() const {
    return new LinkEvaluatorIdNormalized;
}

} // namespace
