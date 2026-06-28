#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

WebServer server(80);

// Your WiFi credentials
const char* ssid = "wifi_name";
const char* password = "wifi_password";

// L298N pins
#define IN1 32   // Left motor
#define IN2 33
#define IN3 27   // Right motor
#define IN4 14

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ---------------------------------------------------------
// UNIVERSAL (PC & MOBILE) NEON WEB INTERFACE
// ---------------------------------------------------------
String webPage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no, orientation=landscape">
  <title>ESP32 Pro Controller</title>
  <style>
    @import url('https://fonts.googleapis.com/css2?family=Orbitron:wght@500;700&display=swap');

    body {
      font-family: 'Orbitron', sans-serif;
      background: radial-gradient(circle at 50% 50%, #1a1a24 0%, #08080c 100%);
      margin: 0;
      height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      touch-action: none;
      user-select: none;
      -webkit-user-select: none;
      overflow: hidden;
    }
    
    .gamepad-shell {
      background: linear-gradient(145deg, #181822, #0f0f15);
      border-radius: 80px;
      box-shadow: 
        0 20px 50px rgba(0,0,0,0.9), 
        inset 0 3px 6px rgba(255,255,255,0.05),
        inset 0 -3px 6px rgba(0,0,0,0.5),
        0 0 40px rgba(0, 229, 255, 0.1);
      border: 1px solid #2a2a35;
      padding: 30px 50px;
      display: flex;
      justify-content: space-between;
      align-items: center;
      width: 85vw;
      max-width: 800px;
      height: 220px;
      position: relative;
    }

    .dashboard {
      position: absolute;
      left: 50%;
      top: 50%;
      transform: translate(-50%, -50%);
      display: flex;
      flex-direction: column;
      align-items: center;
      width: 200px;
    }

    .brand {
      color: #555;
      font-size: 14px;
      letter-spacing: 4px;
      margin-bottom: 5px;
      text-shadow: 0 1px 1px rgba(0,0,0,0.8);
    }
    
    .pc-controls {
      color: #333;
      font-size: 10px;
      letter-spacing: 1px;
      margin-bottom: 10px;
    }

    .led-screen {
      background: #050505;
      border: 2px solid #222;
      border-radius: 8px;
      padding: 10px 20px;
      width: 100%;
      text-align: center;
      box-shadow: inset 0 0 15px rgba(0,0,0,0.8);
      position: relative;
      overflow: hidden;
    }
    
    .led-screen::after {
      content: ""; position: absolute; top: 0; left: 0; width: 100%; height: 100%;
      background: linear-gradient(rgba(18, 16, 16, 0) 50%, rgba(0, 0, 0, 0.25) 50%), linear-gradient(90deg, rgba(255, 0, 0, 0.06), rgba(0, 255, 0, 0.02), rgba(0, 0, 255, 0.06));
      background-size: 100% 4px, 6px 100%;
      pointer-events: none;
    }

    #status {
      color: #333;
      font-weight: 700;
      font-size: 22px;
      letter-spacing: 2px;
      text-shadow: none;
      transition: all 0.2s;
    }
    #status.glow-cyan { color: #00e5ff; text-shadow: 0 0 10px #00e5ff, 0 0 20px #00e5ff; }
    #status.glow-pink { color: #ff007f; text-shadow: 0 0 10px #ff007f, 0 0 20px #ff007f; }

    .stick-container { display: flex; flex-direction: column; align-items: center; z-index: 10; }
    .stick-label { font-size: 12px; letter-spacing: 2px; margin-bottom: 15px; font-weight: 700; }
    .label-cyan { color: #00e5ff; text-shadow: 0 0 5px rgba(0, 229, 255, 0.5); }
    .label-pink { color: #ff007f; text-shadow: 0 0 5px rgba(255, 0, 127, 0.5); }

    .joystick-base {
      width: 150px; height: 150px; background: #111; border-radius: 50%;
      position: relative; display: flex; justify-content: center; align-items: center;
    }

    #base-left { border: 3px solid #005f6b; box-shadow: 0 0 20px rgba(0, 229, 255, 0.2), inset 0 0 30px rgba(0, 229, 255, 0.1); }
    #base-left.active { border-color: #00e5ff; box-shadow: 0 0 30px rgba(0, 229, 255, 0.6), inset 0 0 40px rgba(0, 229, 255, 0.3); }

    #base-right { border: 3px solid #6b0035; box-shadow: 0 0 20px rgba(255, 0, 127, 0.2), inset 0 0 30px rgba(255, 0, 127, 0.1); }
    #base-right.active { border-color: #ff007f; box-shadow: 0 0 30px rgba(255, 0, 127, 0.6), inset 0 0 40px rgba(255, 0, 127, 0.3); }

    .joystick-knob {
      width: 75px; height: 75px;
      background: radial-gradient(circle at 35% 35%, #4a4a55 0%, #22222b 50%, #111115 100%);
      border-radius: 50%; position: absolute;
      box-shadow: 0 15px 25px rgba(0,0,0,0.9), inset 0 2px 4px rgba(255,255,255,0.3), inset 0 -2px 10px rgba(0,0,0,0.8);
      border: 1px solid #000;
      transition: transform 0.1s cubic-bezier(0.25, 0.8, 0.25, 1);
      cursor: pointer; display: flex; justify-content: center; align-items: center;
    }
    
    .joystick-knob::after {
      content: ""; width: 30px; height: 30px; border-radius: 50%;
      background: repeating-radial-gradient(#111 0, #111 2px, transparent 3px, transparent 4px); opacity: 0.5;
    }

    .active .joystick-knob { transition: none; }
    /* Re-enable smooth transition for keyboard snapping */
    .keyboard-active .joystick-knob { transition: transform 0.1s cubic-bezier(0.25, 0.8, 0.25, 1); }

    .axis-y { position: absolute; width: 2px; height: 100%; background: linear-gradient(to bottom, transparent, rgba(0,229,255,0.5), transparent); }
    .axis-x { position: absolute; width: 100%; height: 2px; background: linear-gradient(to right, transparent, rgba(255,0,127,0.5), transparent); }

    /* Only show phone rotation warning on actual touch devices */
    @media screen and (orientation: portrait) and (pointer: coarse) {
      body::before {
        content: "PLEASE ROTATE PHONE 🔄";
        position: absolute; z-index: 100; color: #00e5ff; font-size: 24px;
        text-align: center; width: 100%; text-shadow: 0 0 20px #00e5ff;
      }
      .gamepad-shell { opacity: 0.1; pointer-events: none; }
    }
  </style>
</head>
<body>

  <div class="gamepad-shell">
    
    <div class="stick-container">
      <div class="stick-label label-cyan">THROTTLE (W/S)</div>
      <div id="base-left" class="joystick-base">
        <div class="axis-y"></div>
        <div id="knob-left" class="joystick-knob"></div>
      </div>
    </div>

    <div class="dashboard">
      <div class="brand">ESP-32 PRO</div>
      <div class="pc-controls">WASD / ARROWS</div>
      <div class="led-screen">
        <div id="status">STANDBY</div>
      </div>
    </div>

    <div class="stick-container">
      <div class="stick-label label-pink">STEER (A/D)</div>
      <div id="base-right" class="joystick-base">
        <div class="axis-x"></div>
        <div id="knob-right" class="joystick-knob"></div>
      </div>
    </div>

  </div>

  <script>
    const baseLeft = document.getElementById('base-left');
    const knobLeft = document.getElementById('knob-left');
    const baseRight = document.getElementById('base-right');
    const knobRight = document.getElementById('knob-right');
    const statusText = document.getElementById('status');

    let currentCommand = 'stop';
    
    // Command Variables
    let touchThrottle = 0; let touchSteering = 0;
    let maxRadius = (baseLeft.clientWidth / 2) - (knobLeft.clientWidth / 2); 

    // --- SHARED DASHBOARD UPDATE ---
    function sendCommand(nextCommand) {
      if (currentCommand !== nextCommand) {
        currentCommand = nextCommand;
        statusText.innerText = nextCommand.toUpperCase();
        
        statusText.className = '';
        if(nextCommand === 'stop') statusText.innerText = 'STANDBY';
        else if(nextCommand === 'forward' || nextCommand === 'backward') statusText.className = 'glow-cyan';
        else statusText.className = 'glow-pink';
        
        fetch('/' + nextCommand);
      }
    }

    // ==========================================
    // 1. MOBILE TOUCH LOGIC
    // ==========================================
    let isLeftDragging = false;
    let isRightDragging = false;

    function evaluateTouch() {
      if (touchSteering === 1) sendCommand('right');
      else if (touchSteering === -1) sendCommand('left');
      else if (touchThrottle === 1) sendCommand('forward');
      else if (touchThrottle === -1) sendCommand('backward');
      else sendCommand('stop');
    }

    // Left Stick (Touch)
    baseLeft.addEventListener('touchstart', (e) => {
      isLeftDragging = true; baseLeft.classList.add('active');
    }, { passive: false });
    
    baseLeft.addEventListener('touchmove', (e) => {
      if (!isLeftDragging) return; e.preventDefault();
      let rect = baseLeft.getBoundingClientRect();
      let centerY = rect.top + (rect.height / 2);
      let dy = e.targetTouches[0].clientY - centerY;

      if (dy > maxRadius) dy = maxRadius; if (dy < -maxRadius) dy = -maxRadius;
      knobLeft.style.transform = `translate(0px, ${dy}px)`;

      if (Math.abs(dy) < 15) touchThrottle = 0;
      else if (dy < 0) touchThrottle = 1; else touchThrottle = -1;
      evaluateTouch();
    }, { passive: false });
    
    baseLeft.addEventListener('touchend', () => {
      isLeftDragging = false; baseLeft.classList.remove('active');
      knobLeft.style.transform = `translate(0px, 0px)`;
      touchThrottle = 0; evaluateTouch();
    });

    // Right Stick (Touch)
    baseRight.addEventListener('touchstart', (e) => {
      isRightDragging = true; baseRight.classList.add('active');
    }, { passive: false });
    
    baseRight.addEventListener('touchmove', (e) => {
      if (!isRightDragging) return; e.preventDefault();
      let rect = baseRight.getBoundingClientRect();
      let centerX = rect.left + (rect.width / 2);
      let dx = e.targetTouches[0].clientX - centerX;

      if (dx > maxRadius) dx = maxRadius; if (dx < -maxRadius) dx = -maxRadius;
      knobRight.style.transform = `translate(${dx}px, 0px)`;

      if (Math.abs(dx) < 15) touchSteering = 0;
      else if (dx > 0) touchSteering = 1; else touchSteering = -1;
      evaluateTouch();
    }, { passive: false });
    
    baseRight.addEventListener('touchend', () => {
      isRightDragging = false; baseRight.classList.remove('active');
      knobRight.style.transform = `translate(0px, 0px)`;
      touchSteering = 0; evaluateTouch();
    });

    // ==========================================
    // 2. PC KEYBOARD LOGIC
    // ==========================================
    const activeKeys = new Set();
    
    window.addEventListener('keydown', (e) => {
      const key = e.key.toLowerCase();
      if (['w', 'a', 's', 'd', 'arrowup', 'arrowdown', 'arrowleft', 'arrowright'].includes(key)) {
        if (!activeKeys.has(key)) {
          activeKeys.add(key);
          evaluateKeyboard();
        }
      }
    });

    window.addEventListener('keyup', (e) => {
      const key = e.key.toLowerCase();
      if (activeKeys.has(key)) {
        activeKeys.delete(key);
        evaluateKeyboard();
      }
    });

    function evaluateKeyboard() {
      // Don't interfere if someone is currently using the touch screen
      if (isLeftDragging || isRightDragging) return; 

      let nextCommand = 'stop';
      
      // Right Stick Animation & Logic
      if (activeKeys.has('d') || activeKeys.has('arrowright')) {
        nextCommand = 'right';
        knobRight.style.transform = `translate(${maxRadius}px, 0px)`;
        baseRight.classList.add('keyboard-active', 'active');
      } else if (activeKeys.has('a') || activeKeys.has('arrowleft')) {
        nextCommand = 'left';
        knobRight.style.transform = `translate(-${maxRadius}px, 0px)`;
        baseRight.classList.add('keyboard-active', 'active');
      } else {
        knobRight.style.transform = `translate(0px, 0px)`;
        baseRight.classList.remove('keyboard-active', 'active');
      }

      // Left Stick Animation & Logic (Steering overrides throttle visually and logically)
      if (nextCommand === 'stop') {
        if (activeKeys.has('w') || activeKeys.has('arrowup')) {
          nextCommand = 'forward';
          knobLeft.style.transform = `translate(0px, -${maxRadius}px)`;
          baseLeft.classList.add('keyboard-active', 'active');
        } else if (activeKeys.has('s') || activeKeys.has('arrowdown')) {
          nextCommand = 'backward';
          knobLeft.style.transform = `translate(0px, ${maxRadius}px)`;
          baseLeft.classList.add('keyboard-active', 'active');
        } else {
          knobLeft.style.transform = `translate(0px, 0px)`;
          baseLeft.classList.remove('keyboard-active', 'active');
        }
      } else {
        // If steering is active, visual reset the throttle stick
        knobLeft.style.transform = `translate(0px, 0px)`;
        baseLeft.classList.remove('keyboard-active', 'active');
      }

      sendCommand(nextCommand);
    }
  </script>
</body>
</html>
)rawliteral";
  return html;
}

// Handlers now send a simple "OK" back to the background JavaScript
void handleRoot()     { server.send(200, "text/html", webPage()); }
void handleForward()  { moveForward();  server.send(200, "text/plain", "OK"); }
void handleBackward() { moveBackward(); server.send(200, "text/plain", "OK"); }
void handleLeft()     { moveLeft();     server.send(200, "text/plain", "OK"); }
void handleRight()    { moveRight();    server.send(200, "text/plain", "OK"); }
void handleStop()     { stopMotors();   server.send(200, "text/plain", "OK"); }
void handleNotFound() { server.send(404, "text/plain", "Not found"); }

void setup() {
  Serial.begin(115200);

  // Initialize motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ensure motors are stopped on startup
  stopMotors();

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Setup mDNS
  if (MDNS.begin("esp32car")) {
    Serial.println("Webserver: http://esp32car.local");
  }

  // Setup routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);
  server.onNotFound(handleNotFound);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
