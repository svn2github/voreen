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

#include "plotdataexport.h"

#include "../utils/plotdata.h"
#include "../utils/plotcell.h"
#include "../utils/plotrow.h"
#include "../utils/plotfunction.h"

#include "voreen/core/voreenapplication.h"

#include "tgt/tgt_math.h"
#include <iostream>
#include <fstream>

namespace voreen {

const std::string PlotDataExport::loggerCat_("voreen.PlotDataExport");

PlotDataExport::PlotDataExport():
    PlotDataExportBase()
    , outputFile_("outputFile", "Save File", "Write CSV Output file", VoreenApplication::app()->getDataPath(),
        "Comma-Separated Files (*.csv);;Textfile (*.txt);;XML-File (*.xml);;HTML-File (*.htm *.html);;All TextFiles (*.csv *.xml *.txt *.htm *.html)",
        FileDialogProperty::SAVE_FILE,Processor::VALID)
    , rewrite_("rewrite","rewrite Export File",Processor::VALID)
{
    outputFile_.onChange(CallMemberAction<PlotDataExport>(this, &PlotDataExport::exportFile));
    rewrite_.onChange(CallMemberAction<PlotDataExport>(this, &PlotDataExport::exportFile));
    addProperty(&outputFile_);
    addProperty(&rewrite_);

    setPropertyGroupGuiName("FileSelection", "File-Selection");

    outputFile_.setGroupID("FileSelection");
    rewrite_.setGroupID("FileSelection");
}

Processor* PlotDataExport::create() const {
    return new PlotDataExport();
}

void PlotDataExport::exportFile() {
    PlotDataExportBase::exportFile(outputFile_.get());
}


}
