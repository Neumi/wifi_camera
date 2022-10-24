# wifi_camera

### A camera that can see WiFi signals. Just the sensor unit. Currently planned for 8x8=64 pixels.

<img alt="result of a scanned 3D frame" src="/images/animation.gif">
3D capture of a wifi signal in a 20x20x20 cm grid.


## What it does
The sensor array captures RSSI values from near by WiFi networks and sends the collected pixel data to a master that processes and visualizes the captured data. The goal is to build a sensor, that makes WiFi signal visible in more or less real time.

## Why? 
WiFi signals are invisible to humans. I think it would be fun to make them visible and play around with it. Projects I have in mind unsing the sensor array: real time analysis of antennas and obstacles..., real time object/person detection/tracking by reading WiFi shadows and reflections, using the standing wave to 'surf' it to get position data back for i.e. robots.

<img alt="4x4 pixel array" src="/images/pixel_array.jpeg" width=49%>


## How?
Before this, I built a rig to scan and visualize WiFi signal propagation in 3D 

https://hackaday.com/2021/11/22/visualizing-wifi-with-a-converted-3d-printer/

https://github.com/Neumi/3D_wifi_scanner

This got me interested in building a real time, sensor array to take a whole frame at once without having to scan a slice one position after another.


To capture a whole slice at once, I built this array unsing four PCBs with 4x4 ESP8266 sensor nodes connected via i2c where every pixel is an i2c slave and a master that asks the pixels one by one for the captured values.
 
<img alt="four 4x4 pixel arrays" src="/images/pixel_array_large.jpeg" width=49%>

I'm currently waiting fore more ESP8266s to arrive.



## Results
The results look pretty granular currently, as I only used 4x4 pixels, which is a bit low. When more ESPs arrive, I will take more images.
<img alt="16 pixels" src="/images/pixelarray_capture2d.png">
16 Pixels, x-axis is time, Y axis is RSSI with an offset between each pixel for visibility.
<img alt="four 4x4 pixel arrays" src="/images/pixelarray_capture.png">
16 Pixels with correct orientation in a 2D plot. 




