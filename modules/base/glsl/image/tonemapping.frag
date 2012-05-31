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

#include "modules/mod_sampler2d.frag"

uniform SAMPLER2D_TYPE colorTex_;
uniform SAMPLER2D_TYPE depthTex_;
uniform TEXTURE_PARAMETERS textureParameters_;

#if defined(GLSL_VERSION_130)
    #define TEXTURE_LOD(myTexture, texCoords, lodLevel) textureLod(myTexture, texCoords, lodLevel)
#else
    #define TEXTURE_LOD(myTexture, texCoords, lodLevel) texture2DLod(myTexture, texCoords, lodLevel)
#endif

#if defined(USE_S_CURVE)
uniform float sigma_;
uniform float power_;
#elif defined(USE_RAHMAN_RETINEX)
uniform float frequency_;
uniform float subtractionFactor_;
uniform float iterations_;
uniform float maxLevel_;
uniform float wTotal_;
#endif

void main() {
    vec2 pos = gl_FragCoord.xy * screenDimRCP_;
    vec4 fragColor = vec4(0.0);
    float fragDepth = 0.0;

    // fetch input textures
    vec4 color = textureLookup2Dnormalized(colorTex_, textureParameters_, pos);
    float depth = textureLookup2Dnormalized(depthTex_, textureParameters_, pos).z;

    #if defined(USE_S_CURVE)
        //Perform the S-curve tone mapping based on the parameters sigma and n
        vec4 pow_value = pow(color, vec4(power_));
        fragColor = pow_value/(pow_value+pow(sigma_, power_));
    #elif defined(USE_RAHMAN_RETINEX)
        float W_n;
        vec4 value = vec4(0.0);
        float sum = 0.0;
        float n = 0.0;
        
        //Calculate which rate the mipmap level should increase
        float per_level = maxLevel_/iterations_;

        //Transform texture parameters
        vec2 texCoordsTransformed = (textureParameters_.matrix_ * vec4(pos, 0.0, 1.0)).xy;
               
        while(n<iterations_){  
           //Calculate the current weight       
           W_n = pow(iterations_ - n + 1.0, frequency_) / wTotal_;
           
           //Subtract a mipmapped image from the orginal one bu a factor of k, and in the logarithmic domain
           //Also make sure that value are above zero to avoid dividing by zero.
           value += W_n * (log(color) - (subtractionFactor_ * log(max(TEXTURE_LOD(colorTex_, texCoordsTransformed, n*per_level), 0.0001))));
           n++;              
        }
        //Retrieve the finsihed image from the log domain.
        fragColor = exp(value);
    #endif
    fragDepth = depth;

    FragData0 = fragColor;
    gl_FragDepth = fragDepth;
}
