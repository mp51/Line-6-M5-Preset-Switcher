# Line 6 M5 Preset Switcher
MIDI commands preset switcher for Line 6 M5 on Arduino Pro Micro (Leonardo).

![switcherdrawing](https://user-images.githubusercontent.com/15908138/39406359-f43e2472-4bb5-11e8-947d-f4c644077170.png)

## Switcher logic

### Preset switching
  * Next preset:     Button 1 (UP)
  * Previous preset: Button 2 (DOWN)

### Bank switching:

| Action         | Bank | Presets    | Indication  |
| ----------- |----- | ---------- | ----------- |
| Press both buttons (default on startup)    | 0    | 1-24 (all) | All LEDs    |
| Hold Button 1 (UP)   | 1    | 1-5        | LED1 (Green)|
| Hold Button 2 (DOWN) | 1    | 5-10        | LED2 (Red)  |
| Hold both buttons    | 3    | 11-15        | LED3 (Blue) |


## Board 
Code written for Arduino Pro Micro (Leonardo). Can be adjusted for other boards by altering `Serial1` related code to `Serial`.
 
Wiring:

| I/O         | Pin   |
| ----------- |-------|
| MIDI Out    | Tx0   |
| Button Up   | Pin 2 |
| Button Down | Pin 3 |
| LED1 (Green)| Pin 9 |
| LED2 (Red)  | Pin 7 |
| LED3 (Blue) | Pin 8 |

Written by Marcin Pęczkowski, 2018
