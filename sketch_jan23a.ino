#include <WiFi.h>
#include <WebServer.h>

#define DOT_BUTTON 4      // GPIO4 for dot/space
#define DASH_BUTTON 5     // GPIO5 for dash/newline
#define BACKSPACE_BUTTON 23 // GPIO23 for backspace (delete one character)
#define LED_PIN 2         // GPIO2 for LED

const char* ssid = "Morse_AP";
const char* password = "12345678";

WebServer server(80);

// Timing constants
const int LETTER_TIMEOUT = 1000;
const int DEBOUNCE = 50;
const int LONG_PRESS_DURATION = 600;

// Morse code lookup tables
const char* const MORSE_LETTERS[] PROGMEM = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

const char* const MORSE_DIGITS[] PROGMEM = {
  "-----", ".----", "..---", "...--", "....-",
  ".....", "-....", "--...", "---..", "----."
};

String currentCode = "";
unsigned long lastAction = 0;
String decodedMessage = "";

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
<head>
  <meta charset='UTF-8'>
  <title>Morse Decoder</title>
  <style>
    body { font-family: monospace; background: #f0f0f0; padding: 20px; }
    h1 { color: #333; }
    pre {
      background: #fff;
      padding: 15px;
      border: 1px solid #ccc;
      border-radius: 5px;
      font-size: 1.3em;
      white-space: pre-wrap;
    }
    .cursor {
      display: inline-block;
      width: 10px;
      animation: blink 1s step-start infinite;
    }
    @keyframes blink {
      50% { background: black; color: black; }
      100% { background: transparent; color: transparent; }
    }
  </style>
  <script>
    setInterval(() => {
      fetch("/data")
        .then(response => response.text())
        .then(data => {
          document.getElementById("output").innerHTML = data + "<span class='cursor'>|</span>";
        });
    }, 500);
  </script>
</head>
<body>
  <h1>Decoded Morse:</h1>
  <pre id="output">Loading<span class='cursor'>|</span></pre>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send_P(200, "text/html", htmlPage);
}

void handleData() {
  server.send(200, "text/html", decodedMessage);
}

void setup() {
  Serial.begin(115200);
  pinMode(DOT_BUTTON, INPUT_PULLUP);
  pinMode(DASH_BUTTON, INPUT_PULLUP);
  pinMode(BACKSPACE_BUTTON, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  WiFi.softAP(ssid, password);
  Serial.println("AP Started: " + WiFi.softAPIP().toString());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  unsigned long currentTime = millis();
  server.handleClient();

  // Check backspace button first with proper debouncing
  if (digitalRead(BACKSPACE_BUTTON) == LOW) {
    delay(DEBOUNCE); // Debounce delay
    if (digitalRead(BACKSPACE_BUTTON) == LOW) { // Confirm button is still pressed
      digitalWrite(LED_PIN, HIGH);
      delay(100); // Visual feedback
      digitalWrite(LED_PIN, LOW);
      
      if (decodedMessage.length() > 0) {
        // Remove last character
        decodedMessage.remove(decodedMessage.length()-1);
        Serial.println("<Backspace>");
      }
      
      // Clear any pending Morse code
      currentCode = "";
      lastAction = currentTime;
      
      // Wait for button release
      while (digitalRead(BACKSPACE_BUTTON) == LOW);
      return; // Skip other button checks this loop
    }
  }

  // DOT Button
  if (digitalRead(DOT_BUTTON) == LOW) {
    delay(DEBOUNCE);
    if (digitalRead(DOT_BUTTON) == LOW) {
      unsigned long pressStart = millis();
      digitalWrite(LED_PIN, HIGH);
      while (digitalRead(DOT_BUTTON) == LOW);
      digitalWrite(LED_PIN, LOW);
      unsigned long duration = millis() - pressStart;

      if (duration >= LONG_PRESS_DURATION) {
        decodedMessage += " ";
        Serial.print(" ");
      } else {
        currentCode += ".";
        lastAction = currentTime;
      }
    }
  }

  // DASH Button
  if (digitalRead(DASH_BUTTON) == LOW) {
    delay(DEBOUNCE);
    if (digitalRead(DASH_BUTTON) == LOW) {
      unsigned long pressStart = millis();
      digitalWrite(LED_PIN, HIGH);
      while (digitalRead(DASH_BUTTON) == LOW);
      digitalWrite(LED_PIN, LOW);
      unsigned long duration = millis() - pressStart;

      if (duration >= LONG_PRESS_DURATION) {
        decodedMessage += "\n";
        Serial.println(" ");
      } else {
        currentCode += "-";
        lastAction = currentTime;
      }
    }
  }

  // Decode after timeout
  if (currentCode.length() > 0 && (currentTime - lastAction) > LETTER_TIMEOUT) {
    char decoded = '?';

    for (int i = 0; i < 26; i++) {
      if (currentCode.equals(String(FPSTR(MORSE_LETTERS[i])))) {
        decoded = 'A' + i;
        break;
      }
    }

    if (decoded == '?') {
      for (int i = 0; i < 10; i++) {
        if (currentCode.equals(String(FPSTR(MORSE_DIGITS[i])))) {
          decoded = '0' + i;
          break;
        }
      }
    }

    decodedMessage += decoded;
    Serial.print(decoded);
    currentCode = "";
  }

  delay(5);
}