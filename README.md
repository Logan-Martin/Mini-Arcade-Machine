# Mini-Arcade-Machine
With this project, I hope to mix my love for engineering and video game development by creating a video game for a custom machine.
Documentation will eventually feature a wiring diagram, final OnShape CAD model, a code flowchart, and updates.

<img width="337" height="435" alt="IMG_20260818_180818005" src="https://github.com/user-attachments/assets/972a2a61-902c-427a-b77e-c60f91dd03b9" />

Link to CAD Model: [click to open](https://cad.onshape.com/documents/1f67ee2ecc3e3aa01e412fcf/w/54ba2dbc630de261fbd7408a/e/2a63c9408a712fd025e38aa2)
- NOTE: OnShape may come up with a 404 Forbidden Page. If this happens, please copy and paste the link into your browser. 

---

### Materials
|Type |Quantity |
|--- | --- |
| Microcontroller [Arduino Mega R3] | x1 |
| Wires | x? |
| Arcade Pushbuttons | x2 |
| Joystick | x1 |
| LCD Screen [2.8" TFT ILI 9341] | x1 |
| M3 Nuts | x22 [x8 for holding Joystick] + x4 more if using Arduino standoffs |
| M3 x 20mm length Screws | x14 |
| M3 x 25mm length Screws | x4 [for holding Joystick] |

Note: The arcade pushbuttons I used required soldering. 
That requires soldering iron, solder itself, wire to strip [wire stripper needed], copper shavings, sponge. 
Soldering fume extractor not required, but can be good to have as well as a stand with clips to hold what you're soldering and/or mat to solder on.

---
### Important Links
- LCD Screen info: [https://wiki.elegoo.com/oshw-parts-&-accessories/screen-intruduction](https://wiki.elegoo.com/oshw-parts-&-accessories/screen-intruduction) 

---

### Wiring
<img width="866" height="632" alt="image" src="https://github.com/user-attachments/assets/effb5e52-b80e-49b7-9c5e-502307221fda" />

---

### Updates

#### Latest Update:

8/18/2026:
- Attempting to fix the screen today. After double checking wires with the code and with a multimeter [icon that looks like sound waves/audio], they all seem to work fine. I did, however, miss adding Digital Pin 13 by accident. The screen is still just white though, no image is displaying, with some flickering. That tells me there's something with the Power, maybe one of the Reset pins. Unsure, but it doesn't seem to be.
- I've realized my mistake, or hopefully the last one. I used a breadboard to connect LCD pins and wires from the Arduino, but I didn't put a connection between both sides of the breadboard. That meant that no charge would go from one side of the board to the other. I can connect it or bridge it. 
- After looking for ways to connect two sides of a breadboard, I found a bunch of male-to-female wires that are pre-stuck together. I've decided to rewire the LCD with these as it's a direct connection and much cleaner.
- Update [6:10]: It WORKS! The rewiring was annoying, but made it all nicer to work with. The wires fit mostly in the box. I had to sand some more friction fit holes, and had some more annoyances with screwing in each wall, but the final result didn't take too long. I made sure to test each button and the screen each wall I added just to be sure. Now to learn graphics or overall drawing on the screen to make something run on the machine.

<details>
<summary>Previous Updates [Click to Open Dropdown]</summary>
8/17/2026:
- Did some physical assembly, thankfully finding many terminal stacking headers to make the job of connecting pins easier.
- Encountered an issue with ButtonB not working and the screen. ButtonA and the Joystick worked perfect. Turns out I can't use Digital Pins 20 and 21 for buttons on the Arduino Mega for the buttons as they are for I2C [SDA, SDL] communication. After rewiring the digital pins of the buttons to 30 and 32, both buttons now work.

8/14/2026:
- [2:13pm] After laser cutting everything, I realized that the holes for the main piece isn't spread out enough for the Joystick to attach properly, and that the hole itself for it needs to be bigger.
   - Additionally, some friction fit pieces are great, others may need some sanding. [2:26] The small screws for the walls, it's been difficult to find a screwdriver for them. 
- [2:36] Trying to place the screws and nuts in to hold is frustrating, especially with the screwdriver not fitting nicely. -And the gap on the backboard to allow cord to go through to the Arduino didn't account for the arduino standoffs I added. I'll need to adjust it in CAD and recut.
- [3:41] Unit overall needs to be taller to fit wires nicely. Hit issues again with the screws. +Screen wall needs to be thicker to not break under pressure, and to connect to the wooden plate above it.


8/13/2026:
- Updated image for wiring to be more direct. While the wiring looks cool, and I may remake the wiring diagram, TinkerCad makes it difficult to redo a bunch of wiring with a lack of a select all wires or selection method.
- Made physical wiring of everything connected. Each component works [writing to LCD screen, reading Joystick values, & button pressing].
   - Note: This took a while and was very frustating to figure out wiring everything together. Using wires that are stuck together in a row helps. My current set up can't work for the final wiring due to the screen set up, but I can now return to the figured out pins. I often forgot, and initially didn't know, I needed two pins for resetting. One that goes from the Reset pin on the Arduino to a random pin that is unlabeled on the physical LCD screen. The other being LCD_RST to any analog pin on the Arduino [I used A4].

8/12/2026:
- Attempted to solder wires to arcade pushbuttons, but the soldering iron had issues. Eventually I found it was oxidation on the tip. After resetting the soldering iron, checking temperature, and trying to de-oxidize it with the copper shavings in the soldering station, I found it ineffective. After letting it cool down, I will replace the tip with a new one.
   - Edit: switching the tip of the soldering iron fixed the problem. Soldering took a bit to get right after not doing it for a while, but I got there eventually.
- Code & Wiring:
   - Note that for the arcade button to register properly with ```buttonState = digitalRead(buttonPin);```, there needs to be a common ground with the LED GND pin and the COM/GND pin on the button.
   - AND there needs to be ```INPUT_PULLUP``` in ```pinMode(buttonPinA, INPUT_PULLUP);```. Code at [https://github.com/Logan-Martin/Mini-Arcade-Machine/blob/main/code/OnlyPushButtonCode](https://github.com/Logan-Martin/Mini-Arcade-Machine/blob/main/code/OnlyPushButtonCode)
   - Video that helped with Joystick: [https://www.youtube.com/watch?v=9z5FsTzYWE4](https://www.youtube.com/watch?v=9z5FsTzYWE4)
   - Old image for wiring: <img width="1303" height="740" alt="image" src="https://github.com/user-attachments/assets/a408ab1c-4327-4963-a7f8-4267a6d22e36" />
 - Physical: laser cut walls for bottom, screen, and buttons. The cut holes fit perfectly. 

 8/11/2026:
 - Trying this now: [https://www.instructables.com/Arduino-Mega-Touchscreen-Quiz-Using-Elegoo-28-TFT-/](https://www.instructables.com/Arduino-Mega-Touchscreen-Quiz-Using-Elegoo-28-TFT-/)
 - Edit: IT WORKS! Just need to follow instructions by guide above. Download each library, put the LCD on the arduino [soldering holes side facing away from cord port], copy the code, make sure the board is connected via the IDE, verify the code with the IDE button, if no errors, run the code.
 - CAD improvements: smaller holes for screws available, and smaller height to save material and wiring. Modeled a fake Arduino mega, push button, LCD screen, and joystick with a ball joint and put into an assembly for testing fit:
   - <img width="320" height="351" alt="image" src="https://github.com/user-attachments/assets/b4b0ca74-928d-4694-a129-cd8a7897a6c5" />

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
8/5/2026:
- Started Project
- V1 of CAD Model: https://cad.onshape.com/documents/1f67ee2ecc3e3aa01e412fcf/w/54ba2dbc630de261fbd7408a/e/83f6dcfcd872f677a0073c63?renderMode=0&uiState=6a73e49e044e03fd4e4e218f
- Note: When using Box Joint add-on, make sure walls intersect geometry with each other.
- Progress screenshot:
   - <img width="892" height="735" alt="image" src="https://github.com/user-attachments/assets/88094ea1-6ea7-4b17-8c51-4fe3e1b8c56e" />

</details>
