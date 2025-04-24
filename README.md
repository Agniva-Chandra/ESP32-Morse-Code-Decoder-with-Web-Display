# 📡 ESP32 Morse Code Decoder with Web Display

Decode Morse code using physical buttons and visualize the result live on a local web interface hosted by the ESP32.

---

## 📝 Description

This project turns an ESP32 into a Morse code decoder using three physical buttons:

- **DOT / Space**
- **DASH / Newline**
- **Backspace**

The decoded message is displayed in real-time through a local Wi-Fi Access Point.  
The web interface updates automatically using JavaScript polling — no internet needed.

---

## ✨ Features

- 🧠 Physical button-controlled Morse code input.
- 📶 ESP32 creates its own Wi-Fi AP — no internet required.
- 🌐 Real-time decoded output visible on a web page.
- 🔙 Backspace support to delete the last character.
- 💡 Built-in LED feedback for button presses.

---

## real photo of device

![image](https://github.com/user-attachments/assets/c525235b-b4a4-47cf-af96-72b5ac56b232)


## 🔧 Components Required

| Component           | Quantity   | Details                                      |
|---------------------|------------|----------------------------------------------|
| ESP32 Dev Board      | 1          | Main microcontroller                         |
| Push Buttons         | 3          | For Dot, Dash, and Backspace                 |
| 10kΩ Resistor        | 2          | Pull-down for Dot and Backspace buttons      |
| 6.8kΩ Resistor       | 1          | Pull-down for Dash button (D5/GPIO5)         |
| Breadboard + Wires   | As needed  | For prototyping                              |

---

## circuit diagram 

![image](https://github.com/user-attachments/assets/1c85d204-0d5a-40b1-9afc-1afa8fc3bf83)


## 🧩 Circuit Connections

| ESP32 Pin | Button Function | Resistor | Connection       |
|-----------|------------------|----------|------------------|
| GPIO4     | Dot / Space       | 10kΩ     | Button → GND      |
| GPIO5     | Dash / Newline    | 6.8kΩ    | Button → GND      |
| GPIO23    | Backspace         | 10kΩ     | Button → GND      |
| GPIO2     | LED (feedback)    | *(none)* | Built-in on ESP32 |

> 🔧 **Note:** Buttons are configured using `INPUT_PULLUP`. That means one end of the button goes to the GPIO pin, and the other to **GND**.

---

## ⚙️ How It Works

## morse code chart

![image](https://github.com/user-attachments/assets/6ebabd35-bb32-49d5-b8bf-dfb5e8f863f2)


### 📶 ESP32 as Wi-Fi AP

The ESP32 starts a local Wi-Fi network:
- **SSID:** `Morse_AP`  
- **Password:** `12345678`

Connect your device to this network and open [http://192.168.4.1](http://192.168.4.1) in a browser.

---

### 🔘 Button Functions

- **DOT Button (short press):** Adds `.`
- **DASH Button (short press):** Adds `-`
- **DOT Button (long press):** Adds space (` `)
- **DASH Button (long press):** Adds newline (`\n`)
- **Backspace Button:** Deletes the last decoded character

---

## result serial monitor

![image](https://github.com/user-attachments/assets/5a9e9247-dab8-412d-99f4-38bf280d5705)


### 🔡 Morse Decoding

If no button is pressed for **1 second**, the current Morse sequence is decoded into a letter or digit using internal lookup tables.

---

### 🌐 Live Web Output

- The webpage auto-refreshes every **500ms** using JavaScript.
- Shows the full decoded message live.
- Includes a **blinking cursor** animation for a terminal-style display.

---


## result in Access Point (AP) 

![image](https://github.com/user-attachments/assets/5a63a407-4de5-4f35-b498-8bc08742ff43)

