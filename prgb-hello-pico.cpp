/**
 * @file prgb-hello-pico.cpp
 * @author Holger Willenborg (holger@willenb.org)
 * @brief Demonstration of the prgb library. Just creates a moving, yellow square to a WS2821B matrix
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <TimeBasePico.hpp>
#include <W2812Array.hpp>
#include <Geometry_2xBTF_WS2812B_8x32_ECO.hpp>
#include <Coordinates.hpp>
#include <Color.hpp>


int main() {

    using namespace pico;
    using namespace prgb;

    // Raspberry Pi Pico is the timer source
    TimeBasePico timebase_pico= TimeBasePico();
 
    // The geometry is 2 BTX 32x8 matrices adding up to 32x16
    Geometry_2xBTF_WS2812B_8x32_ECO geometry = Geometry_2xBTF_WS2812B_8x32_ECO();
    
    // It's a W2812B matrix - Pico implementation, using out pin 16 to output the data for the WS2812B LED matrix
    W2812LightArray ar = W2812LightArray(16,100, geometry, timebase_pico, true);

    // start displaying the initially empty RGB(0,0,0) display. This will start to regularly show the content of the active buffer onthe LED matrix at 50 Hz
    ar.start_display(50); 
    
    TimeMS start_time = timebase_pico.get_deltatime_ms();

    // calculate y coordinate of the square
    Dimension y = geometry.get_y_count()/2-2;

    // do this forever 
    while (true) {

        static Dimension x = 0; // start left

        // Clear the display
        ar.fill_all(RGB(0,0,0));

        // draw rectangle in yellow
        ar.fill_rect(x,y,4,4,RGB(255,255,0), CMODE_Set);

        // Calculate next x position based on elapsed time calculating a value between 0 and the width of the geometry incrementing every 250ms
        x = ((timebase_pico.get_deltatime_ms() - start_time) / 250) % geometry.get_x_count();

        // the while loop would create as many buffers as possible, there's no need for this, we can easily spend some time doing nothing. Saves energy in the Pico, too.
        timebase_pico.wait_ms(20);

        // switch buffers, next framw will go into other buffer
        ar.commit_buffer(); 
	}
}