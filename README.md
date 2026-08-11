# Mini-Arcade-Machine
With this project, I hope to mix my love for engineering and video game development by creating a video game for a custom machine.
Documentation will eventually feature a wiring diagram, final OnShape CAD model, a code flowchart, and updates.

<img width="595" height="772" alt="image" src="https://github.com/user-attachments/assets/180d8530-0a75-49bb-89e5-ec37b06f4cd9" />


### Materials
|Type |Quantity |
|--- | --- |
| Microcontroller [Arduino Uno] | x1 |
| Wires | x? |
| Pushbutton | x2 |
| Joystick | x1 |
| LCD Screen [2.8" TFT ILI 9341] | x1 |
| ? Nuts | x? |
| ? Screws | x? |

### Code Dependencies
The [Main] library is "Adafruit ILI9341:1.6.3" which has its own dependencies.
The library can be found by typing "ILI9341" in the Library Manager in the Arduino IDE App. 

When installing, there should be a pop-up asking to download the dependencies.
These are:
- Adafruit BusIO
- Adafruit GFX Library
- Adafruit SH110X
- Adafruit STMPE610
- Adafruit TSC2007
- Adafruit TouchScreen

### Updates

8/5/2026:
- Started Project
- V1 of CAD Model: https://cad.onshape.com/documents/1f67ee2ecc3e3aa01e412fcf/w/54ba2dbc630de261fbd7408a/e/83f6dcfcd872f677a0073c63?renderMode=0&uiState=6a73e49e044e03fd4e4e218f
- Note: When using Box Joint add-on, make sure walls intersect geometry with each other.
- Progress screenshot:
   - <img width="892" height="735" alt="image" src="https://github.com/user-attachments/assets/88094ea1-6ea7-4b17-8c51-4fe3e1b8c56e" />

8/6/2026:
- Video showcasing same LCD Screen: https://www.youtube.com/watch?v=0-aUxdmCEgg
   - Datasheet Doc on LCD: https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf
   - <img width="516" height="452" alt="image" src="https://github.com/user-attachments/assets/5cf0746e-76ce-41c1-95c5-6dc3673c946d" />

- Update on CAD:
   - Used T-Slot Joint add-on in OnShape for screw inserts.
   - Made Drawings for each part with a total of 3 sheets with 1 being a test sheet. Everything can fit on two wooden sheets:
       - <img width="898" height="718" alt="image" src="https://github.com/user-attachments/assets/63a1ef20-1365-49e2-a37a-62f0f2bc7138" />
   - Physically laser cut Bottom and Front pieces to test fit on a small scale. Screws & nuts are limited in quantity with varying sizes. Assembly will be frustrating.
     - Take away: Use smaller screws to make a smaller hole so a full circle can fit on the thin material.
- Start of Wiring:
   - <img width="1480" height="759" alt="image" src="https://github.com/user-attachments/assets/853d3d26-c098-4ff8-ae2c-0ad57f597f7c" />
- Updated: [Same-day, only LCD Screen wiring diagram]
   - <img width="1296" height="732" alt="image" src="https://github.com/user-attachments/assets/7a94b132-7932-4708-9d95-ba036317fb0d" />

8/10/2026:
- Tried running old library on Arduino Uno and it didn't work. Looked online, AI says the library doesn't match my LCD despite the video.
- I tried a new library "mcufriend_kbv," as AI suggested. Running it tells me the Arduino Uno doesn't have enough memory. Thus, I've switched the an Arduino Mega board [Mega 2560 Rev3].
- Running the library on the Arduino Mega, I get the following errors:
```
Error: timeout
Error: timeout communicating with programmer
Error: failed to execute command 0x13
Error: write command failed
 ```
- Important links:
   - Arduino docs of board: https://docs.arduino.cc/hardware/mega-2560/

 8/11/2026:
 - Trying this now: [https://www.instructables.com/Arduino-Mega-Touchscreen-Quiz-Using-Elegoo-28-TFT-/](https://www.instructables.com/Arduino-Mega-Touchscreen-Quiz-Using-Elegoo-28-TFT-/)
 - Edit: IT WORKS! Just need to follow instructions by guide above. Download each library, put the LCD on the arduino [soldering holes side facing away from cord port], copy the code, make sure the board is connected via the IDE, verify the code with the IDE button, if no errors, run the code.
