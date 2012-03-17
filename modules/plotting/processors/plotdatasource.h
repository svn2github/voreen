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

#ifndef VRN_PLOTDATASOURCE_H
#define VRN_PLOTDATASOURCE_H

#include "../ports/plotport.h"

#include "voreen/core/processors/processor.h"
#include "voreen/core/properties/intproperty.h"
#include "voreen/core/properties/stringproperty.h"
#include "voreen/core/properties/filedialogproperty.h"
#include "voreen/core/properties/boolproperty.h"
#include "voreen/core/properties/buttonproperty.h"

namespace voreen {

class PlotData;

class PlotDataSource : public Processor {

public:
    PlotDataSource();
    ~PlotDataSource();
    virtual Processor* create() const;

    virtual std::string getCategory() const  { return "Data Source"; }
    virtual std::string getClassName() const { return "PlotDataSource"; }
    virtual CodeState getCodeState() const   { return CODE_STATE_TESTING; }
    //virtual bool usesExpensiveComputation() const { return true; }

protected:
    virtual void process();
    virtual void initialize() throw (tgt::Exception);
    virtual void deinitialize() throw (tgt::Exception);

private:
    void recalculate();
    PlotData* readCSVData();
    void csvline_populate(std::vector<std::string> &record, const std::string& line);
    std::string trimString(const std::string& oldString);

    PlotPort outPort_;

    FileDialogProperty inputFile_;   ///< filename of the file containing the value information

    StringProperty separator_;
    PlotData* pData_;

    IntProperty countLine_;
    IntProperty countKeyColumn_;

    BoolProperty constantOrder_;

    ButtonProperty recalculate_;

    static const std::string loggerCat_;
};

} //namespace
#endif // VRN_DataSource_H

