# DigitalLock - The Power of Security in Digital Locks and Passwords

<p align="center">
  <img src="https://img.shields.io/badge/Status-CLASSIFIED-red?style=for-the-badge" alt="Classified Badge">
</p>

<p align="center">
  <span style="font-size: 2em; color: #00ffff; text-shadow: 0 0 10px #00ffff;"></span>
  <br>
  <span style="font-family: 'Orbitron', sans-serif; font-size: 2.5em; color: #00ffff; text-shadow: 0 0 10px #00ffff, 0 0 20px #0080ff;">DARK@WEB</span>
</p>

## Overview

DigitalLock is an Arduino-based digital locking system designed to secure doors using a keypad and LCD interface. The system allows users to enter a 5-digit password to unlock a door, change the password, and includes security features like a lockout timer after multiple incorrect attempts. This project combines hardware and software to create a robust and user-friendly digital lock solution.

## Features (All Original Features + New Professional Enhancements)

- **Password-Protected Access**: Unlock the door by entering a correct 5-digit password via a 4x4 keypad.
- **LCD Feedback**: Displays prompts, password entry feedback, and status messages on a 20x4 LCD.
- **Password Change**: Allows users to change the password by entering the old password and a new one.
- **Security Lockout**: Locks the keypad for 60 seconds after three consecutive incorrect password attempts.
- **Visual Indicators**: Uses LEDs (Green, Yellow, Red) to indicate correct password, password change, or errors.
- **Relay Control**: Activates a relay to control the door lock mechanism.
- **NEW — Permanent EEPROM Storage**: Password is saved in non-volatile memory – survives power cycles.
- **NEW — First-Time Auto Setup**: On first boot, the system forces the user to set a custom password.
- **NEW — Fixed Admin Password**: `99999` always works as emergency/master key.
- **NEW — Buzzer Feedback**: Audible beep on every keypress, success, error, and lockout.
- **NEW — Clear Entry ('C' Key)**: Press 'C' to instantly clear current input.
- **NEW — Remaining Attempts Display**: LCD shows "Attempts left: X" in real time.
- **NEW — Full Keypad Disable During Lockout**: No key responds during the 60-second penalty.
- **NEW — Enhanced LCD Interface**: Professional messages, countdown timer, and better animations.

## Hardware Requirements

- **Arduino Board** (e.g., Arduino Uno)
- **4x4 Keypad**
- **20x4 LCD Display** (direct pin connection – no I2C needed)
- **LEDs**:
  - Green LED (for correct password)
  - Yellow LED (for password change / timer)
  - Red LED (for errors or warnings)
- **Relay Module** (to control the door lock)
- **Active or Passive Buzzer** (NEW – highly recommended)
- **Connecting Wires**
- **Breadboard or PCB** (for prototyping)
- **Power Supply** (compatible with Arduino and relay)

### Pin Connections (Updated with Buzzer)

| Component                 | Arduino Pin(s)              |
|---------------------------|-----------------------------|
| LCD (RS, EN, D4, D5, D6, D7) | 9, 8, 13, 12, 11, 10       |
| Keypad Rows               | 0, 1, 2, 3                  |
| Keypad Columns            | 7, 6, 5, 4                  |
| Green LED                 | A0                          |
| Yellow LED                | A1                          |
| Red LED                   | A2                          |
| Relay                     | 4                           |
| **Buzzer (NEW)**          | **A3**                      |

## Software Requirements

- **Arduino IDE** (or compatible IDE)
- **Libraries**:
  - `Keypad.h` (for keypad input)
  - `LiquidCrystal.h` (for LCD control)
  - `EEPROM.h` (built-in – for permanent password storage)

Install the libraries via the Arduino IDE Library Manager or download them from their respective repositories.

## Installation and Setup

1. **Hardware Setup**:
   - Connect the keypad, LCD, LEDs, relay, and **buzzer to A3** as per the updated pin table.
   - Ensure all connections are secure and the power supply is adequate.

2. **Software Setup**:
   - Install the Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software).
   - Install the `Keypad` and `LiquidCrystal` libraries via the Library Manager:
     - Go to `Sketch > Include Library > Manage Libraries...`
     - Search for `Keypad` and `LiquidCrystal`, then install.
   - Use the updated `DigitalLock_Pro.ino` code (provided separately).

3. **Upload the Code**:
   - Open the updated `.ino` file in the Arduino IDE.
   - Connect your Arduino board to your computer via USB.
   - Select the correct board and port under `Tools > Board` and `Tools > Port`.
   - Click `Upload` to flash the code to the Arduino.

4. **Initial Configuration**:
   - **First boot ever**: The system displays "First Time Setup" and asks you to enter your desired 5-digit password (saved permanently).
   - **Subsequent boots**: Uses your saved password.
   - **Emergency access**: Always use `99999` (admin password – cannot be changed).

## Usage

1. **Unlocking the Door**:
   - Enter the 5-digit password using the keypad.
   - Each keypress displays an asterisk (`*`) and plays a short beep.
   - If correct (or admin `99999`), Green LED + success tone, relay activates for ~3 seconds.
   - If incorrect, Red LED + error tone, attempts counter decreases.

2. **Changing the Password**:
   - Enter `##` → press `#` to confirm (or `*` to cancel).
   - Enter current password → enter new 5-digit password.
   - Yellow LED + success tone → new password saved to EEPROM.

3. **Security Features**:
   - After two incorrect attempts → warning message + tone.
   - After three incorrect attempts → keypad fully locked for 60 seconds with countdown timer, red/yellow LEDs, and continuous warning beeps.
   - Press 'C' anytime to clear current input.

## Code Explanation

The updated `DigitalLock_Pro.ino` retains all original functions and logic while adding professional enhancements:

- **setup()**: Initializes everything + loads/saves password from EEPROM + first-time setup.
- **loop()**: Handles real-time input, buzzer, clear key, and full lockout state.
- **check()**: Now also accepts admin password `99999`.
- **check_oldpassword()**: Saves new password to EEPROM.
- **change()**: Initiates password change with confirmation.
- **timer()**: Upgraded 60-second lockout with countdown and complete keypad disable.

## Troubleshooting

- **LCD Not Displaying**: Check pin connections and contrast potentiometer.
- **Keypad Not Responding**: Verify row/column wiring and library installation.
- **Relay Not Activating**: Check relay power and pin 4 connection.
- **No Sound**: Ensure buzzer is connected to A3 and is active type (or use passive with tone()).
- **Forgot Password?** → Use admin password `99999` (always works).

## Contributing

Contributions are welcome! Please follow these steps:
1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request with a detailed description of your changes.

---

*Built with Love and powered by Arduino*  
*Now with permanent memory, admin access, buzzer, and pro-level security*