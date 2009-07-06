/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2009 Visualization and Computer Graphics Group, *
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

#ifndef VRN_BOOLPROPERTY_H
#define VRN_BOOLPROPERTY_H

#include "voreen/core/vis/properties/templateproperty.h"

namespace voreen {

class BoolProp : public TemplateProperty<bool> {
public:
    BoolProp(const std::string& id, const std::string& guiText, bool value = false,
        bool invalidate = true, bool invalidateShader = false);
    virtual ~BoolProp() {}

    void updateFromXml(TiXmlElement* propElem);
    TiXmlElement* serializeToXml() const;

    PropertyWidget* createWidget(PropertyWidgetFactory* f);
    virtual std::string toString() const { 
        return ((value_ == true) ? "true" : "false");
    }
};

}   // namespace

#endif