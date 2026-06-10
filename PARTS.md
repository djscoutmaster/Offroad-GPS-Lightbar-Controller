# Parts List / Bill of Materials

This list combines the original prototype parts list with the requirements from the project document. Items marked **Verify** need a final decision before ordering or publishing the repo.

## Required controller parts

| Qty | Part / module | Example / compatible part | Purpose | Status | Notes |
|---:|---|---|---|---|---|
| 1 | Main microcontroller | Arduino Mega 2560 | Runs the Smart Light Bar Controller sketch | **Required / verify** | The requirements target a Mega 2560. The original compact parts list references a DFRobot Beetle, so pick one official target. Current pin usage strongly favors the Mega because pins 41-49 are used. |
| 1 | GPS module | NEO-6M-compatible or GT-U7 GPS module | Reads vehicle speed | Required | Confirm serial voltage level, antenna placement, and whether the module supports 10 Hz updates. |
| 1 | Accelerometer | ADXL345-compatible module | Detects activity/inactivity state | Required / partially implemented | Use I2C or SPI consistently and document the interrupt pin. |
| 1 | Momentary push button | 6 mm x 6 mm through-hole push button | User input for speed calibration | Required | Current sketch uses pin 2 with debounce. |
| 1 | Piezo buzzer | TBM12A05-compatible | Audible feedback for button actions and status | Required | Current sketch uses pin 4. |
| 6 | Indicator LEDs | 3 mm or 5 mm LEDs | Shows active light setting 1-6 | Required | Add current-limiting resistors. |
| 1 | Blue status LED | 3 mm or 5 mm blue LED | Accelerometer/status indication | Required | Intended for inactivity/activity state. Current code also uses it during GPS update checks. |
| 1 | Red error LED | 3 mm or 5 mm red LED | GPS and signal error indication | Required | Should flash non-blocking for error states. |
| 8+ | LED resistors | 220-330 Ω typical | Limits LED current | Required | Size based on LED forward voltage and desired brightness. |
| 1 | 5 V buck regulator | Adafruit MPM3610 Buck Converter or automotive-rated 12 V-to-5 V converter | Powers controller from vehicle 12 V | Required / verify | For vehicle use, prefer an automotive-rated regulator with transient protection. |
| 1 | Enclosure | New Age Medium Utility S-352510 | Protects electronics | Prototype part | Original parts list references this enclosure. Confirm fit with final PCB and connectors. |

## Signal interface and vehicle-install parts

| Qty | Part / module | Purpose | Recommendation |
|---:|---|---|---|
| 1 | Inline fuse holder + fuse | Protects the 12 V feed | Add near the power source. Size the fuse to the controller and wiring, not the light bar. |
| 1 | Reverse-polarity protection | Protects against accidental reverse wiring | Consider a series Schottky diode or ideal-diode MOSFET circuit. |
| 1 | TVS diode or automotive transient protection | Protects against load dumps and voltage spikes | Strongly recommended for vehicle electrical systems. |
| 1 | Common ground connection | Shared reference for controller and light-bar signal | Required for reliable 5 V digital signaling. |
| As needed | Waterproof connectors | Serviceable vehicle wiring | Use locking connectors if installed in a vehicle. |
| As needed | Wire, heat-shrink, loom, strain relief | Durable install | Avoid breadboards or loose jumpers in the vehicle. |
| As needed | Headers / screw terminals | Board connections | Choose connectors that match the enclosure and vibration environment. |

## PCB and fabrication files

| File / folder | Purpose |
|---|---|
| `PCB DESIGN/PCB_PCB_Light Bar Controller v2_2_2022-02-16_2022-04-08.pcbdoc` | PCB design source/export. |
| `PCB DESIGN/PCB_PCB_Light Bar Controller v2_2_2022-02-16_2022-04-08.dxf` | Mechanical / board outline export. |
| `PCB DESIGN/Gerber out/GerberFiles/` | Gerber files for PCB fabrication. |
| `PCB DESIGN/Gerber out/DrillFiles/` | Drill files for PCB fabrication. |
| `PCB DESIGN/Gerber out/Assembly/` | Assembly output files. |

## Original compact prototype parts list

These were present in the original `Parts List.rtf` file:

| Part | Notes |
|---|---|
| DFRobot Beetle | Compact Arduino-compatible board. Verify compatibility with the current sketch before listing as the main target. |
| Adafruit MPM3610 Buck Converter | 12 V-to-5 V power conversion candidate. |
| 6 mm x 6 mm through-hole push button | User input button. |
| GT-U7 GPS module | GPS speed module. |
| Tatoko 20PCS 10 mm x 3 mm mini vibration motors, DC 3 V | Original list item. Verify if these are still needed; the requirements call for a piezo buzzer, not vibration motors. |
| New Age Medium Utility - S-352510 enclosure | Prototype enclosure. |

## Final BOM cleanup needed

Before publishing the repo publicly, I would resolve these items:

- Pick one official controller board: **Arduino Mega 2560** or **DFRobot Beetle**.
- Add exact resistor values for each LED.
- Add the exact connector types used for power, ground, controller input, and light-bar output.
- Add the final accelerometer interrupt pin.
- Add the final GPS serial port wiring and baud/update rate.
- Add links to exact purchase pages if you want the repo to be builder-friendly.
- Separate **prototype parts** from **recommended vehicle-install parts** so people do not copy breadboard-style wiring into a vehicle.
