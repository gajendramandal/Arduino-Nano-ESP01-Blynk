# 🔌 Arduino Nano + ESP-01 WiFi Control with Blynk IoT

> **Important:** Please read the complete README before proceeding. Following the steps correctly is essential for successful setup and operation.

Control your Arduino Nano peripherals (buzzer, LED, relay) from **anywhere in the world** using the Blynk IoT app via the ESP-01 WiFi module.

---

## 📋 Table of Contents
- [About This Project](#about-this-project)
- [Hardware Required](#hardware-required)
- [Wiring Diagram](#wiring-diagram)
- [Library Setup](#library-setup)
- [Project Structure](#project-structure)
- [Installation & Setup Guide](#installation--setup-guide)
- [Blynk App Setup](#blynk-app-setup)
- [ESP-01 Baud Rate Fix](#esp-01-baud-rate-fix)
- [Upload Code](#upload-code)
- [Troubleshooting](#troubleshooting)
- [Key Learnings](#key-learnings)
- [Credits](#credits)
- [License](#license)

---

## 📖 About This Project

This project demonstrates how to connect an **Arduino Nano** with an **ESP-01 WiFi module** to the **Blynk IoT platform** for remote control of output devices like buzzers, LEDs, and relays.

### Features
- Control buzzer/LED/relay from a phone app anywhere in the world
- Works over WiFi using the ESP-01 module
- Uses the Blynk IoT platform for a beautiful mobile dashboard
- Supports virtual pin control (V0, V1, V2...)
- Real-time response

### How It Works
```
Phone (Blynk App)
       │
       ▼
Blynk Cloud Server
       │
       ▼
ESP-01 WiFi Module
       │
       ▼
Arduino Nano
       │
       ▼
Buzzer / LED / Relay
```

---

## 🛒 Hardware Required

| Component | Quantity | Purpose |
|---|---|---|
| Arduino Nano | 1 | Main microcontroller |
| ESP-01 WiFi Module | 1 | WiFi connectivity |
| AMS1117 3.3V Regulator | 1 | Power ESP-01 safely |
| Buzzer | 1 | Output device |
| Jumper Wires | Several | Connections |
| Breadboard | 1 | Prototyping |

> ⚠️ **Important:** ESP-01 runs on 3.3V only! Never connect it to 5V — it will permanently damage the module!

---

## 🔌 Wiring Diagram

### ESP-01 to Arduino Nano:
```
ESP-01 Pin    →    Arduino Nano Pin
──────────────────────────────────
VCC           →    3.3V (via AMS1117 regulator)
GND           →    GND
TX            →    Pin 13 (RX of SoftwareSerial)
RX            →    Pin 2  (TX of SoftwareSerial)
CH_PD (EN)    →    3.3V  ← MUST be connected!
RST           →    Not connected
GPIO0         →    Not connected
GPIO2         →    Not connected
```

### Buzzer to Arduino Nano:
```
Buzzer Pin    →    Arduino Nano Pin
──────────────────────────────────
+  (positive) →    Pin 7
-  (negative) →    GND
```

### AMS1117 3.3V Regulator:
```
Input  →    5V (Arduino)
Output →    3.3V (ESP-01 VCC and CH_PD)
GND    →    GND
```

> ⚠️ **Why use an external regulator?** The Arduino Nano's 3.3V pin provides only 50mA. The ESP-01 needs up to 250mA. Using the Arduino's 3.3V pin directly causes brownouts and random resets!

---

## 📚 Library Setup

This is the trickiest part! Here is the exact setup that works.

### Problem
The new Blynk library removed `ESP8266_Lib.h`. You need TWO separate libraries:
- **Blynk** (v0.6.1) — contains `BlynkSimpleShieldEsp8266.h`
- **BlynkESP8266** — contains `ESP8266_Lib.h` and `ESP8266.cpp`

---

## 📂 Project Structure

```
├── IOT_Blynk_MC.ino
├── library/
│   ├── Blynk/
│   └── BlynkESP8266/
└── README.md
```

---

## 🚀 Installation & Setup Guide

Follow these steps to run the project successfully on your system:

### 1. Clone or Download the Repository

```bash
git clone https://github.com/your-username/your-repo-name.git
```

Or download the ZIP file and extract it.

---

### 2. Install Required Libraries

- Navigate to the `library` folder inside this repository.
- You will find two folders:
  - `Blynk`
  - `BlynkESP8266`

👉 Copy both folders.

---

### 3. Paste Libraries into Arduino

Open your Arduino libraries directory:

```
Documents/Arduino/libraries/
```

Paste both folders (`Blynk` and `BlynkESP8266`) inside the `libraries` folder.

---

### 4. Restart Arduino IDE

- Close Arduino IDE (if already open)
- Reopen it to load the new libraries

---

### 5. Open the Project File

```
IOT_Blynk_MC.ino
```

---

### 6. Select Board & Port

In Arduino IDE:

- Go to **Tools → Board → Arduino Nano**
- Select the correct **Port**

---

### 7. Upload the Code

- Click **Upload**
- Wait for compilation and uploading to complete

---

## ✅ You're Done!

Your project should now be running successfully on the Arduino Nano.

---

## ⚠️ Notes

- Make sure Arduino Nano drivers are installed
- Ensure the correct COM port is selected
- Check hardware connections if the upload fails

---

## 🛠️ Requirements

- Arduino Nano
- ESP-01 WiFi Module
- USB Cable
- Arduino IDE

---

## 📱 Blynk App Setup

### Step 1 — Download the App
Download **Blynk IoT** from the Play Store or App Store.

### Step 2 — Create an Account
Sign up at [blynk.cloud](https://blynk.cloud)

### Step 3 — Create a Template
```
Blynk App → + New Template
Name     → LED ON OFF
Hardware → Arduino Nano
```

Copy these values to your code:
- `BLYNK_TEMPLATE_ID`
- `BLYNK_TEMPLATE_NAME`

### Step 4 — Create a Device
```
My Devices → + New Device
Select your template
```

Copy the `Auth Token` to your code.

### Step 5 — Add a Datastream
```
Template → Datastreams → + New Datastream
Type      → Virtual Pin
Pin       → V0
Data Type → Integer
Min       → 0
Max       → 1
```

### Step 6 — Add a Button Widget
```
Dashboard → Edit → + Widget → Button
Pin  → V0
Mode → Switch
```

---

## ⚙️ ESP-01 Baud Rate Fix (Optional but Recommended)

> ℹ️ **Note:** If you want to use the factory default baud rate (115200), you can skip this step. However, it is strongly recommended to change it to 9600 for reliable communication with SoftwareSerial.

> ⚠️ **Why change it?** The ESP-01 factory default baud rate is **115200**. SoftwareSerial on Arduino Nano is unreliable at 115200 and causes garbled data. Changing it to **9600** makes communication stable and reliable.

### Run This ONE-TIME Code:

```cpp
#include <SoftwareSerial.h>
SoftwareSerial espSerial(13, 2);

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);  // Start at factory default
  delay(2000);
  Serial.println("Changing baud rate to 9600...");
  espSerial.println("AT+UART_DEF=9600,8,1,0,0");  // Save permanently
  delay(3000);
  espSerial.begin(9600);  // Switch to verify
  espSerial.println("AT");
  delay(2000);
  String r = "";
  while (espSerial.available()) r += (char)espSerial.read();
  if (r.indexOf("OK") != -1) Serial.println("SUCCESS! ESP now at 9600!");
  else Serial.println("Check wiring and try again");
}
void loop() {}
```

Upload this → Open Serial Monitor at 9600 → Press RESET → Wait for "SUCCESS!"

After this, the ESP-01 permanently remembers 9600 baud even after power off!

---

## 💻 Upload Code

### Main Blynk Control Code:
Use the code below, or simply download the repository, open `IOT_Blynk_MC.ino` in Arduino IDE, and upload it directly.

```cpp
// Fill in your Blynk credentials here
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <SoftwareSerial.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// WiFi credentials
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// SoftwareSerial for ESP-01
// Pin 13 = RX (connect to TX of ESP-01)
// Pin 2  = TX (connect to RX of ESP-01)
SoftwareSerial EspSerial(13, 2);

// Use 9600 after baud rate change
// Use 115200 if keeping factory default
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

// Output pin (buzzer/LED/relay)
#define OUTPUT_PIN 7

// This function runs when the button is pressed in the Blynk app
BLYNK_WRITE(V0) {
  int value = param.asInt();  // 1 = ON, 0 = OFF
  if (value == 1) {
    digitalWrite(OUTPUT_PIN, HIGH);
    Serial.println("ON");
  } else {
    digitalWrite(OUTPUT_PIN, LOW);
    Serial.println("OFF");
  }
}

void setup() {
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(1000);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
}
```

### Upload Steps:
```
STEP 1  → Disconnect ESP-01 from Arduino
STEP 2  → Connect Arduino to PC via USB
STEP 3  → Open Arduino IDE
STEP 4  → Select Board → Arduino Nano
STEP 5  → Select ATmega328P (Old Bootloader) if needed
STEP 6  → Select the correct COM port
STEP 7  → Upload the code
STEP 8  → Reconnect ESP-01
STEP 9  → Open Serial Monitor at 9600
STEP 10 → Wait for "Blynk Connected!"
```

> ⚠️ Always disconnect ESP-01 before uploading! Having ESP-01 connected during upload causes upload failures.

---

## 🔧 Troubleshooting

### Garbled text ⸮⸮⸮ in Serial Monitor
```
Cause → Baud rate mismatch
Fix   → Run the baud rate change code first (see above)
        Set Serial Monitor to 9600
```

### ESP-01 Not Responding
```
Cause → Wrong wiring or CH_PD not connected
Fix   → Check TX/RX connections (try swapping them)
        Verify CH_PD is connected to 3.3V
        Check power supply (use AMS1117 regulator!)
```

### WiFi FAIL
```
Cause → Wrong credentials or 5GHz router
Fix   → Verify WiFi name and password in the code
        ESP-01 only supports 2.4GHz networks!
        Try using a phone hotspot instead
```

### Blynk Login Timeout
```
Cause → Wrong Auth Token or slow connection
Fix   → Verify Auth Token copied from Blynk app
        Check internet connection on your phone/router
        Increase delay() in setup()
```

### Failed to Enable MUX
```
Cause → ESP-01 busy or wrong baud rate
Fix   → Press RESET button on Arduino
        Verify baud rate is set to 9600
```

### Upload Failed
```
Cause → ESP-01 connected during upload
Fix   → Always disconnect ESP-01 before uploading!
```

---

## 🧠 Key Learnings

### Baud Rate
```
Serial.begin(9600)     → Arduino to PC speed (matches Serial Monitor)
EspSerial.begin(9600)  → Arduino to ESP-01 speed (must match ESP-01)
Both sides must use the same speed!
```

### SoftwareSerial Limitation
```
SoftwareSerial is unreliable above 9600 baud on Arduino Nano
It is recommended to change ESP-01 from 115200 to 9600
Use the F() macro to save RAM on Arduino Nano
Use byte arrays instead of String for handling binary data
```

---

## 🙏 Credits

- [Blynk](https://blynk.io) — IoT platform
- [ESP8266 AT Firmware](https://github.com/espressif/esp-at) — ESP-01 firmware
- [BlynkESP8266](https://github.com/vshymanskyy/BlynkESP8266) — ESP8266 library for Blynk

---

## 📄 License

MIT License — Free to use, modify, and distribute!

---

## ⭐ If This Helped You

Give this repo a ⭐ star so others can find it easily!

If you face any issues → open an Issue on GitHub!

---

*Made with ❤️ for the Arduino IoT community*