# ESP32-Morse-Code-Decoder-with-Web-Display
Decode Morse code using physical buttons and visualize the result live on a local web interface hosted by the ESP32.

📝 Description
This project turns an ESP32 into a Morse code decoder using three physical buttons:

Dot/Space

Dash/Newline

Backspace

Decoded text is displayed in real-time through a local Wi-Fi access point. The web interface updates automatically using JavaScript fetch polling.


✨ Features
🧠 Morse code decoding with physical input (dots, dashes, space, newline, backspace).

🌐 ESP32 creates its own Wi-Fi Access Point (AP) — no internet needed.

🖥️ Clean real-time web interface to view the decoded output.

🔙 Backspace support to delete the last decoded character.

💡 Onboard LED feedback for button press events.


Component | Quantity | Notes
ESP32 Dev Board | 1 | Main microcontroller
Push Buttons | 3 | For Dot, Dash, and Backspace
10kΩ Resistor | 2 | Pull-down for Dot and Backspace
6.8kΩ Resistor | 1 | Pull-down for Dash button (D5/GPIO5)
Breadboard & Jumper Wires | As needed | For prototyping


ESP32 Pin | Button Function | Resistor | Connected To
GPIO4 | Dot / Space | 10kΩ | Button → GND
GPIO5 | Dash / Newline | 6.8kΩ | Button → GND
GPIO23 | Backspace | 10kΩ | Button → GND
GPIO2 | LED Indicator | - | Built-in on ESP32

Note: Use INPUT_PULLUP in the code. This means buttons should connect one leg to GPIO and the other to GND. Resistors are used for clean signals.



⚙️ How It Works
Start-Up:

ESP32 creates a Wi-Fi AP named Morse_AP with password 12345678.

Access the server by connecting your mobile or laptop to this AP and navigating to 192.168.4.1.

Morse Input:

Short Press on DOT button: Adds a . to the current Morse character.

Short Press on DASH button: Adds a -.

Long Press on DOT button: Adds a space ( ) between words.

Long Press on DASH button: Adds a newline (\n) in the output.

Backspace button: Removes the last decoded character.

Decoding:

After a short inactivity (1s), current Morse code is decoded into a letter or number and added to the displayed message.

Web Interface:

Simple UI updates every 500ms with the latest message.

Shows live typing with a blinking cursor effect.
