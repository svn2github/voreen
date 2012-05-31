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

#include "tonemapping.h"

#include "tgt/textureunit.h"

using tgt::TextureUnit;

namespace voreen {

ToneMapping::ToneMapping()
    : ImageProcessor("image/toneMapping")
      , toneMappingMethod_("toneMappingMethod", "Tone Mapping Method", Processor::INVALID_PROGRAM)
      , scurveSigma_("scurveSigma", "Sigma", 0.3f, 0.01f, 20.0f)
      , scurvePower_("scurvePower", "Power", 4.6f, 0.01f, 20.0f)  
      , rahmanFrequency_("rahmanFrequency", "Frequency", -7.5f, -10.0f, 10.0f)  
      , rahmanSubtractionFactor_("rahmanSubtractionFactor", "Subtraction Factor", 1.0f, -1.0f, 1.0f)
      , rahmanIterations_("rahmanIterations", "Iterations", 4.0f, 0.0f, 10.0f)  
      , rahmanMaxLevel_("rahmanMaxLevel", "Max Level", 13.0f, 0.0f, 20.0f)  
      , inport_(Port::INPORT, "image.inport", false, Processor::INVALID_RESULT, GL_RGBA32F_ARB)
      , outport_(Port::OUTPORT, "image.outport", false, Processor::INVALID_RESULT, GL_RGBA32F_ARB)
{
    toneMappingMethod_.addOption("s-curve",                "S-Curve (Global)",                   "USE_S_CURVE");
    toneMappingMethod_.addOption("rahman-retinex",         "Rahman Retinex (Local)",            "USE_RAHMAN_RETINEX");
    toneMappingMethod_.set("s-curve");
    toneMappingMethod_.onChange(CallMemberAction<ToneMapping>(this, &ToneMapping::toneMappingMethodChanged));
    addProperty(toneMappingMethod_);

    addProperty(scurveSigma_);
    addProperty(scurvePower_);
    addProperty(rahmanFrequency_);
    rahmanFrequency_.onChange(CallMemberAction<ToneMapping>(this, &ToneMapping::rahmanUpdate));
    addProperty(rahmanSubtractionFactor_);
    addProperty(rahmanIterations_);
    rahmanIterations_.onChange(CallMemberAction<ToneMapping>(this, &ToneMapping::rahmanUpdate));
    addProperty(rahmanMaxLevel_);
    rahmanMaxLevel_.onChange(CallMemberAction<ToneMapping>(this, &ToneMapping::rahmanUpdate));

    addPort(inport_);
    addPort(outport_);
}

void ToneMapping::initialize() throw (tgt::Exception){
    ImageProcessor::initialize();
    toneMappingMethodChanged();
    wTotal_ = 0.0f;
}

void ToneMapping::process() {

    if (getInvalidationLevel() >= Processor::INVALID_PROGRAM)
        compile();

    outport_.activateTarget();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    TextureUnit colorUnit, depthUnit;
    inport_.bindColorTexture(colorUnit.getEnum());
    if (toneMappingMethod_.get() == "rahman-retinex") {
        glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmapEXT(GL_TEXTURE_2D);
    }
    inport_.bindDepthTexture(depthUnit.getEnum());

    // initialize shader
    program_->activate();
    setGlobalShaderParameters(program_);

    // set uniforms
    program_->setUniform("colorTex_", colorUnit.getUnitNumber());
    program_->setUniform("depthTex_", depthUnit.getUnitNumber());
    inport_.setTextureParameters(program_, "textureParameters_");

    // set method specific uniforms
    if (toneMappingMethod_.get() == "s-curve") {
        program_->setUniform("sigma_", scurveSigma_.get());
        program_->setUniform("power_", scurvePower_.get());
    }
    if (toneMappingMethod_.get() == "rahman-retinex") {
        if(rahmanTotalUpdate_ || inport_.hasChanged()){
            wTotal_ = 0.0f;
            float i = 0.0f;
            while(i<rahmanIterations_.get()){
                wTotal_ += pow(rahmanIterations_.get() - i + 1, rahmanFrequency_.get());
                i++;
            }
            rahmanTotalUpdate_ = false;
        }

        //colorUnit.activate();
        //glGenerateMipmapEXT(GL_TEXTURE_2D);

        program_->setUniform("frequency_", rahmanFrequency_.get());
        program_->setUniform("subtractionFactor_", rahmanSubtractionFactor_.get());
        program_->setUniform("iterations_", rahmanIterations_.get());
        program_->setUniform("maxLevel_", rahmanMaxLevel_.get());
        program_->setUniform("wTotal_", wTotal_);
    }

    renderQuad();

    program_->deactivate();
    outport_.deactivateTarget();
    TextureUnit::setZeroUnit();
    LGL_ERROR;
}

std::string ToneMapping::generateHeader(const tgt::GpuCapabilities::GlVersion* version) {
    std::string header = ImageProcessor::generateHeader(version);
    header += "#define " + toneMappingMethod_.getValue() + "\n";
    return header;
}

void ToneMapping::compile() {
    if (program_)
        program_->setHeaders(generateHeader());
    ImageProcessor::compile();
}

void ToneMapping::toneMappingMethodChanged() {
    scurveSigma_.setVisible(toneMappingMethod_.get() == "s-curve");
    scurvePower_.setVisible(toneMappingMethod_.get() == "s-curve");
    rahmanFrequency_.setVisible(toneMappingMethod_.get() == "rahman-retinex");
    rahmanSubtractionFactor_.setVisible(toneMappingMethod_.get() == "rahman-retinex");
    rahmanIterations_.setVisible(toneMappingMethod_.get() == "rahman-retinex");
    rahmanMaxLevel_.setVisible(toneMappingMethod_.get() == "rahman-retinex");
}

void ToneMapping::rahmanUpdate() {
    rahmanTotalUpdate_ = true;
}

} // voreen namespace
