# SD 5529 Embedded interaction workshop
![](./Assets%20and%20resources/cover.jpg)
## Component list
- 1 x Arduino Mega 2560 R3
- 5 x 1x8 5V Relay board
- 40 x single bubble unit
- 2 x conductive sheet for capacitive sensing
- 5 x 12V power supply
- 1 x 5V power supply
- 200 feets+ wire
### Single bubble unit component list
- 3D printed housing
![](./Assets%20and%20resources/3dmerged.png)
  - Base unit [(STL file here)](/Assets%20and%20resources/3dprint/base_wleg_0512f.stl)
  - Ring housing unit [(STL file here)](/Assets%20and%20resources/3dprint/ring_housing_merged_0511f.stl)
  - Cloth-fitting unit [(STL file here)](/Assets%20and%20resources/3dprint/ring_lock_fit_0511.stl)
- 12V, 0.45A  computer fan
- 16 x WS2812 RGBW LED in ring PCB
- Sealed cloth bubble [(Paper cut file here)](/Assets%20and%20resources/IMG_3083.png)
![](./Assets%20and%20resources/Image-2.jpeg)

## Wiring and circuit design
- All unit's fans Vcc are connected to relay's NO (Normal open)
- All relay signal pins are connected to Mega's digital pins (40 pins)
- All LED wires are merged in a row basis -> only 5 pins are required for controlling

Simplifed sketch for wiring and circuit design
![](./Assets%20and%20resources/wiring.png)

## Trimmed logic flow
![](./Assets%20and%20resources/logicflow.jpg)

## Future improvement
- More animation patterns
- Real unit design, to control each unit with indivial MCU
- To test for 5V fan performance which can simplifed the circuit design

## Special thanks
We are very thankful for the supports and leatures from Mr. Ken Yiu and Tim.
![](./Assets%20and%20resources/group.JPG)