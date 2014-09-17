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

#ifndef VRN_NUMERICPROPERTY_H
#define VRN_NUMERICPROPERTY_H

#include "voreen/core/properties/condition.h"
#include "voreen/core/properties/templateproperty.h"

namespace voreen {

/**
 * Template for properties that store numeric values.
 *
 * Besides the allowed value range, some GUI hints can be defined,
 * such as the stepping and number of decimals.
 */
template<typename T>
class NumericProperty : public TemplateProperty<T> {

template<typename> friend class NumericPropertyValidation;

public:
    typedef T ElemType;

    NumericProperty(const std::string& id, const std::string& guiText, const T& value,
                    const T& minValue, const T& maxValue, const T& stepping,
                    Processor::InvalidationLevel invalidationLevel=Processor::INVALID_RESULT);

    /**
     * Sets the minimum value the variable can take.
     * This is checked by a NumericPropertyValidation on each
     * set() call. Therefore, it is guaranteed that the property
     * never attains a value outside its valid range.
     */
    void setMinValue(const T& minValue);
    const T& getMinValue() const;

    /**
     * Sets the maximum value the variable can take.
     * This is checked by a NumericPropertyValidation on each
     * set() call. Therefore, it is guaranteed that the property
     * never attains a value outside its valid range.
     */
    void setMaxValue(const T& maxValue);
    const T& getMaxValue() const;

    /**
     * Sets the property's minimum increase/decrease,
     * which should be used in GUI widgets representing
     * the property, e.g., a spin box.
     *
     * @see increase, decrease
     */
    void setStepping(const T stepping);
    T getStepping() const;

    /**
     * Sets the number of decimals that should be
     * displayed by a GUI representation of the property.
     */
    void setNumDecimals(int numDecimals);
    int getNumDecimals() const;

    /**
     * If tracking is disabled, the property is not to be updated
     * during user interactions, e.g., while the user drags a slider.
     * Tracking is enabled by default.
     */
    void setTracking(bool tracking);
    bool hasTracking() const;

    /**
     * Increases the property's value by its stepping.
     * @see setStepping
     */
    void increase();

    /**
     * Decreases the property's value by its stepping.
     * @see setStepping
     */
    void decrease();

    /// @see Property::serialize
    virtual void serialize(XmlSerializer& s) const;

    /// @see Property::deserialize
    virtual void deserialize(XmlDeserializer& s);

protected:
    using TemplateProperty<T>::value_;

    T minValue_;
    T maxValue_;
    T stepping_;
    bool tracking_;
    int numDecimals_;
};

template<typename T>
NumericProperty<T>::NumericProperty(const std::string& id, const std::string& guiText, const T& value,
                                    const T& minValue, const T& maxValue, const T& stepping,
                                    Processor::InvalidationLevel invalidationLevel)
                                    : TemplateProperty<T>(id, guiText, value, invalidationLevel),
                                    minValue_(minValue),
                                    maxValue_(maxValue),
                                    stepping_(stepping),
                                    tracking_(true),
                                    numDecimals_(2)
{
    this->addValidation(NumericPropertyValidation<T>(this));
    std::string errorMsg;
    this->validate(value, errorMsg);
    if (!errorMsg.empty())
        LWARNINGC("voreen.TemplateProperty", errorMsg);
}

template<typename T>
void NumericProperty<T>::setMaxValue( const T& maxValue ) {
    maxValue_ = maxValue;
    this->updateWidgets();
}

template<typename T>
const T& NumericProperty<T>::getMaxValue() const {
    return maxValue_;
}

template<typename T>
void NumericProperty<T>::setMinValue(const T& minValue) {
    minValue_ = minValue;
    this->updateWidgets();
}

template<typename T>
const T& NumericProperty<T>::getMinValue() const {
    return minValue_;
}

template<typename T>
void NumericProperty<T>::setStepping(const T stepping) {
    stepping_ = stepping;
    this->updateWidgets();
}

template<typename T>
T NumericProperty<T>::getStepping() const {
    return stepping_;
}

template<typename T>
int NumericProperty<T>::getNumDecimals() const {
    return numDecimals_;
}

template<typename T>
void NumericProperty<T>::setNumDecimals(int numDecimals) {
    tgtAssert(numDecimals <= 64 && numDecimals >= 0, "Invalid number of decimals");
    numDecimals_ = numDecimals;
    this->updateWidgets();
}

template<typename T>
bool NumericProperty<T>::hasTracking() const {
    return tracking_;
}

template<typename T>
void NumericProperty<T>::setTracking(bool tracking) {
    tracking_ = tracking;
    this->updateWidgets();
}

template<typename T>
void NumericProperty<T>::increase() {
    this->set(value_ + stepping_);
}

template<typename T>
void NumericProperty<T>::decrease() {
    this->set(value_ - stepping_);
}

template<typename T>
void NumericProperty<T>::serialize(XmlSerializer& s) const {
    Property::serialize(s);

    s.serialize("value", value_);

    // serialize tracking mode, if it differs from default value
    if (!tracking_)
        s.serialize("tracking", tracking_);
}

template<typename T>
void NumericProperty<T>::deserialize(XmlDeserializer& s) {
    Property::deserialize(s);

    // deserialize value
    T value;
    s.deserialize("value", value);
    try {
        this->set(value);
    }
    catch (Condition::ValidationFailed& e) {
        s.addError(e);
    }

    // deserialize tracking mode, if available
    try {
        s.deserialize("tracking", tracking_);
    }
    catch (XmlSerializationNoSuchDataException&) {
        s.removeLastError();
    }
}

} // namespace voreen

#endif // VRN_NUMERICPROPERTY_H
