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

#ifndef VRN_PLOTFUNCTIONDISCRET_H
#define VRN_PLOTFUNCTIONDISCRET_H

#include "../ports/plotport.h"

#include "voreen/core/processors/processor.h"
#include "voreen/core/properties/floatproperty.h"
#include "voreen/core/properties/buttonproperty.h"
#include "voreen/core/properties/optionproperty.h"

namespace voreen {

class PlotData;
class PlotFunction;

class PlotFunctionDiscret : public Processor {
public:
    PlotFunctionDiscret();

    virtual Processor* create() const;
    virtual std::string getCategory() const  { return "Plotting"; }
    virtual std::string getClassName() const { return "PlotFunctionDiscret"; }
    virtual CodeState getCodeState() const   { return CODE_STATE_TESTING; }
    //virtual bool usesExpensiveComputation() const { return true; }
    virtual bool isEndProcessor() const;
    virtual bool isReady() const;

    /// @see Serializer::serialize
    virtual void serialize(XmlSerializer& s) const;

    /// @see Deserializer::deserialize
    virtual void deserialize(XmlDeserializer& s);

    /// Provides the link to the object for the widget.
    const PlotData* getPlotData() const;


    /// default destructor
    virtual ~PlotFunctionDiscret();
protected:
    virtual void process();
    virtual void initialize() throw (tgt::Exception);
    virtual void deinitialize() throw (tgt::Exception);

private:

    struct DiscretizeValues  : public Serializable {
        std::vector<std::pair<plot_t, plot_t> > interval;
        std::vector<plot_t> stepwidth;
        std::pair<int,int> columns;

        /// @see Serializer::serialize
        virtual void serialize(XmlSerializer& s) const;

        /// @see Deserializer::deserialize
        virtual void deserialize(XmlDeserializer& s);

    };

    void setOutPortData();
    void readData();
    void calculate();
    void deleteList();
    void choiceChange();
    void intervalStepChange();
    void leftIntervalChange();
    void rightIntervalChange();
    void calculateResultLength();

    PlotPort outPort_;
    PlotPort inPort_;

    /// Properties
    IntOptionProperty dimensionsList_;

    FloatProperty leftInterval_;
    FloatProperty rightInterval_;
    FloatProperty steps_;

    ButtonProperty startDiscretization_;

    FloatProperty numberofCalculations_;

    DiscretizeValues resetList_;

    const PlotFunction* pData_;
    PlotData* pDataOut_;

    static const std::string loggerCat_;

};

} // namespace voreen

#endif // VRN_PLOTFUNCTIONDISCRET_H
