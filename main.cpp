#include "mbed.h"

// HC-SR04
DigitalOut trig(p5);
DigitalIn echo(p6);
Timer timer;

// LED
DigitalOut led(LED1);
Ticker ticker;

void toggleLed() {
    led = !led;   
}

void updateDistance(int distance) {
    if (distance > 100) {
        ticker.detach();
        led = 1;
    }
    else if (distance > 50) {
        ticker.detach();
        ticker.attach(&toggleLed, 0.2);
    }
    else {
        ticker.detach();
        ticker.attach(&toggleLed, 0.05);   
    }
    
}

int main()
{  
    while(1) {
        // Send trig pulse
        trig = 1;
        wait_us(10.0);
        trig = 0;
        timer.reset();
        
        // Wait for echo high
        while (echo == 0) {};
        timer.start();
        
        // Wait for echo low
        while (echo == 1) {}
        timer.stop();
        
        updateDistance(timer.read_us() / 58.0);
        
        wait(0.1);
    }
}