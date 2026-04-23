#include "getColor.h"
#include "raymath.h"

Color getRandColor(float distance, float maxDistance) {
    // Clamp distance to a max value of 200 or maxDistance
    distance = Clamp(distance, 0, maxDistance);

    // Calculate the interpolation factor (0.0 to 1.0)
    if(distance < 0)
        distance *= -1; 
    float factor = distance / maxDistance;

    // Linearly interpolate the red and blue channels
    unsigned char red = (unsigned char)((1.0f - factor) * 255);   // Red increases as distance decreases
    unsigned char blue = (unsigned char)(factor * 255);           // Blue decreases as distance decreases

    // Return the color with full alpha (255) and no green (0)
    return (Color){red, 0, blue, 255};
}