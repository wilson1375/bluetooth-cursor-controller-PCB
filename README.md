# Wireless ESP32 Navigation Mouse
## Why?

I recently encountered a need for a handheld, portable device with a specific amount of buttons that could wirelessly connect to a computer and simulate mouse clicks at predefined screen coordinates per button press.
This project uses a custom PCB that converts an ESP32 board into a Bluetooth Low Energy (BLE) "navigation mouse" using the [BLEMouse](https://github.com/T-vK/ESP32-BLE-Mouse) library available in the Arduino IDE.
Gerber files are included [here](bluetooth_5btn_APR11_23/Gerber_PCB_bluetooth_5btn.zip) if you want to modify/make your own. Additionally, you can see the bill of materials [here](bluetooth_5btn_APR11_23/BOM_PCB_bluetooth_5btn_2023-04-11.csv).

## Usage
* Set mouse sensitivty to 10.
* Turn off "Enhance Pointer Precision"/"Mouse Acceleration."
* Change the resolution `screenResolution` to match that of your monitor.
* Change the desired coordinates for each button.
* Flash.
* Connect via bluetooth to machine. Device is called "Navigation Mouse."

Testing/usage can be done as long as it is plugged in, but if you want it to be wireless, you will need a battery. Some batteries that would work [here](https://www.digikey.com/en/products/filter/batteries-rechargeable-secondary/91?s=N4IgjCBcoEwKwA4qgMZQGYEMA2BnApgDQgD2UA2iAMwBsMYDIxALAgAwDsNEAusQA4AXKCADKggE4BLAHYBzEAF9lQA). Green light comes on when fully charged.

## Limitations

Due to the 8-bit (signed) number limitation in the BLEMouse library commands, the cursor movement is restricted to a range of -127 to +127 pixels per command.
Additionally, the BLEMouse library only allows for relative cursor movement, meaning you can only move the mouse relative to its current position and cannot directly
specify absolute screen coordinates for the mouse to navigate to. To deal with this, instead we "jump" towards the target coordinates
by moving the cursor in the maximum allowed increments until the destination is reached. Additionally, due to the nature of how BLEMouse works, mouse sensitivity must be at 10 and mouse acceleration must be off.

## TODO

An alternative, better approach: have the ESP32 communicate with a custom application on the machine, then use that communication to invoke API calls to change coordinates. This would sidestep all current limitations.

![pcbpic](https://github.com/wilson1375/bluetooth-cursor-controller-PCB/assets/80933034/81c1e6fd-d39f-4ac8-b958-9d6fa3431fe7)

