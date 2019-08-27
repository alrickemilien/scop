#version 410

out vec4 fragColour;

in vec3 _position;
in vec4 _color;
in vec3 _normal;
in vec2 _uv;
in vec3 _light;
in vec4 _eye;

uniform float ambient_light;
uniform float specular_light;
uniform sampler2D texture_sample;
uniform int grey_scale;
uniform float smooth_texture_coefficient;

const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;

const float epsilon = 1e-6;

// hue, saturation and value are all in the range [0,1> here, as opposed to their
// normal ranges of: hue: [0,360>, sat: [0, 100] and value: [0, 256>
vec3 RGBtoHSV(vec3 color) {
    int sortindex[3] = int[3](RED,GREEN,BLUE);
    int tmpIndex;
    float rgbArr[3] = float[3](color.r, color.g, color.b);

    float hue, saturation, value, diff;
    float minCol, maxCol;
    int minIndex, maxIndex;

    if (color.g < color.r) {
      tmpIndex = sortindex[0];
      sortindex[0] = sortindex[1];
      sortindex[1] = tmpIndex;
    }

    if (color.b < color.g) {
      tmpIndex = sortindex[2];
      sortindex[2] = sortindex[1];
      sortindex[1] = tmpIndex;
    }

    if (color.r < color.b) {
      tmpIndex = sortindex[2];
      sortindex[2] = sortindex[0];
      sortindex[0] = tmpIndex;
    }

    minIndex = sortindex[0];
    maxIndex = sortindex[2];
    minCol = rgbArr[minIndex];
    maxCol = rgbArr[maxIndex];

    diff = maxCol - minCol;

    // Hue
    if( diff < epsilon){
        hue = 0.0;
    }
    else if(maxIndex == RED){
        hue = ((1.0/6.0) * ( (color.g - color.b) / diff )) + 1.0;
        hue = fract(hue);
    }
    else if(maxIndex == GREEN){
        hue = ((1.0/6.0) * ( (color.b - color.r) / diff )) + (1.0/3.0);
    }
    else if(maxIndex == BLUE){
        hue = ((1.0/6.0) * ( (color.r - color.g) / diff )) + (2.0/3.0);        
    }

    // Saturation
    if(maxCol < epsilon)
        saturation = 0;
    else
        saturation = (maxCol - minCol) / maxCol;

    /* Value */
    value = maxCol;

    return vec3(hue, saturation, value);
}

vec3 HSVtoRGB(vec3 color) {
    float f,p,q,t, hueRound;
    int hueIndex;
    float hue, saturation, value;
    vec3 result;

    // just for clarity
    hue = color.r;
    saturation = color.g;
    value = color.b;

    hueRound = floor(hue * 6.0);
    hueIndex = int(hueRound) % 6;
    f = (hue * 6.0) - hueRound;
    p = value * (1.0 - saturation);
    q = value * (1.0 - f*saturation);
    t = value * (1.0 - (1.0 - f)*saturation);

    switch(hueIndex) {
        case 0:
            result = vec3(value,t,p);
        break;
        case 1:
            result = vec3(q,value,p);
        break;
        case 2:
            result = vec3(p,value,t);
        break;
        case 3:
            result = vec3(p,q,value);
        break;
        case 4:
            result = vec3(t,p,value);
        break;
        default:
            result = vec3(value,p,q);
        break;
    }

    return result;
}

void main() {
  vec3  norm;
  vec3  lightDir;
  float diffuse;

  norm = normalize(_normal);

  lightDir = normalize(_light - _position);
  diffuse = max(dot(_normal, lightDir), 0.0);

  fragColour = (ambient_light + diffuse) * vec4((1 - smooth_texture_coefficient) * _color.xyz + smooth_texture_coefficient * texture(texture_sample, _uv).rgb, 255.0);
  fragColour.w = 255.0;

  if (grey_scale == 1) {
    vec3  hsvColor = RGBtoHSV(fragColour.rgb);

    // You can do further changes here, if you want.
    // Here set saturation to zero
    hsvColor.g = 0; 
    
    vec3  rgbColor = HSVtoRGB(hsvColor);
    fragColour = vec4(rgbColor.r, rgbColor.g, rgbColor.b, fragColour.a);
  }
}