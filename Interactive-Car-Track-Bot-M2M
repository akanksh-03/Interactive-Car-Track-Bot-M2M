#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// --- WIFI CONFIGURATION ---
const char* ssid = "wifi_name";
const char* password = "wifi_password";

WebServer server(80);

// --- SERVO SETUP ---
Servo servo1;
Servo servo2;
Servo servo3;

const int servo1Pin = 13;
const int servo2Pin = 12;
const int servo3Pin = 14;

// =========================================================================
// --- GAME 1: BIO-LOCK HACK ---
// =========================================================================
const char game1_html[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Hurdle 01: BIO-LOCK HACK // Cyber-Sequence Protocol</title>
    <link
      href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700;900&family=Share+Tech+Mono&display=swap"
      rel="stylesheet"
    />
    <style>
      * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }

      :root {
        --red: #ff2d5a;
        --green: #2dff8a;
        --blue: #2db8ff;
        --yellow: #ffe02d;
        --bg-0: #02030a;
        --neon: #00ffe5;
      }

      html,
      body {
        width: 100%;
        height: 100%;
        overflow: hidden;
        background: var(--bg-0);
        color: var(--neon);
        font-family: "Share Tech Mono", monospace;
        cursor: crosshair;
      }

      #bg-canvas {
        position: fixed;
        inset: 0;
        z-index: 0;
        width: 100%;
        height: 100%;
      }

      .scanlines {
        position: fixed;
        inset: 0;
        z-index: 2;
        pointer-events: none;
        background: repeating-linear-gradient(
          to bottom,
          rgba(0, 255, 229, 0.03) 0px,
          rgba(0, 255, 229, 0.03) 1px,
          transparent 1px,
          transparent 3px
        );
        mix-blend-mode: overlay;
        animation: scan 8s linear infinite;
      }
      @keyframes scan {
        from {
          background-position-y: 0;
        }
        to {
          background-position-y: 100px;
        }
      }

      .vignette {
        position: fixed;
        inset: 0;
        z-index: 3;
        pointer-events: none;
        background: radial-gradient(
          ellipse at center,
          transparent 30%,
          rgba(0, 0, 0, 0.85) 100%
        );
      }

      .wrap {
        position: relative;
        z-index: 5;
        width: 100%;
        height: 100vh;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        padding: 20px;
      }

      .hud {
        position: absolute;
        top: 18px;
        left: 0;
        right: 0;
        display: flex;
        justify-content: space-between;
        padding: 0 28px;
        font-family: "Orbitron", sans-serif;
        font-size: 13px;
        letter-spacing: 2px;
        color: var(--neon);
        text-shadow: 0 0 6px var(--neon);
        z-index: 10;
      }
      .hud-cell {
        background: rgba(0, 255, 229, 0.05);
        border: 1px solid rgba(0, 255, 229, 0.3);
        padding: 6px 14px;
        clip-path: polygon(0 0, 100% 0, 100% 70%, 92% 100%, 0 100%);
        backdrop-filter: blur(6px);
      }
      .hud-cell .lbl {
        opacity: 0.55;
        font-size: 10px;
      }
      .hud-cell .val {
        font-weight: 900;
        font-size: 16px;
      }
      .hud-cell.right {
        clip-path: polygon(0 0, 100% 0, 100% 100%, 8% 100%, 0 70%);
      }

      .title-box {
        position: relative;
        margin-bottom: 8px;
        text-align: center;
      }
      .title-box::before,
      .title-box::after {
        content: "";
        position: absolute;
        top: 50%;
        width: 80px;
        height: 1px;
        background: linear-gradient(90deg, transparent, var(--neon));
        box-shadow: 0 0 8px var(--neon);
      }
      .title-box::before {
        right: calc(100% + 30px);
      }
      .title-box::after {
        left: calc(100% + 30px);
        transform: scaleX(-1);
      }

      .h1 {
        font-family: "Orbitron", sans-serif;
        font-weight: 900;
        font-size: 38px;
        letter-spacing: 6px;
        color: #fff;
        text-shadow:
          0 0 6px var(--neon),
          0 0 16px var(--neon),
          0 0 30px rgba(0, 255, 229, 0.4);
        animation: titleGlitch 5s infinite;
      }
      @keyframes titleGlitch {
        0%,
        92%,
        100% {
          transform: translate(0, 0);
          text-shadow:
            0 0 6px var(--neon),
            0 0 16px var(--neon),
            0 0 30px rgba(0, 255, 229, 0.4);
        }
        93% {
          transform: translate(-2px, 1px);
          text-shadow:
            -2px 0 #ff2d5a,
            2px 0 #2db8ff;
        }
        95% {
          transform: translate(2px, -1px);
          text-shadow:
            2px 0 #ff2d5a,
            -2px 0 #2db8ff;
        }
        97% {
          transform: translate(-1px, 0);
        }
      }

      .sub {
        font-family: "Share Tech Mono", monospace;
        color: #88a;
        letter-spacing: 3px;
        font-size: 12px;
        margin-top: 6px;
      }
      .blink {
        animation: blink 1s steps(2) infinite;
      }
      @keyframes blink {
        50% {
          opacity: 0;
        }
      }

      .stage {
        position: relative;
        padding: 40px;
        margin-top: 20px;
        background: radial-gradient(
          ellipse at center,
          rgba(0, 255, 229, 0.05),
          transparent 70%
        );
      }
      .stage::before {
        content: "";
        position: absolute;
        inset: 0;
        border: 1px dashed rgba(0, 255, 229, 0.25);
        pointer-events: none;
        animation: rotate 30s linear infinite;
      }
      @keyframes rotate {
        to {
          transform: rotate(360deg);
        }
      }

      .grid {
        display: grid;
        grid-template-columns: repeat(2, 130px);
        grid-template-rows: repeat(2, 130px);
        gap: 24px;
        position: relative;
      }

      .vial {
        position: relative;
        width: 130px;
        height: 130px;
        border-radius: 18px;
        cursor: pointer;
        overflow: hidden;
        border: 1px solid rgba(255, 255, 255, 0.1);
        background: linear-gradient(
          135deg,
          rgba(255, 255, 255, 0.04),
          rgba(0, 0, 0, 0.4)
        );
        box-shadow:
          inset 0 0 25px rgba(0, 0, 0, 0.7),
          inset 0 1px 0 rgba(255, 255, 255, 0.15),
          0 0 12px rgba(0, 0, 0, 0.6);
        transition: transform 0.12s ease;
      }
      .vial:hover {
        transform: translateY(-2px);
      }
      .vial:active {
        transform: scale(0.94);
      }

      .vial::before {
        content: "";
        position: absolute;
        left: 10%;
        right: 10%;
        top: 18%;
        bottom: 8%;
        border-radius: 14px;
        background: radial-gradient(
          circle at 30% 30%,
          var(--c-light) 0%,
          var(--c) 55%,
          var(--c-dark) 100%
        );
        opacity: 0.45;
        filter: blur(0.5px);
        transition:
          opacity 0.3s,
          transform 0.3s;
      }
      .vial::after {
        content: "";
        position: absolute;
        top: 8%;
        left: 18%;
        width: 22%;
        height: 30%;
        background: linear-gradient(
          135deg,
          rgba(255, 255, 255, 0.6),
          transparent 70%
        );
        border-radius: 50%;
        filter: blur(2px);
        pointer-events: none;
      }

      .vial.red {
        --c: #ff2d5a;
        --c-light: #ff7a99;
        --c-dark: #8a0020;
      }
      .vial.green {
        --c: #2dff8a;
        --c-light: #88ffbf;
        --c-dark: #006b30;
      }
      .vial.blue {
        --c: #2db8ff;
        --c-light: #82d9ff;
        --c-dark: #003a66;
      }
      .vial.yellow {
        --c: #ffe02d;
        --c-light: #fff099;
        --c-dark: #8a6e00;
      }

      .vial.active::before {
        opacity: 1;
        transform: scale(1.06);
        box-shadow:
          0 0 25px var(--c),
          0 0 50px var(--c),
          0 0 90px var(--c);
        animation: pulse 0.5s ease-out;
      }
      .vial.active {
        box-shadow:
          inset 0 0 25px rgba(255, 255, 255, 0.2),
          0 0 30px var(--c),
          0 0 60px var(--c);
        border-color: var(--c);
      }
      @keyframes pulse {
        0% {
          transform: scale(0.9);
        }
        50% {
          transform: scale(1.1);
        }
        100% {
          transform: scale(1.06);
        }
      }

      .vial-label {
        position: absolute;
        bottom: 6px;
        left: 0;
        right: 0;
        text-align: center;
        font-family: "Orbitron", sans-serif;
        font-size: 10px;
        letter-spacing: 2px;
        color: rgba(255, 255, 255, 0.6);
        text-shadow: 0 0 4px var(--c);
        pointer-events: none;
      }

      .shake {
        animation: shake 0.4s;
      }
      @keyframes shake {
        0%,
        100% {
          transform: translate(0, 0);
        }
        20% {
          transform: translate(-6px, 2px);
        }
        40% {
          transform: translate(6px, -2px);
        }
        60% {
          transform: translate(-4px, 2px);
        }
        80% {
          transform: translate(4px, -1px);
        }
      }

      .status-wrap {
        margin-top: 26px;
        text-align: center;
        min-height: 60px;
      }
      #status {
        font-family: "Orbitron", sans-serif;
        font-size: 18px;
        letter-spacing: 3px;
        color: #ccc;
        text-shadow: 0 0 6px currentColor;
        transition: color 0.3s;
      }
      #status.good {
        color: var(--green);
      }
      #status.bad {
        color: var(--red);
      }
      #status.info {
        color: var(--neon);
      }

      .progress {
        margin-top: 12px;
        width: 320px;
        height: 6px;
        background: rgba(255, 255, 255, 0.06);
        border: 1px solid rgba(0, 255, 229, 0.2);
        position: relative;
        overflow: hidden;
      }
      .progress-fill {
        position: absolute;
        left: 0;
        top: 0;
        bottom: 0;
        width: 0%;
        background: linear-gradient(90deg, var(--neon), #fff);
        box-shadow: 0 0 10px var(--neon);
        transition: width 0.4s ease;
      }

      .btn {
        margin-top: 18px;
        position: relative;
        padding: 14px 38px;
        font-family: "Orbitron", sans-serif;
        font-size: 16px;
        font-weight: 700;
        letter-spacing: 4px;
        color: var(--neon);
        background: linear-gradient(
          180deg,
          rgba(0, 255, 229, 0.08),
          rgba(0, 255, 229, 0.02)
        );
        border: 1px solid var(--neon);
        cursor: pointer;
        text-transform: uppercase;
        clip-path: polygon(8% 0, 100% 0, 92% 100%, 0 100%);
        transition: all 0.2s;
        text-shadow: 0 0 6px var(--neon);
      }
      .btn:hover {
        background: var(--neon);
        color: #000;
        box-shadow:
          0 0 25px var(--neon),
          0 0 50px var(--neon);
        text-shadow: none;
      }
      .btn:active {
        transform: scale(0.97);
      }

      .lives {
        position: absolute;
        top: 70px;
        left: 50%;
        transform: translateX(-50%);
        display: flex;
        gap: 8px;
        z-index: 10;
      }
      .heart {
        width: 18px;
        height: 18px;
        background: var(--red);
        clip-path: polygon(
          50% 100%,
          0 35%,
          0 15%,
          25% 0,
          50% 20%,
          75% 0,
          100% 15%,
          100% 35%
        );
        box-shadow: 0 0 10px var(--red);
        transition:
          opacity 0.3s,
          transform 0.3s;
      }
      .heart.lost {
        opacity: 0.15;
        transform: scale(0.7);
      }

      .particles {
        position: fixed;
        inset: 0;
        pointer-events: none;
        z-index: 4;
      }
      .particle {
        position: absolute;
        width: 6px;
        height: 6px;
        border-radius: 50%;
        pointer-events: none;
      }

      .overlay {
        position: fixed;
        inset: 0;
        background: rgba(2, 3, 10, 0.85);
        backdrop-filter: blur(8px);
        display: none;
        align-items: center;
        justify-content: center;
        z-index: 50;
        flex-direction: column;
      }
      .overlay.show {
        display: flex;
        animation: fadeIn 0.5s;
      }
      @keyframes fadeIn {
        from {
          opacity: 0;
        }
        to {
          opacity: 1;
        }
      }

      .overlay h2 {
        font-family: "Orbitron", sans-serif;
        font-size: 56px;
        letter-spacing: 8px;
        margin-bottom: 16px;
        animation: glow 2s ease-in-out infinite alternate;
      }
      .overlay h2.win {
        color: var(--green);
        text-shadow:
          0 0 20px var(--green),
          0 0 50px var(--green);
      }
      .overlay h2.lose {
        color: var(--red);
        text-shadow:
          0 0 20px var(--red),
          0 0 50px var(--red);
      }
      @keyframes glow {
        from {
          filter: brightness(1);
        }
        to {
          filter: brightness(1.4);
        }
      }

      .overlay p {
        font-family: "Share Tech Mono", monospace;
        color: #ccc;
        font-size: 18px;
        margin-bottom: 30px;
        letter-spacing: 2px;
        text-align: center;
      }

      .confetti {
        position: fixed;
        top: -10px;
        width: 10px;
        height: 14px;
        pointer-events: none;
        z-index: 60;
      }

      .mode-label {
        margin-top: 18px;
        font-family: "Share Tech Mono", monospace;
        color: #88a;
        letter-spacing: 3px;
        font-size: 11px;
        text-shadow: 0 0 4px var(--neon);
      }
      .mode-label::before,
      .mode-label::after {
        content: "▸";
        color: var(--neon);
        margin: 0 8px;
        animation: arrowPulse 1.5s ease-in-out infinite;
      }
      .mode-label::after {
        content: "◂";
        animation-delay: 0.75s;
      }
      @keyframes arrowPulse {
        0%,
        100% {
          opacity: 0.3;
        }
        50% {
          opacity: 1;
        }
      }

      .diff {
        display: flex;
        gap: 14px;
        margin-top: 10px;
        flex-wrap: wrap;
        justify-content: center;
      }
      .diff button {
        position: relative;
        width: 110px;
        padding: 14px 8px 10px;
        background: linear-gradient(
          180deg,
          rgba(0, 255, 229, 0.04),
          rgba(0, 255, 229, 0.01)
        );
        border: 1px solid rgba(0, 255, 229, 0.35);
        color: var(--neon);
        font-family: "Orbitron", sans-serif;
        cursor: pointer;
        text-transform: uppercase;
        transition: all 0.25s;
        display: flex;
        flex-direction: column;
        align-items: center;
        gap: 4px;
        clip-path: polygon(0 0, 100% 0, 100% 80%, 88% 100%, 0 100%);
        text-shadow: 0 0 4px currentColor;
      }
      .diff button::before {
        content: "";
        position: absolute;
        top: 0;
        left: 0;
        right: 0;
        height: 1px;
        background: linear-gradient(
          90deg,
          transparent,
          var(--neon),
          transparent
        );
        opacity: 0.5;
      }
      .diff button:hover {
        transform: translateY(-4px) scale(1.05);
        border-color: var(--neon);
        box-shadow:
          0 0 20px rgba(0, 255, 229, 0.5),
          0 0 40px rgba(0, 255, 229, 0.2);
        background: linear-gradient(
          180deg,
          rgba(0, 255, 229, 0.12),
          rgba(0, 255, 229, 0.03)
        );
      }
      .diff button:active {
        transform: scale(0.97);
      }
      .diff button .mode-name {
        font-size: 14px;
        font-weight: 900;
        letter-spacing: 3px;
      }
      .diff button .mode-len {
        font-size: 10px;
        letter-spacing: 2px;
        opacity: 0.75;
      }
      .diff button .mode-desc {
        font-size: 8px;
        letter-spacing: 2px;
        opacity: 0.55;
        font-family: "Share Tech Mono", monospace;
      }

      /* Difficulty-specific colors */
      .diff button.mode-easy {
        color: #2dff8a;
        border-color: rgba(45, 255, 138, 0.4);
      }
      .diff button.mode-normal {
        color: #ffe02d;
        border-color: rgba(255, 224, 45, 0.4);
      }
      .diff button.mode-hard {
        color: #ff8a2d;
        border-color: rgba(255, 138, 45, 0.4);
      }
      .diff button.mode-insane {
        color: #ff2d5a;
        border-color: rgba(255, 45, 90, 0.4);
      }
      .diff button.mode-easy:hover {
        box-shadow: 0 0 25px rgba(45, 255, 138, 0.6);
        border-color: #2dff8a;
      }
      .diff button.mode-normal:hover {
        box-shadow: 0 0 25px rgba(255, 224, 45, 0.6);
        border-color: #ffe02d;
      }
      .diff button.mode-hard:hover {
        box-shadow: 0 0 25px rgba(255, 138, 45, 0.6);
        border-color: #ff8a2d;
      }
      .diff button.mode-insane:hover {
        box-shadow: 0 0 25px rgba(255, 45, 90, 0.6);
        border-color: #ff2d5a;
      }

      .diff button.active {
        color: #000 !important;
        background: currentColor;
        box-shadow:
          0 0 25px currentColor,
          0 0 50px currentColor;
      }
      .diff button.active .mode-name,
      .diff button.active .mode-len,
      .diff button.active .mode-desc {
        color: #000;
        text-shadow: none;
        opacity: 1;
      }

      /* hide START HACK while a mode is being chosen - modes are the entry point */
      .start-btn-hidden {
        display: none !important;
      }

      .corner {
        position: fixed;
        width: 40px;
        height: 40px;
        border: 2px solid var(--neon);
        pointer-events: none;
        z-index: 6;
        opacity: 0.7;
      }
      .corner.tl {
        top: 14px;
        left: 14px;
        border-right: none;
        border-bottom: none;
      }
      .corner.tr {
        top: 14px;
        right: 14px;
        border-left: none;
        border-bottom: none;
      }
      .corner.bl {
        bottom: 14px;
        left: 14px;
        border-right: none;
        border-top: none;
      }
      .corner.br {
        bottom: 14px;
        right: 14px;
        border-left: none;
        border-top: none;
      }
    </style>
  </head>
  <body>
    <canvas id="bg-canvas"></canvas>
    <div class="scanlines"></div>
    <div class="vignette"></div>
    <div class="particles" id="particles"></div>

    <div class="corner tl"></div>
    <div class="corner tr"></div>
    <div class="corner bl"></div>
    <div class="corner br"></div>

    <div class="hud">
      <div class="hud-cell">
        <div class="lbl">SCORE</div>
        <div class="val" id="hudScore">0</div>
      </div>
      <div class="hud-cell" style="text-align: center">
        <div class="lbl">ROUND</div>
        <div class="val" id="hudRound">0/4</div>
      </div>
      <div class="hud-cell right" style="text-align: right">
        <div class="lbl">BEST</div>
        <div class="val" id="hudBest">0</div>
      </div>
    </div>

    <div class="lives" id="lives">
      <div class="heart"></div>
      <div class="heart"></div>
      <div class="heart"></div>
    </div>

    <div class="wrap">
      <div class="title-box">
        <div class="h1">HURDLE 01</div>
        <div class="sub">// BIO-LOCK HACK <span class="blink">_</span></div>
      </div>

      <div class="stage">
        <div class="grid">
          <div class="vial red" id="red" onclick="playerClick('red')">
            <div class="vial-label">P-01</div>
          </div>
          <div class="vial green" id="green" onclick="playerClick('green')">
            <div class="vial-label">P-02</div>
          </div>
          <div class="vial blue" id="blue" onclick="playerClick('blue')">
            <div class="vial-label">P-03</div>
          </div>
          <div class="vial yellow" id="yellow" onclick="playerClick('yellow')">
            <div class="vial-label">P-04</div>
          </div>
        </div>
      </div>

      <div class="status-wrap">
        <div id="status">// SELECT DIFFICULTY MODE TO INITIATE HACK //</div>
        <div class="progress">
          <div class="progress-fill" id="progressFill"></div>
        </div>
        <div class="mode-label">// CHOOSE ACCESS LEVEL //</div>
        <div class="diff" id="diffGroup">
          <button onclick="pickMode('easy', this)" class="mode-easy">
            <span class="mode-name">EASY</span>
            <span class="mode-len">SEQ · 4</span>
            <span class="mode-desc">RECRUIT</span>
          </button>
          <button onclick="pickMode('normal', this)" class="mode-normal">
            <span class="mode-name">NORMAL</span>
            <span class="mode-len">SEQ · 6</span>
            <span class="mode-desc">AGENT</span>
          </button>
          <button onclick="pickMode('hard', this)" class="mode-hard">
            <span class="mode-name">HARD</span>
            <span class="mode-len">SEQ · 8</span>
            <span class="mode-desc">OPERATIVE</span>
          </button>
          <button onclick="pickMode('insane', this)" class="mode-insane">
            <span class="mode-name">INSANE</span>
            <span class="mode-len">SEQ · 10</span>
            <span class="mode-desc">GHOST</span>
          </button>
        </div>
        <button
          class="btn start-btn-hidden"
          id="startBtn"
          onclick="startGame()"
        >
          START HACK
        </button>
      </div>
    </div>

    <div class="overlay" id="overlay">
      <h2 id="overlayTitle" class="win">SYSTEM BREACHED</h2>
      <p id="overlaySub">Gate Opened · ESP32 Signal Sent</p>
      <button
        class="btn"
        onclick="
          hideOverlay();
          resetGame();
        "
      >
        RUN AGAIN
      </button>
    </div>

    <script>
      // ============================================
      //  AUDIO ENGINE (Web Audio API - no assets)
      // ============================================
      const AudioCtx = window.AudioContext || window.webkitAudioContext;
      let audioCtx;
      function ensureAudio() {
        if (!audioCtx) audioCtx = new AudioCtx();
        if (audioCtx.state === "suspended") audioCtx.resume();
      }

      const tones = {
        red: 329.63, // E4
        green: 392.0, // G4
        blue: 523.25, // C5
        yellow: 659.25, // E5
        win: [523.25, 659.25, 783.99, 1046.5],
        lose: [220, 196, 174.6, 130.8],
        click: 880,
      };

      function playTone(freq, duration = 0.25, type = "sine", gain = 0.18) {
        try {
          ensureAudio();
          const o = audioCtx.createOscillator();
          const g = audioCtx.createGain();
          o.type = type;
          o.frequency.value = freq;
          g.gain.setValueAtTime(0, audioCtx.currentTime);
          g.gain.linearRampToValueAtTime(gain, audioCtx.currentTime + 0.01);
          g.gain.exponentialRampToValueAtTime(
            0.0001,
            audioCtx.currentTime + duration,
          );
          o.connect(g).connect(audioCtx.destination);
          o.start();
          o.stop(audioCtx.currentTime + duration);
        } catch (e) {}
      }

      function playMelody(notes, gap = 0.12) {
        notes.forEach((n, i) =>
          setTimeout(() => playTone(n, 0.3, "triangle", 0.2), i * gap * 1000),
        );
      }

      function playColor(color) {
        playTone(tones[color], 0.3, "sine", 0.2);
      }
      function playWin() {
        playMelody(tones.win);
      }
      function playLose() {
        playMelody(tones.lose, 0.18);
      }
      function playClick() {
        playTone(tones.click, 0.08, "square", 0.08);
      }

      // ============================================
      //  BACKGROUND CANVAS (cyber grid + matrix rain)
      // ============================================
      const bgCanvas = document.getElementById("bg-canvas");
      const bgCtx = bgCanvas.getContext("2d");
      let bgW, bgH;

      function resizeBG() {
        bgW = bgCanvas.width = window.innerWidth;
        bgH = bgCanvas.height = window.innerHeight;
      }
      resizeBG();
      window.addEventListener("resize", resizeBG);

      // Matrix rain
      const matrixChars =
        "アイウエオカキクケコサシスセソタチツテトナニヌネノ0123456789ABCDEF<>{}[]/";
      const fontSize = 16;
      let columns = Math.floor(window.innerWidth / fontSize);
      let drops = Array(columns)
        .fill(0)
        .map(() => Math.random() * -100);

      // Grid pulses
      const gridPulses = [];

      function drawBackground() {
        // Fading trail
        bgCtx.fillStyle = "rgba(2, 3, 10, 0.15)";
        bgCtx.fillRect(0, 0, bgW, bgH);

        // Cyber grid
        bgCtx.strokeStyle = "rgba(0, 255, 229, 0.06)";
        bgCtx.lineWidth = 1;
        const gs = 60;
        for (let x = 0; x < bgW; x += gs) {
          bgCtx.beginPath();
          bgCtx.moveTo(x, 0);
          bgCtx.lineTo(x, bgH);
          bgCtx.stroke();
        }
        for (let y = 0; y < bgH; y += gs) {
          bgCtx.beginPath();
          bgCtx.moveTo(0, y);
          bgCtx.lineTo(bgW, y);
          bgCtx.stroke();
        }

        // Grid pulses
        for (let i = gridPulses.length - 1; i >= 0; i--) {
          const p = gridPulses[i];
          p.r += 3;
          p.alpha -= 0.015;
          if (p.alpha <= 0) {
            gridPulses.splice(i, 1);
            continue;
          }
          bgCtx.beginPath();
          bgCtx.arc(p.x, p.y, p.r, 0, Math.PI * 2);
          bgCtx.strokeStyle = `rgba(0, 255, 229, ${p.alpha})`;
          bgCtx.lineWidth = 2;
          bgCtx.stroke();
        }

        // Matrix rain
        bgCtx.font = fontSize + "px monospace";
        for (let i = 0; i < drops.length; i++) {
          const text =
            matrixChars[Math.floor(Math.random() * matrixChars.length)];
          const x = i * fontSize;
          const y = drops[i] * fontSize;
          bgCtx.fillStyle = "rgba(0, 255, 229, 0.6)";
          bgCtx.fillText(text, x, y);
          bgCtx.fillStyle = "rgba(0, 255, 229, 0.15)";
          bgCtx.fillText(text, x, y - fontSize);
          if (y > bgH && Math.random() > 0.975) drops[i] = 0;
          drops[i] += 0.5;
        }
      }
      setInterval(drawBackground, 50);

      window.addEventListener("resize", () => {
        columns = Math.floor(window.innerWidth / fontSize);
        drops = Array(columns)
          .fill(0)
          .map(() => Math.random() * -100);
      });

      // ============================================
      //  PARTICLE BURSTS
      // ============================================
      const particleLayer = document.getElementById("particles");
      const colorMap = {
        red: "#ff2d5a",
        green: "#2dff8a",
        blue: "#2db8ff",
        yellow: "#ffe02d",
      };

      function spawnParticles(x, y, color, count = 24) {
        for (let i = 0; i < count; i++) {
          const p = document.createElement("div");
          p.className = "particle";
          p.style.left = x + "px";
          p.style.top = y + "px";
          p.style.background = color;
          p.style.boxShadow = `0 0 8px ${color}, 0 0 16px ${color}`;
          particleLayer.appendChild(p);

          const angle = (Math.PI * 2 * i) / count + Math.random() * 0.5;
          const speed = 80 + Math.random() * 180;
          const dx = Math.cos(angle) * speed;
          const dy = Math.sin(angle) * speed;
          const size = 4 + Math.random() * 6;

          p.style.width = size + "px";
          p.style.height = size + "px";

          const duration = 700 + Math.random() * 400;
          p.animate(
            [
              { transform: `translate(0,0) scale(1)`, opacity: 1 },
              { transform: `translate(${dx}px, ${dy}px) scale(0)`, opacity: 0 },
            ],
            { duration, easing: "cubic-bezier(.2,.7,.3,1)" },
          ).onfinish = () => p.remove();
        }
      }

      // ============================================
      //  CONFETTI
      // ============================================
      function launchConfetti() {
        const colors = [
          "#ff2d5a",
          "#2dff8a",
          "#2db8ff",
          "#ffe02d",
          "#00ffe5",
          "#fff",
        ];
        for (let i = 0; i < 80; i++) {
          const c = document.createElement("div");
          c.className = "confetti";
          c.style.left = Math.random() * 100 + "vw";
          c.style.background =
            colors[Math.floor(Math.random() * colors.length)];
          c.style.transform = `rotate(${Math.random() * 360}deg)`;
          document.body.appendChild(c);

          const duration = 2500 + Math.random() * 2000;
          const drift = (Math.random() - 0.5) * 300;
          c.animate(
            [
              { transform: `translate(0,0) rotate(0deg)`, opacity: 1 },
              {
                transform: `translate(${drift}px, ${window.innerHeight + 50}px) rotate(${720 + Math.random() * 360}deg)`,
                opacity: 0.9,
              },
            ],
            { duration, easing: "cubic-bezier(.3,.1,.7,1)" },
          ).onfinish = () => c.remove();
        }
      }

      // ============================================
      //  GAME LOGIC
      // ============================================
      const colors = ["red", "green", "blue", "yellow"];
      const colorHex = {
        red: "#ff2d5a",
        green: "#2dff8a",
        blue: "#2db8ff",
        yellow: "#ffe02d",
      };

      let sequence = [];
      let playerSequence = [];
      let isPlayerTurn = false;
      let requiredLength = 4;
      let score = 0;
      let best = parseInt(localStorage.getItem("biolock_best") || "0", 10);
      let lives = 3;
      let isPlaying = false;

      const $status = document.getElementById("status");
      const $startBtn = document.getElementById("startBtn");
      const $hudScore = document.getElementById("hudScore");
      const $hudRound = document.getElementById("hudRound");
      const $hudBest = document.getElementById("hudBest");
      const $progress = document.getElementById("progressFill");
      const $hearts = document.querySelectorAll("#lives .heart");
      const $overlay = document.getElementById("overlay");
      const $oTitle = document.getElementById("overlayTitle");
      const $oSub = document.getElementById("overlaySub");

      $hudBest.textContent = best;

      function setStatus(msg, cls = "") {
        $status.textContent = msg;
        $status.className = cls;
      }

      function setProgress(pct) {
        $progress.style.width = pct + "%";
      }

      const modeMap = {
        easy: { len: 4, speed: 0.95, label: "RECRUIT" },
        normal: { len: 6, speed: 0.85, label: "AGENT" },
        hard: { len: 8, speed: 0.7, label: "OPERATIVE" },
        insane: { len: 10, speed: 0.55, label: "GHOST" },
      };
      let currentSpeedMul = 0.95;

      // PICK A MODE: this is the entry point. Clicking a mode starts the game.
      function pickMode(level, btn) {
        if (isPlaying) return;
        ensureAudio();
        const cfg = modeMap[level];
        requiredLength = cfg.len;
        currentSpeedMul = cfg.speed;
        document
          .querySelectorAll(".diff button")
          .forEach((b) => b.classList.remove("active"));
        btn.classList.add("active");
        // dramatic flash on the selected card
        btn.animate(
          [
            { transform: "translateY(0) scale(1)" },
            { transform: "translateY(-8px) scale(1.12)" },
            { transform: "translateY(0) scale(1)" },
          ],
          { duration: 400, easing: "ease-out" },
        );
        playClick();
        // small countdown-style status then start
        setStatus(`ACCESS GRANTED :: ${cfg.label} MODE`, "info");
        setTimeout(() => startGame(), 550);
      }

      // Kept for backward compatibility (not used by UI anymore)
      function setDiff(level, btn) {
        pickMode(level, btn);
      }

      function flashColor(color, dur = 420) {
        const el = document.getElementById(color);
        el.classList.add("active");
        const rect = el.getBoundingClientRect();
        spawnParticles(
          rect.left + rect.width / 2,
          rect.top + rect.height / 2,
          colorHex[color],
          18,
        );
        setTimeout(() => el.classList.remove("active"), dur);
        playColor(color);
      }

      function startGame() {
        ensureAudio();
        sequence = [];
        score = 0;
        lives = 3;
        $hearts.forEach((h) => h.classList.remove("lost"));
        $hudScore.textContent = score;
        isPlaying = true;
        // hide mode selector and start button while playing
        $startBtn.classList.add("start-btn-hidden");
        document
          .querySelectorAll(".diff button")
          .forEach((b) => (b.disabled = true));
        document.getElementById("diffGroup").style.opacity = "0.3";
        document.getElementById("diffGroup").style.pointerEvents = "none";
        setStatus("INITIALIZING SEQUENCE...", "info");
        setTimeout(generateRound, 600);
      }

      function generateRound() {
        if (!isPlaying) return;
        playerSequence = [];
        isPlayerTurn = false;
        sequence.push(colors[Math.floor(Math.random() * 4)]);
        setStatus(
          `ROUND ${sequence.length}/${requiredLength} // MEMORIZE`,
          "info",
        );
        $hudRound.textContent = `${sequence.length}/${requiredLength}`;
        setProgress((sequence.length / requiredLength) * 100);
        playSequence();
      }

      async function playSequence() {
        await new Promise((r) => setTimeout(r, 700));
        // base speed depends on mode; shrinks further as the sequence grows
        const base = 600 * currentSpeedMul;
        const speed = Math.max(140, base - sequence.length * 25);
        for (let c of sequence) {
          flashColor(c, speed * 0.7);
          await new Promise((r) => setTimeout(r, speed));
        }
        isPlayerTurn = true;
        setStatus("YOUR TURN // INPUT SEQUENCE", "good");
      }

      function playerClick(color) {
        if (!isPlayerTurn) return;
        const el = document.getElementById(color);
        const rect = el.getBoundingClientRect();
        spawnParticles(
          rect.left + rect.width / 2,
          rect.top + rect.height / 2,
          colorHex[color],
          10,
        );
        playColor(color);
        flashColor(color, 250);
        playerSequence.push(color);
        checkPlayerInput();
      }

      function checkPlayerInput() {
        const i = playerSequence.length - 1;
        if (playerSequence[i] !== sequence[i]) {
          // WRONG
          const stageEl = document.querySelector(".stage");
          if (stageEl) stageEl.classList.add("shake");
          setTimeout(() => stageEl && stageEl.classList.remove("shake"), 400);
          lives--;
          $hearts[lives].classList.add("lost");
          setProgress((sequence.length / requiredLength) * 100);
          setStatus("ACCESS DENIED // TRACE DETECTED", "bad");
          playLose();
          if (lives <= 0) {
            isPlaying = false;
            setTimeout(() => showOverlay(false), 700);
            return;
          }
          isPlayerTurn = false;
          setTimeout(() => {
            setStatus(
              `RETRYING ROUND ${sequence.length}/${requiredLength}`,
              "info",
            );
            playSequence();
          }, 1200);
          return;
        }

        if (playerSequence.length === sequence.length) {
          score += 10 * sequence.length;
          $hudScore.textContent = score;
          if (score > best) {
            best = score;
            localStorage.setItem("biolock_best", best);
            $hudBest.textContent = best;
          }
          if (sequence.length >= requiredLength) {
            isPlaying = false;
            setStatus("HACK SUCCESSFUL // GATE OPENING", "good");
            playWin();
            setTimeout(() => showOverlay(true), 900);
            return;
          }
          isPlayerTurn = false;
          setStatus("CORRECT // NEXT STEP INCOMING", "good");
          setTimeout(generateRound, 900);
        }
      }

      function showOverlay(won) {
        if (won) {
          $oTitle.textContent = "SYSTEM BREACHED";
          $oTitle.className = "win";
          $oSub.textContent = `Gate Opened · Final Score: ${score} · ESP32 Signal Sent`;
          launchConfetti();
          gridPulses.push({ x: bgW / 2, y: bgH / 2, r: 0, alpha: 1 });
        } else {
          $oTitle.textContent = "CONNECTION LOST";
          $oTitle.className = "lose";
          $oSub.textContent = `Trace completed · Score: ${score} · Best: ${best}`;
        }
        $overlay.classList.add("show");
        sendWinSignalToESP(won);
      }

      function hideOverlay() {
        $overlay.classList.remove("show");
      }

      function resetGame() {
        sequence = [];
        playerSequence = [];
        isPlayerTurn = false;
        isPlaying = false;
        lives = 3;
        score = 0;
        $hudScore.textContent = score;
        $hudRound.textContent = `0/${requiredLength}`;
        setProgress(0);
        $hearts.forEach((h) => h.classList.remove("lost"));
        // re-enable mode selector for the next run
        $startBtn.classList.add("start-btn-hidden");
        document.querySelectorAll(".diff button").forEach((b) => {
          b.disabled = false;
          b.classList.remove("active");
        });
        const dg = document.getElementById("diffGroup");
        dg.style.opacity = "1";
        dg.style.pointerEvents = "auto";
        setStatus("// SELECT DIFFICULTY MODE TO INITIATE HACK //", "info");
      }

      // Keyboard support:
      //  - When NOT playing, 1-4 picks a difficulty mode (and starts the game)
      //  - When playing, 1-4 selects a vial
      document.addEventListener("keydown", (e) => {
        const k = String(e.key);
        if (isPlayerTurn) {
          if (k === "1") playerClick("red");
          else if (k === "2") playerClick("green");
          else if (k === "3") playerClick("blue");
          else if (k === "4") playerClick("yellow");
        } else if (!isPlaying) {
          if (k === "1") pickModeByKey("easy");
          else if (k === "2") pickModeByKey("normal");
          else if (k === "3") pickModeByKey("hard");
          else if (k === "4") pickModeByKey("insane");
        }
      });

      function pickModeByKey(level) {
        const btn = document.querySelector(`.diff button.mode-${level}`);
        if (btn) pickMode(level, btn);
      }

      function sendWinSignalToESP(won) {
        if (won) {
          console.log("Triggering Motor 1...");
          // 1. Send signal to ESP32
          fetch("/win1").catch(e => console.log(e));
          // 2. Wait 5 seconds, then load Game 2
          setTimeout(() => { window.location.href = "/game2"; }, 5000);
        }
      }

      // Init
      setStatus("// SELECT DIFFICULTY MODE TO INITIATE HACK //", "info");
    </script>
  </body>
</html>
)rawliteral";

// =========================================================================
// --- GAME 2: POWER GRID ---
// =========================================================================
const char game2_html[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Hurdle 3: Power Grid Overdrive</title>
    <style>
      /* ============================================
           ROOT & RESET
           ============================================ */
      :root {
        --cyan: #00ffff;
        --cyan-mid: #00bbcc;
        --cyan-dim: #005566;
        --cyan-glow: rgba(0, 255, 255, 0.6);
        --cyan-deep: rgba(0, 255, 255, 0.15);
        --yellow: #ffdd00;
        --yellow-glow: rgba(255, 221, 0, 0.6);
        --red: #ff2233;
        --red-bright: #ff4455;
        --red-glow: rgba(255, 34, 51, 0.7);
        --green: #00ff66;
        --green-glow: rgba(0, 255, 102, 0.6);
        --bg-primary: #020a14;
        --bg-panel: rgba(4, 12, 28, 0.92);
        --bg-tile: #060d1a;
        --border-cyan: rgba(0, 255, 255, 0.25);
        --border-dim: rgba(0, 255, 255, 0.08);
        --text-bright: #e0ffff;
        --text-dim: rgba(0, 255, 255, 0.45);
      }

      *,
      *::before,
      *::after {
        box-sizing: border-box;
        margin: 0;
        padding: 0;
      }

      body {
        background: var(--bg-primary);
        color: var(--cyan);
        font-family: "Courier New", "Consolas", monospace;
        text-align: center;
        margin: 0;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        height: 100vh;
        overflow: hidden;
        user-select: none;
      }

      /* ============================================
           BACKGROUND & ENVIRONMENT
           ============================================ */
      #bgEnvironment {
        position: fixed;
        inset: 0;
        z-index: 0;
        background:
          radial-gradient(
            ellipse at 20% 80%,
            rgba(0, 40, 80, 0.2) 0%,
            transparent 50%
          ),
          radial-gradient(
            ellipse at 80% 20%,
            rgba(0, 20, 60, 0.15) 0%,
            transparent 50%
          ),
          radial-gradient(
            ellipse at 50% 50%,
            rgba(0, 10, 25, 1) 0%,
            #010508 100%
          );
        pointer-events: none;
      }

      #bgEnvironment::before {
        content: "";
        position: absolute;
        inset: -100%;
        background:
          radial-gradient(
            ellipse at 30% 60%,
            rgba(0, 80, 120, 0.06) 0%,
            transparent 50%
          ),
          radial-gradient(
            ellipse at 70% 40%,
            rgba(0, 60, 100, 0.05) 0%,
            transparent 50%
          );
        animation: fogDrift1 25s ease-in-out infinite;
      }

      #bgEnvironment::after {
        content: "";
        position: absolute;
        inset: -100%;
        background:
          radial-gradient(
            ellipse at 60% 30%,
            rgba(0, 50, 80, 0.05) 0%,
            transparent 45%
          ),
          radial-gradient(
            ellipse at 40% 70%,
            rgba(0, 40, 70, 0.04) 0%,
            transparent 45%
          );
        animation: fogDrift2 30s ease-in-out infinite;
      }

      @keyframes fogDrift1 {
        0%,
        100% {
          transform: translate(0, 0) rotate(0deg);
        }
        33% {
          transform: translate(3%, -2%) rotate(1deg);
        }
        66% {
          transform: translate(-2%, 3%) rotate(-1deg);
        }
      }

      @keyframes fogDrift2 {
        0%,
        100% {
          transform: translate(0, 0) rotate(0deg);
        }
        33% {
          transform: translate(-4%, 2%) rotate(-0.5deg);
        }
        66% {
          transform: translate(2%, -3%) rotate(0.5deg);
        }
      }

      .grid-bg-overlay {
        position: fixed;
        inset: 0;
        z-index: 0;
        background-image:
          linear-gradient(rgba(0, 255, 255, 0.02) 1px, transparent 1px),
          linear-gradient(90deg, rgba(0, 255, 255, 0.02) 1px, transparent 1px);
        background-size: 60px 60px;
        animation: gridScroll 40s linear infinite;
        pointer-events: none;
      }

      @keyframes gridScroll {
        0% {
          transform: translateY(0);
        }
        100% {
          transform: translateY(60px);
        }
      }

      /* ============================================
           PARTICLE CANVAS
           ============================================ */
      #particleCanvas {
        position: fixed;
        inset: 0;
        z-index: 1;
        pointer-events: none;
      }

      /* ============================================
           SCANLINES & VIGNETTE
           ============================================ */
      .scanlines {
        position: fixed;
        inset: 0;
        z-index: 50;
        pointer-events: none;
        background: repeating-linear-gradient(
          0deg,
          transparent,
          transparent 2px,
          rgba(0, 0, 0, 0.06) 2px,
          rgba(0, 0, 0, 0.06) 4px
        );
        opacity: 0.7;
      }

      .vignette {
        position: fixed;
        inset: 0;
        z-index: 49;
        pointer-events: none;
        background: radial-gradient(
          ellipse at center,
          transparent 40%,
          rgba(0, 0, 0, 0.6) 100%
        );
      }

      /* ============================================
           SCREEN FLASH & EFFECTS
           ============================================ */
      #screenFlash {
        position: fixed;
        inset: 0;
        z-index: 60;
        pointer-events: none;
        opacity: 0;
        transition: opacity 0.15s ease-out;
      }

      #warningOverlay {
        position: fixed;
        inset: 0;
        z-index: 55;
        pointer-events: none;
        display: none;
        align-items: center;
        justify-content: center;
        background: rgba(255, 0, 0, 0.15);
      }

      #warningOverlay.active {
        display: flex;
        animation: warningFlash 0.3s ease-in-out infinite alternate;
      }

      #warningOverlay .warning-text {
        font-size: 48px;
        font-weight: bold;
        color: var(--red);
        text-shadow:
          0 0 30px var(--red-glow),
          0 0 60px var(--red-glow);
        letter-spacing: 8px;
        animation: warningPulse 0.5s ease-in-out infinite alternate;
      }

      @keyframes warningFlash {
        0% {
          background: rgba(255, 0, 0, 0.05);
        }
        100% {
          background: rgba(255, 0, 0, 0.2);
        }
      }

      @keyframes warningPulse {
        0% {
          opacity: 0.7;
          transform: scale(1);
        }
        100% {
          opacity: 1;
          transform: scale(1.05);
        }
      }

      /* ============================================
           GAME CONTAINER
           ============================================ */
      .game-container {
        position: relative;
        z-index: 10;
        display: flex;
        flex-direction: column;
        align-items: center;
        gap: 12px;
        padding: 10px;
        will-change: transform;
      }

      .game-container.shaking {
        animation: screenShake 0.08s linear infinite;
      }

      @keyframes screenShake {
        0% {
          transform: translate(0, 0);
        }
        25% {
          transform: translate(-3px, 2px);
        }
        50% {
          transform: translate(2px, -3px);
        }
        75% {
          transform: translate(-1px, 1px);
        }
        100% {
          transform: translate(3px, -1px);
        }
      }

      /* ============================================
           TITLE SECTION
           ============================================ */
      .title-section {
        text-align: center;
        margin-bottom: 2px;
      }

      .title-section h1 {
        font-size: 28px;
        font-weight: bold;
        color: var(--yellow);
        text-shadow:
          0 0 10px var(--yellow-glow),
          0 0 30px rgba(255, 221, 0, 0.3),
          0 0 60px rgba(255, 221, 0, 0.15);
        letter-spacing: 4px;
        margin-bottom: 4px;
        animation: titleFlicker 4s ease-in-out infinite;
        position: relative;
      }

      .title-section h1::after {
        content: "";
        position: absolute;
        bottom: -2px;
        left: 10%;
        right: 10%;
        height: 1px;
        background: linear-gradient(
          90deg,
          transparent,
          var(--yellow),
          transparent
        );
        opacity: 0.5;
      }

      .title-section .subtitle {
        font-size: 11px;
        color: var(--text-dim);
        letter-spacing: 2px;
        text-transform: uppercase;
      }

      @keyframes titleFlicker {
        0%,
        100% {
          opacity: 1;
        }
        92% {
          opacity: 1;
        }
        93% {
          opacity: 0.7;
        }
        94% {
          opacity: 1;
        }
        96% {
          opacity: 0.85;
        }
        97% {
          opacity: 1;
        }
      }

      /* ============================================
           TIMER SECTION
           ============================================ */
      .timer-section {
        position: relative;
        margin-bottom: 4px;
      }

      .timer-label {
        font-size: 9px;
        letter-spacing: 3px;
        color: var(--text-dim);
        text-transform: uppercase;
        margin-bottom: 2px;
      }

      .timer-display {
        font-size: 36px;
        font-weight: bold;
        color: var(--cyan);
        text-shadow: 0 0 15px var(--cyan-glow);
        letter-spacing: 4px;
        padding: 6px 24px;
        background: var(--bg-panel);
        border: 1px solid var(--border-cyan);
        border-radius: 6px;
        position: relative;
        overflow: hidden;
        transition:
          color 0.3s,
          text-shadow 0.3s;
      }

      .timer-display::before {
        content: "";
        position: absolute;
        inset: 0;
        background: linear-gradient(
          180deg,
          rgba(0, 255, 255, 0.03) 0%,
          transparent 100%
        );
        pointer-events: none;
      }

      .timer-display::after {
        content: "";
        position: absolute;
        top: 0;
        left: -100%;
        width: 100%;
        height: 100%;
        background: linear-gradient(
          90deg,
          transparent,
          rgba(0, 255, 255, 0.05),
          transparent
        );
        animation: timerSheen 3s ease-in-out infinite;
      }

      @keyframes timerSheen {
        0% {
          left: -100%;
        }
        50% {
          left: 100%;
        }
        100% {
          left: 100%;
        }
      }

      /* Timer states */
      .timer-display.warning {
        color: var(--yellow);
        text-shadow:
          0 0 15px var(--yellow-glow),
          0 0 30px rgba(255, 221, 0, 0.3);
        animation: timerPulseYellow 0.8s ease-in-out infinite;
      }

      .timer-display.danger {
        color: var(--red);
        text-shadow:
          0 0 15px var(--red-glow),
          0 0 30px rgba(255, 34, 51, 0.4);
        animation: timerFlashRed 0.4s ease-in-out infinite;
      }

      .timer-display.critical {
        color: var(--red-bright);
        text-shadow:
          0 0 20px var(--red-glow),
          0 0 40px rgba(255, 34, 51, 0.6);
        animation: timerFlashCritical 0.2s ease-in-out infinite;
      }

      .timer-display.emergency {
        color: #ff0011;
        text-shadow: 0 0 30px rgba(255, 0, 17, 0.8);
        animation: emergencyShutdown 0.15s linear infinite;
      }

      @keyframes timerPulseYellow {
        0%,
        100% {
          opacity: 1;
        }
        50% {
          opacity: 0.6;
        }
      }

      @keyframes timerFlashRed {
        0%,
        100% {
          opacity: 1;
        }
        50% {
          opacity: 0.5;
        }
      }

      @keyframes timerFlashCritical {
        0%,
        100% {
          opacity: 1;
          transform: scale(1);
        }
        50% {
          opacity: 0.4;
          transform: scale(1.03);
        }
      }

      @keyframes emergencyShutdown {
        0%,
        100% {
          opacity: 1;
        }
        50% {
          opacity: 0.2;
        }
      }

      /* ============================================
           GAME AREA (Power Source | Grid | Door)
           ============================================ */
      .game-area {
        display: flex;
        align-items: center;
        gap: 16px;
      }

      /* ============================================
           POWER SOURCE (Reactor)
           ============================================ */
      .power-source-panel {
        width: 110px;
        display: flex;
        flex-direction: column;
        align-items: center;
        gap: 8px;
      }

      .reactor {
        width: 100px;
        height: 100px;
        position: relative;
        display: flex;
        align-items: center;
        justify-content: center;
      }

      .reactor-outer-ring {
        position: absolute;
        width: 90px;
        height: 90px;
        border: 2px solid rgba(255, 221, 0, 0.4);
        border-radius: 50%;
        border-top-color: var(--yellow);
        border-right-color: var(--yellow);
        animation: rotateReactorCW 4s linear infinite;
        box-shadow:
          0 0 15px rgba(255, 221, 0, 0.2),
          inset 0 0 15px rgba(255, 221, 0, 0.1);
      }

      .reactor-inner-ring {
        position: absolute;
        width: 64px;
        height: 64px;
        border: 2px solid rgba(0, 255, 255, 0.3);
        border-radius: 50%;
        border-bottom-color: var(--cyan);
        border-left-color: var(--cyan);
        animation: rotateReactorCCW 2.5s linear infinite;
        box-shadow:
          0 0 10px rgba(0, 255, 255, 0.15),
          inset 0 0 10px rgba(0, 255, 255, 0.1);
      }

      .reactor-core {
        position: absolute;
        width: 30px;
        height: 30px;
        background: radial-gradient(
          circle,
          #ffee88 0%,
          var(--yellow) 40%,
          rgba(255, 200, 0, 0.4) 70%,
          transparent 100%
        );
        border-radius: 50%;
        animation: corePulse 2s ease-in-out infinite;
        box-shadow:
          0 0 20px var(--yellow-glow),
          0 0 40px rgba(255, 221, 0, 0.3);
      }

      .reactor-energy-wave {
        position: absolute;
        width: 30px;
        height: 30px;
        border: 1px solid rgba(255, 221, 0, 0.3);
        border-radius: 50%;
        animation: energyWave 2.5s ease-out infinite;
      }

      .reactor-energy-wave:nth-child(2) {
        animation-delay: 0.8s;
      }

      .reactor-energy-wave:nth-child(3) {
        animation-delay: 1.6s;
      }

      .reactor-spark {
        position: absolute;
        width: 2px;
        height: 2px;
        background: var(--yellow);
        border-radius: 50%;
        box-shadow: 0 0 4px var(--yellow);
      }

      .reactor-spark:nth-child(5) {
        animation: sparkOrbit1 3s linear infinite;
      }
      .reactor-spark:nth-child(6) {
        animation: sparkOrbit2 2.2s linear infinite;
      }
      .reactor-spark:nth-child(7) {
        animation: sparkOrbit3 3.5s linear infinite;
      }

      @keyframes rotateReactorCW {
        from {
          transform: rotate(0deg);
        }
        to {
          transform: rotate(360deg);
        }
      }

      @keyframes rotateReactorCCW {
        from {
          transform: rotate(0deg);
        }
        to {
          transform: rotate(-360deg);
        }
      }

      @keyframes corePulse {
        0%,
        100% {
          transform: scale(1);
          opacity: 0.9;
        }
        50% {
          transform: scale(1.15);
          opacity: 1;
        }
      }

      @keyframes energyWave {
        0% {
          transform: scale(1);
          opacity: 0.6;
        }
        100% {
          transform: scale(3.5);
          opacity: 0;
        }
      }

      @keyframes sparkOrbit1 {
        0% {
          transform: rotate(0deg) translateX(38px) rotate(0deg);
          opacity: 1;
        }
        100% {
          transform: rotate(360deg) translateX(38px) rotate(-360deg);
          opacity: 1;
        }
      }

      @keyframes sparkOrbit2 {
        0% {
          transform: rotate(120deg) translateX(32px) rotate(-120deg);
          opacity: 0.8;
        }
        100% {
          transform: rotate(480deg) translateX(32px) rotate(-480deg);
          opacity: 0.8;
        }
      }

      @keyframes sparkOrbit3 {
        0% {
          transform: rotate(240deg) translateX(42px) rotate(-240deg);
          opacity: 0.6;
        }
        100% {
          transform: rotate(600deg) translateX(42px) rotate(-600deg);
          opacity: 0.6;
        }
      }

      .power-source-label {
        font-size: 10px;
        font-weight: bold;
        letter-spacing: 2px;
        color: var(--yellow);
        text-shadow: 0 0 8px var(--yellow-glow);
        text-transform: uppercase;
      }

      .power-source-sublabel {
        font-size: 8px;
        color: var(--text-dim);
        letter-spacing: 1px;
      }

      /* ============================================
           GRID PANEL
           ============================================ */
      .grid-panel {
        background: var(--bg-panel);
        border: 1px solid var(--border-cyan);
        border-radius: 10px;
        padding: 10px;
        position: relative;
        overflow: hidden;
        box-shadow:
          0 0 40px rgba(0, 255, 255, 0.05),
          inset 0 0 60px rgba(0, 0, 0, 0.4);
      }

      .grid-panel::before {
        content: "";
        position: absolute;
        inset: 0;
        background: linear-gradient(
          135deg,
          rgba(0, 255, 255, 0.03) 0%,
          transparent 50%,
          rgba(0, 255, 255, 0.01) 100%
        );
        pointer-events: none;
      }

      .grid-panel::after {
        content: "";
        position: absolute;
        top: -1px;
        left: 20%;
        right: 20%;
        height: 1px;
        background: linear-gradient(
          90deg,
          transparent,
          rgba(0, 255, 255, 0.4),
          transparent
        );
        pointer-events: none;
      }

      .panel-header {
        font-size: 8px;
        letter-spacing: 3px;
        color: var(--text-dim);
        text-transform: uppercase;
        margin-bottom: 8px;
        padding-bottom: 4px;
        border-bottom: 1px solid var(--border-dim);
      }

      .panel-footer {
        font-size: 8px;
        letter-spacing: 2px;
        color: var(--cyan-dim);
        text-transform: uppercase;
        margin-top: 8px;
        padding-top: 4px;
        border-top: 1px solid var(--border-dim);
        display: flex;
        align-items: center;
        justify-content: center;
        gap: 6px;
      }

      .status-dot {
        width: 5px;
        height: 5px;
        border-radius: 50%;
        background: var(--cyan);
        box-shadow: 0 0 6px var(--cyan-glow);
        animation: statusBlink 2s ease-in-out infinite;
      }

      @keyframes statusBlink {
        0%,
        100% {
          opacity: 1;
        }
        50% {
          opacity: 0.3;
        }
      }

      #grid {
        display: grid;
        grid-template-columns: repeat(4, 80px);
        grid-template-rows: repeat(3, 80px);
        gap: 4px;
      }

      /* ============================================
           PIPE TILES
           ============================================ */
      .tile {
        width: 80px;
        height: 80px;
        background: var(--bg-tile);
        cursor: pointer;
        display: flex;
        align-items: center;
        justify-content: center;
        position: relative;
        border-radius: 6px;
        border: 1px solid rgba(0, 255, 255, 0.1);
        transition:
          border-color 0.2s,
          box-shadow 0.3s,
          background 0.2s;
        overflow: hidden;
        will-change: transform;
      }

      .tile::before {
        content: "";
        position: absolute;
        inset: 0;
        background: linear-gradient(
          135deg,
          rgba(0, 255, 255, 0.04) 0%,
          transparent 60%
        );
        pointer-events: none;
        border-radius: 5px;
      }

      .tile::after {
        content: "";
        position: absolute;
        inset: 0;
        border-radius: 5px;
        box-shadow: inset 0 0 20px rgba(0, 0, 0, 0.5);
        pointer-events: none;
      }

      .tile:hover {
        border-color: rgba(0, 255, 255, 0.35);
        background: #0a1525;
        box-shadow: 0 0 15px rgba(0, 255, 255, 0.1);
      }

      .tile:active {
        transform: scale(0.95) !important;
      }

      .tile svg {
        width: 100%;
        height: 100%;
        transition: transform 0.25s cubic-bezier(0.34, 1.56, 0.64, 1);
        filter: drop-shadow(0 0 4px rgba(0, 255, 255, 0.3));
      }

      .tile:hover svg {
        filter: drop-shadow(0 0 8px rgba(0, 255, 255, 0.5));
      }

      /* Tile click ripple */
      .tile .click-ripple {
        position: absolute;
        width: 100%;
        height: 100%;
        border-radius: 6px;
        background: radial-gradient(
          circle,
          rgba(0, 255, 255, 0.3) 0%,
          transparent 70%
        );
        opacity: 0;
        pointer-events: none;
        animation: clickRipple 0.4s ease-out forwards;
      }

      @keyframes clickRipple {
        0% {
          opacity: 1;
          transform: scale(0.5);
        }
        100% {
          opacity: 0;
          transform: scale(1.5);
        }
      }

      /* Energy flow animation on correct path tiles */
      .tile.energy-active {
        border-color: rgba(0, 255, 255, 0.6);
        box-shadow:
          0 0 20px rgba(0, 255, 255, 0.4),
          inset 0 0 15px rgba(0, 255, 255, 0.1);
      }

      .tile.energy-active svg {
        filter: drop-shadow(0 0 12px rgba(0, 255, 255, 0.7));
      }

      .tile.energy-active svg rect:nth-child(4) {
        fill: #88ffff;
      }

      .tile.energy-active svg rect:nth-child(5) {
        fill: #ffffff;
        opacity: 0.95;
      }

      /* ============================================
           DOOR TERMINAL
           ============================================ */
      .door-panel {
        width: 110px;
        display: flex;
        flex-direction: column;
        align-items: center;
        gap: 6px;
      }

      .door-terminal {
        width: 100px;
        height: 110px;
        background: var(--bg-panel);
        border: 2px solid rgba(255, 34, 51, 0.4);
        border-radius: 8px;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        position: relative;
        overflow: hidden;
        transition:
          border-color 0.5s,
          box-shadow 0.5s;
        box-shadow:
          0 0 15px rgba(255, 34, 51, 0.15),
          inset 0 0 20px rgba(0, 0, 0, 0.4);
      }

      .door-terminal::before {
        content: "";
        position: absolute;
        top: 0;
        left: 0;
        right: 0;
        height: 3px;
        background: var(--red);
        opacity: 0.6;
        animation: doorFlicker 2s ease-in-out infinite;
      }

      .door-terminal.powered {
        border-color: rgba(0, 255, 102, 0.5);
        box-shadow:
          0 0 25px rgba(0, 255, 102, 0.2),
          inset 0 0 20px rgba(0, 0, 0, 0.3);
      }

      .door-terminal.powered::before {
        background: var(--green);
        animation: doorScanLine 2s linear infinite;
      }

      @keyframes doorFlicker {
        0%,
        100% {
          opacity: 0.6;
        }
        50% {
          opacity: 0.3;
        }
        52% {
          opacity: 0.8;
        }
        54% {
          opacity: 0.4;
        }
      }

      @keyframes doorScanLine {
        0% {
          top: 0;
        }
        100% {
          top: 100%;
        }
      }

      .door-screen {
        width: 70px;
        height: 50px;
        background: rgba(255, 0, 0, 0.05);
        border: 1px solid rgba(255, 34, 51, 0.2);
        border-radius: 3px;
        display: flex;
        align-items: center;
        justify-content: center;
        position: relative;
        overflow: hidden;
        transition:
          background 0.5s,
          border-color 0.5s;
      }

      .door-terminal.powered .door-screen {
        background: rgba(0, 255, 102, 0.08);
        border-color: rgba(0, 255, 102, 0.3);
      }

      .door-status {
        font-size: 12px;
        font-weight: bold;
        letter-spacing: 2px;
        line-height: 1.4;
        color: var(--red);
        text-shadow: 0 0 8px var(--red-glow);
        transition:
          color 0.5s,
          text-shadow 0.5s;
        z-index: 1;
      }

      .door-terminal.powered .door-status {
        color: var(--green);
        text-shadow: 0 0 10px var(--green-glow);
      }

      .door-indicator {
        width: 60px;
        height: 3px;
        background: rgba(255, 34, 51, 0.3);
        border-radius: 2px;
        margin-top: 6px;
        overflow: hidden;
        position: relative;
      }

      .door-indicator::after {
        content: "";
        position: absolute;
        left: -20px;
        top: 0;
        width: 20px;
        height: 100%;
        background: var(--red);
        border-radius: 2px;
        animation: indicatorSweep 1.5s ease-in-out infinite;
      }

      .door-terminal.powered .door-indicator {
        background: rgba(0, 255, 102, 0.3);
      }

      .door-terminal.powered .door-indicator::after {
        background: var(--green);
        animation: indicatorSweepGreen 1s linear infinite;
      }

      @keyframes indicatorSweep {
        0% {
          left: -20px;
          opacity: 0.5;
        }
        50% {
          left: 60px;
          opacity: 1;
        }
        100% {
          left: 60px;
          opacity: 0.5;
        }
      }

      @keyframes indicatorSweepGreen {
        0% {
          left: -20px;
        }
        100% {
          left: 60px;
        }
      }

      .door-label {
        font-size: 8px;
        letter-spacing: 2px;
        color: var(--text-dim);
        text-transform: uppercase;
        text-align: center;
        line-height: 1.4;
      }

      /* ============================================
           OVERLAY & UI
           ============================================ */
      #overlay {
        position: fixed;
        inset: 0;
        z-index: 40;
        background: rgba(0, 5, 15, 0.88);
        display: flex;
        align-items: center;
        justify-content: center;
        flex-direction: column;
        gap: 20px;
        backdrop-filter: blur(4px);
      }

      #endMessage {
        display: none;
        font-size: 36px;
        font-weight: bold;
        letter-spacing: 3px;
        line-height: 1.4;
        max-width: 600px;
        text-align: center;
      }

      #startBtn {
        padding: 14px 36px;
        font-size: 16px;
        font-family: "Courier New", monospace;
        font-weight: bold;
        letter-spacing: 3px;
        text-transform: uppercase;
        background: transparent;
        color: var(--yellow);
        border: 2px solid var(--yellow);
        cursor: pointer;
        position: relative;
        overflow: hidden;
        transition: all 0.3s ease;
        border-radius: 4px;
      }

      #startBtn::before {
        content: "";
        position: absolute;
        inset: 0;
        background: linear-gradient(
          135deg,
          rgba(255, 221, 0, 0.1) 0%,
          transparent 100%
        );
        opacity: 0;
        transition: opacity 0.3s;
      }

      #startBtn:hover {
        background: rgba(255, 221, 0, 0.15);
        box-shadow:
          0 0 25px rgba(255, 221, 0, 0.2),
          inset 0 0 25px rgba(255, 221, 0, 0.05);
        text-shadow: 0 0 10px var(--yellow-glow);
      }

      #startBtn:hover::before {
        opacity: 1;
      }

      #startBtn:active {
        transform: scale(0.97);
      }

      /* Success message styling */
      .msg-success {
        color: var(--green) !important;
        text-shadow:
          0 0 20px var(--green-glow),
          0 0 40px rgba(0, 255, 102, 0.3);
      }

      /* Failure message styling */
      .msg-failure {
        color: var(--red) !important;
        text-shadow:
          0 0 20px var(--red-glow),
          0 0 40px rgba(255, 34, 51, 0.3);
        animation: msgGlitch 0.1s linear 3;
      }

      @keyframes msgGlitch {
        0% {
          transform: translate(0);
        }
        25% {
          transform: translate(-3px, 1px);
        }
        50% {
          transform: translate(2px, -2px);
        }
        75% {
          transform: translate(-1px, 2px);
        }
        100% {
          transform: translate(0);
        }
      }

      /* ============================================
           ACCESS GRANTED TYPING EFFECT
           ============================================ */
      .access-text {
        display: inline-block;
        overflow: hidden;
        white-space: nowrap;
        border-right: 2px solid var(--green);
        animation: typingCursor 0.6s step-end infinite;
      }

      @keyframes typingCursor {
        0%,
        100% {
          border-color: var(--green);
        }
        50% {
          border-color: transparent;
        }
      }

      /* ============================================
           VICTORY ENERGY BURST
           ============================================ */
      .energy-burst {
        position: fixed;
        top: 50%;
        left: 50%;
        width: 10px;
        height: 10px;
        background: radial-gradient(
          circle,
          rgba(0, 255, 255, 0.8) 0%,
          transparent 70%
        );
        border-radius: 50%;
        z-index: 35;
        pointer-events: none;
        animation: energyBurst 0.8s ease-out forwards;
      }

      @keyframes energyBurst {
        0% {
          transform: translate(-50%, -50%) scale(1);
          opacity: 1;
        }
        100% {
          transform: translate(-50%, -50%) scale(80);
          opacity: 0;
        }
      }

      /* ============================================
           FAIL SCREEN OVERLAY
           ============================================ */
      .fail-overlay {
        position: fixed;
        inset: 0;
        z-index: 38;
        background: rgba(80, 0, 0, 0.4);
        display: none;
        pointer-events: none;
        animation: failOverlayPulse 0.5s ease-in-out 3;
      }

      .fail-overlay.active {
        display: block;
      }

      @keyframes failOverlayPulse {
        0%,
        100% {
          opacity: 0;
        }
        50% {
          opacity: 1;
        }
      }

      /* ============================================
           HUD BOTTOM BAR
           ============================================ */
      .hud-bar {
        display: flex;
        justify-content: center;
        gap: 30px;
        margin-top: 4px;
        font-size: 9px;
        letter-spacing: 2px;
        color: var(--text-dim);
        text-transform: uppercase;
      }

      .hud-item {
        display: flex;
        align-items: center;
        gap: 5px;
      }

      .hud-dot {
        width: 4px;
        height: 4px;
        border-radius: 50%;
        background: var(--cyan-dim);
      }
    </style>
  </head>
  <body>
    <div id="bgEnvironment"></div>
    <div class="grid-bg-overlay"></div>
    <canvas id="particleCanvas"></canvas>
    <div class="scanlines"></div>
    <div class="vignette"></div>

    <div id="screenFlash"></div>
    <div id="warningOverlay">
      <span class="warning-text">⚠ BREACH DETECTED ⚠</span>
    </div>
    <div class="fail-overlay" id="failOverlay"></div>

    <div class="game-container" id="gameContainer">
      <div class="title-section">
        <h1>HURDLE 03: POWER GRID</h1>
        <div class="subtitle">
          Reroute power to the door motor before the system is compromised
        </div>
      </div>

      <div class="timer-section">
        <div class="timer-label">Time Remaining</div>
        <div class="timer-display" id="timer">00:20</div>
      </div>

      <div class="game-area">
        <div class="power-source-panel">
          <div class="reactor" id="reactor">
            <div class="reactor-energy-wave"></div>
            <div class="reactor-energy-wave"></div>
            <div class="reactor-energy-wave"></div>
            <div class="reactor-spark"></div>
            <div class="reactor-spark"></div>
            <div class="reactor-spark"></div>
            <div class="reactor-outer-ring"></div>
            <div class="reactor-inner-ring"></div>
            <div class="reactor-core"></div>
          </div>
          <div class="power-source-label">POWER<br />SOURCE</div>
          <div class="power-source-sublabel">REACTOR</div>
        </div>

        <div class="grid-panel">
          <div class="panel-header">⟐ Power Routing Console ⟐</div>
          <div id="grid">
            </div>
          <div class="panel-footer">
            <span class="status-dot"></span>
            <span id="sysStatus">SYS.STATUS: ACTIVE</span>
          </div>
        </div>

        <div class="door-panel">
          <div class="door-terminal" id="doorMotor">
            <div class="door-screen">
              <div class="door-status" id="doorStatusText">DOOR<br />OFF</div>
            </div>
            <div class="door-indicator"></div>
          </div>
          <div class="door-label">ACCESS<br />PORT</div>
        </div>
      </div>

      <div class="hud-bar">
        <div class="hud-item"><span class="hud-dot"></span>GRID ONLINE</div>
        <div class="hud-item"><span class="hud-dot"></span>SECTOR 7-G</div>
        <div class="hud-item">
          <span class="hud-dot"></span>SECURITY: LEVEL 4
        </div>
      </div>
    </div>

    <div id="overlay">
      <h2 id="endMessage"></h2>
      <button id="startBtn" onclick="startGame()">
        INITIATE POWER ROUTING
      </button>
    </div>

    <script>
      // ============================================
      // SVG DRAWINGS (Upgraded futuristic pipes)
      // ============================================
      const svgStraight = `<svg viewBox="0 0 100 100" xmlns="http://www.w3.org/2000/svg">
            <rect x="34" y="-2" width="32" height="104" rx="4" fill="#060d1a" stroke="#0d3040" stroke-width="1.5"/>
            <rect x="38" y="0" width="24" height="100" rx="3" fill="#001520"/>
            <rect x="42" y="0" width="16" height="100" rx="2" fill="#00ccff" opacity="0.18"/>
            <rect x="46" y="0" width="8" height="100" rx="1" fill="#00ffff" opacity="0.45"/>
            <rect x="48.5" y="0" width="3" height="100" fill="#88ffff" opacity="0.85"/>
        </svg>`;

      const svgCorner = `<svg viewBox="0 0 100 100" xmlns="http://www.w3.org/2000/svg">
            <rect x="34" y="-2" width="32" height="66" rx="4" fill="#060d1a" stroke="#0d3040" stroke-width="1.5"/>
            <rect x="38" y="0" width="24" height="62" rx="3" fill="#001520"/>
            <rect x="42" y="0" width="16" height="62" rx="2" fill="#00ccff" opacity="0.18"/>
            <rect x="46" y="0" width="8" height="62" rx="1" fill="#00ffff" opacity="0.45"/>
            <rect x="48.5" y="0" width="3" height="62" fill="#88ffff" opacity="0.85"/>
            <rect x="34" y="34" width="68" height="32" rx="4" fill="#060d1a" stroke="#0d3040" stroke-width="1.5"/>
            <rect x="38" y="38" width="62" height="24" rx="3" fill="#001520"/>
            <rect x="38" y="42" width="62" height="16" rx="2" fill="#00ccff" opacity="0.18"/>
            <rect x="38" y="46" width="62" height="8" rx="1" fill="#00ffff" opacity="0.45"/>
            <rect x="38" y="48.5" width="62" height="3" fill="#88ffff" opacity="0.85"/>
        </svg>`;

      // ============================================
      // LEVEL DATA (Preserved exactly from original)
      // ============================================
      const levelData = [
        { type: "corner", correct: [], isPath: false },
        { type: "corner", correct: [90], isPath: true },
        { type: "corner", correct: [180], isPath: true },
        { type: "straight", correct: [], isPath: false },
        { type: "straight", correct: [90, 270], isPath: true },
        { type: "corner", correct: [270], isPath: true },
        { type: "straight", correct: [0, 180], isPath: true },
        { type: "corner", correct: [90], isPath: true },
        { type: "corner", correct: [], isPath: false },
        { type: "straight", correct: [], isPath: false },
        { type: "corner", correct: [0], isPath: true },
        { type: "corner", correct: [270], isPath: true },
      ];

      // Energy flow path order (power source → door)
      const pathOrder = [4, 5, 1, 2, 6, 10, 11, 7];

      // ============================================
      // GAME STATE
      // ============================================
      let timeLeft = 20;
      let timerInterval;
      let isGameRunning = false;
      let tileElements = [];

      // ============================================
      // PARTICLE SYSTEM
      // ============================================
      const canvas = document.getElementById("particleCanvas");
      const ctx = canvas.getContext("2d");
      let particles = [];
      const PARTICLE_COUNT = 60;

      function resizeCanvas() {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
      }
      resizeCanvas();
      window.addEventListener("resize", resizeCanvas);

      class Particle {
        constructor() {
          this.reset(true);
        }

        reset(initial = false) {
          this.x = Math.random() * canvas.width;
          this.y = initial ? Math.random() * canvas.height : canvas.height + 10;
          this.isSpark = Math.random() > 0.82;

          if (this.isSpark) {
            this.size = Math.random() * 1.5 + 0.5;
            this.speedX = (Math.random() - 0.5) * 2;
            this.speedY = -(Math.random() * 3 + 1);
            this.life = Math.random() * 40 + 20;
            this.maxLife = this.life;
            this.r = 0;
            this.g = 200 + Math.random() * 55;
            this.b = 255;
          } else {
            this.size = Math.random() * 2 + 0.3;
            this.speedX = (Math.random() - 0.5) * 0.3;
            this.speedY = -(Math.random() * 0.3 + 0.05);
            this.life = Math.random() * 300 + 150;
            this.maxLife = this.life;
            const tone = Math.random();
            this.r = 20 + tone * 40;
            this.g = 60 + tone * 80;
            this.b = 100 + tone * 100;
          }
        }

        update() {
          this.x += this.speedX;
          this.y += this.speedY;
          this.life--;

          if (this.isSpark) {
            this.speedY += 0.04;
            this.opacity = (this.life / this.maxLife) * 0.9;
          } else {
            this.opacity =
              Math.sin((this.life / this.maxLife) * Math.PI) * 0.35;
          }

          if (
            this.life <= 0 ||
            this.x < -10 ||
            this.x > canvas.width + 10 ||
            this.y < -10 ||
            this.y > canvas.height + 10
          ) {
            this.reset();
          }
        }

        draw() {
          ctx.globalAlpha = this.opacity;
          ctx.fillStyle = `rgb(${this.r},${this.g},${this.b})`;
          ctx.beginPath();
          ctx.arc(this.x, this.y, this.size, 0, Math.PI * 2);
          ctx.fill();

          if (this.isSpark) {
            ctx.globalAlpha = this.opacity * 0.3;
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.size * 3, 0, Math.PI * 2);
            ctx.fill();
          }
        }
      }

      function initParticles() {
        particles = [];
        for (let i = 0; i < PARTICLE_COUNT; i++) {
          particles.push(new Particle());
        }
      }

      function animateParticles() {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        for (const p of particles) {
          p.update();
          p.draw();
        }
        ctx.globalAlpha = 1;
        requestAnimationFrame(animateParticles);
      }

      initParticles();
      animateParticles();

      // ============================================
      // GRID INITIALIZATION
      // ============================================
      function initGrid() {
        const gridEl = document.getElementById("grid");
        gridEl.innerHTML = "";
        tileElements = [];

        levelData.forEach((tile, index) => {
          tile.currentRotation = Math.floor(Math.random() * 4) * 90;

          const div = document.createElement("div");
          div.className = "tile";
          div.innerHTML = tile.type === "straight" ? svgStraight : svgCorner;
          div.style.transform = `rotate(${tile.currentRotation}deg)`;

          div.addEventListener("click", () => rotateTile(index, div));
          gridEl.appendChild(div);
          tileElements.push(div);
        });
      }

      // ============================================
      // TILE ROTATION
      // ============================================
      function rotateTile(index, element) {
        if (!isGameRunning) return;

        levelData[index].currentRotation += 90;
        element.style.transform = `rotate(${levelData[index].currentRotation}deg)`;

        // Click ripple effect
        const ripple = document.createElement("div");
        ripple.className = "click-ripple";
        element.appendChild(ripple);
        setTimeout(() => ripple.remove(), 400);

        // Rotate audio cue placeholder
        checkWinCondition();
      }

      // ============================================
      // WIN CONDITION CHECK
      // ============================================
      function checkWinCondition() {
        let isWin = true;

        for (let tile of levelData) {
          if (tile.isPath) {
            let normalizedRot = tile.currentRotation % 360;
            if (!tile.correct.includes(normalizedRot)) {
              isWin = false;
              break;
            }
          }
        }

        if (isWin) {
          gameWon();
        }
      }

      // ============================================
      // START GAME
      // ============================================
      function startGame() {
        document.getElementById("overlay").style.display = "none";
        document.getElementById("endMessage").style.display = "none";
        document.getElementById("endMessage").className = "";

        const door = document.getElementById("doorMotor");
        door.classList.remove("powered");
        document.getElementById("doorStatusText").innerHTML = "DOOR<br>OFF";

        document.getElementById("warningOverlay").classList.remove("active");
        document.getElementById("failOverlay").classList.remove("active");
        document.getElementById("sysStatus").textContent = "SYS.STATUS: ACTIVE";

        // Reset tile energy states
        tileElements.forEach((el) => el.classList.remove("energy-active"));

        // Remove any energy burst elements
        document.querySelectorAll(".energy-burst").forEach((el) => el.remove());

        initGrid();
        timeLeft = 20;
        isGameRunning = true;
        updateTimerDisplay();
        resetTimerStyles();

        timerInterval = setInterval(() => {
          timeLeft--;
          updateTimerDisplay();
          updateTimerEffects();

          if (timeLeft <= 0) gameOver();
        }, 1000);
      }

      // ============================================
      // TIMER DISPLAY & EFFECTS
      // ============================================
      function updateTimerDisplay() {
        const timerEl = document.getElementById("timer");
        const timeString = timeLeft < 10 ? `0${timeLeft}` : timeLeft;
        timerEl.innerText = `00:${timeString}`;
      }

      function resetTimerStyles() {
        const timerEl = document.getElementById("timer");
        timerEl.className = "timer-display";
      }

      function updateTimerEffects() {
        const timerEl = document.getElementById("timer");
        const container = document.getElementById("gameContainer");

        // Remove previous state classes
        timerEl.classList.remove("warning", "danger", "critical", "emergency");

        if (timeLeft > 10) {
          // Normal
        } else if (timeLeft > 5) {
          timerEl.classList.add("warning");
        } else if (timeLeft > 3) {
          timerEl.classList.add("danger");
          container.classList.add("shaking");
          setTimeout(() => container.classList.remove("shaking"), 200);
        } else if (timeLeft > 0) {
          timerEl.classList.add("critical");
          container.classList.add("shaking");
          setTimeout(() => container.classList.remove("shaking"), 100);
        } else {
          timerEl.classList.add("emergency");
        }
      }

      // ============================================
      // SCREEN EFFECTS
      // ============================================
      function screenFlash(
        color = "#ffffff",
        maxOpacity = 0.7,
        duration = 300,
      ) {
        const flash = document.getElementById("screenFlash");
        flash.style.background = color;
        flash.style.opacity = maxOpacity;
        flash.style.transition = "none";
        requestAnimationFrame(() => {
          flash.style.transition = `opacity ${duration}ms ease-out`;
          flash.style.opacity = "0";
        });
      }

      function triggerShake(intensity = 4, duration = 500) {
        const container = document.getElementById("gameContainer");
        container.classList.add("shaking");
        setTimeout(() => container.classList.remove("shaking"), duration);
      }

      // ============================================
      // GAME OVER (Failure)
      // ============================================
      function gameOver() {
        isGameRunning = false;
        clearInterval(timerInterval);

        // Screen effects
        screenFlash("rgba(255, 0, 0, 0.6)", 0.8, 500);
        triggerShake(6, 600);

        // Warning overlay
        document.getElementById("warningOverlay").classList.add("active");

        // Fail overlay
        const failOv = document.getElementById("failOverlay");
        failOv.classList.add("active");

        // Update system status
        document.getElementById("sysStatus").textContent =
          "SYS.STATUS: FAILURE";

        // Show game over after effects
        setTimeout(() => {
          const overlay = document.getElementById("overlay");
          const msg = document.getElementById("endMessage");
          overlay.style.display = "flex";
          msg.style.display = "block";
          msg.className = "msg-failure";
          msg.innerText = "SYSTEM FAILURE\nHORDE BREACHED";

          document.getElementById("startBtn").style.display = "";
          document.getElementById("startBtn").innerText = "RETRY ROUTING";
        }, 1500);
      }

      // ============================================
      // GAME WON (Victory)
      // ============================================
      function gameWon() {
        isGameRunning = false;
        clearInterval(timerInterval);

        // Step 1: Sequential energy flow through path (0 - 1200ms)
        pathOrder.forEach((tileIndex, i) => {
          setTimeout(() => {
            if (tileElements[tileIndex]) {
              tileElements[tileIndex].classList.add("energy-active");
            }
          }, i * 140);
        });

        // Step 2: Power surge & door activation (1200ms)
        setTimeout(() => {
          const door = document.getElementById("doorMotor");
          door.classList.add("powered");
          document.getElementById("doorStatusText").innerHTML = "DOOR<br>ON";
          document.getElementById("sysStatus").textContent =
            "SYS.STATUS: POWER RESTORED";
        }, 1200);

        // Step 3: Energy burst effect (1400ms)
        setTimeout(() => {
          const burst = document.createElement("div");
          burst.className = "energy-burst";
          document.body.appendChild(burst);
          setTimeout(() => burst.remove(), 1000);
        }, 1400);

        // Step 4: Screen shake + white flash (1500ms)
        setTimeout(() => {
          triggerShake(5, 300);
          screenFlash("#ffffff", 0.8, 400);
        }, 1500);

        // Step 5: Door shows ACCESS GRANTED (1800ms)
        setTimeout(() => {
          document.getElementById("doorStatusText").innerHTML =
            '<span style="font-size:9px">ACCESS<br>GRANTED</span>';
        }, 1800);

        // Step 6: Show victory overlay (2500ms)
        setTimeout(() => {
          const overlay = document.getElementById("overlay");
          const msg = document.getElementById("endMessage");
          overlay.style.display = "flex";
          msg.style.display = "block";
          msg.className = "msg-success";
          msg.innerText = "POWER RESTORED\nESCAPE ROUTE OPEN";
          document.getElementById("startBtn").style.display = "none";
        }, 2500);

        sendWinSignalToESP();
      }

      function sendWinSignalToESP() {
  console.log("Triggering Motor 2...");
  // 1. Send signal to ESP32
  fetch("/win2").catch(e => console.log(e));
  // 2. Wait 5 seconds, then load Game 3
  setTimeout(() => { window.location.href = "/game3"; }, 5000);
}
     
    </script>
  </body>
</html>
)rawliteral";

// =========================================================================
// --- GAME 3: TITAN WARLORD ---
// =========================================================================
// =========================================================================
// --- GAME 3: TITAN WARLORD ---
// =========================================================================
// =========================================================================
// --- GAME 3: TITAN WARLORD ---
// =========================================================================
const char game3_html[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>TITAN WARLORD: FINAL SIEGE</title>
    <style>
      body {
        margin: 0;
        overflow: hidden;
        background-color: #000;
        font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
        user-select: none;
      }
      canvas {
        display: block;
      }
      #ui-layer {
        position: absolute;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        pointer-events: none;
      }
      #crosshair {
        position: absolute;
        top: 50%;
        left: 50%;
        width: 20px;
        height: 20px;
        transform: translate(-50%, -50%);
      }
      .crosshair-line {
        position: absolute;
        background: rgba(50, 255, 255, 0.8);
      }
      .ch-top { top: 0; left: 9px; width: 2px; height: 6px; }
      .ch-bottom { bottom: 0; left: 9px; width: 2px; height: 6px; }
      .ch-left { top: 9px; left: 0; width: 6px; height: 2px; }
      .ch-right { top: 9px; right: 0; width: 6px; height: 2px; }
      .ch-center { top: 9px; left: 9px; width: 2px; height: 2px; background: red; }
      #player-hud {
        position: absolute;
        bottom: 30px;
        left: 30px;
      }
      .bar-container {
        width: 300px;
        height: 20px;
        background: rgba(20, 20, 30, 0.8);
        border: 2px solid #fff;
        margin-bottom: 10px;
        box-shadow: 0 0 10px rgba(0, 255, 255, 0.2);
      }
      #hp-bar {
        width: 100%;
        height: 100%;
        background: #00ffaa;
        transition: width 0.2s;
      }
      .hud-text {
        color: #fff;
        font-weight: bold;
        margin-bottom: 5px;
        text-shadow: 1px 1px 2px #000;
        letter-spacing: 2px;
        font-size: 14px;
      }
      #weapon-hud {
        position: absolute;
        bottom: 30px;
        right: 30px;
        text-align: right;
      }
      #weapon-name {
        font-size: 24px;
        color: #0ff;
        font-weight: bold;
        line-height: 1;
        text-shadow: 0 0 10px #0ff;
        margin-bottom: 5px;
        letter-spacing: 2px;
      }
      #ammo-count {
        font-size: 36px;
        color: #ffaa00;
        font-weight: bold;
        line-height: 1;
        text-shadow: 0 0 10px #ffaa00;
      }
      #cooldown-bar-container {
        width: 200px;
        height: 10px;
        background: rgba(20, 20, 30, 0.8);
        border: 1px solid #ffaa00;
        margin-top: 5px;
        float: right;
      }
      #cooldown-bar {
        width: 100%;
        height: 100%;
        background: #00ffaa;
        transition: width 0.05s;
      }
      #weapons-slots {
        position: absolute;
        bottom: 120px;
        right: 30px;
        text-align: right;
        display: flex;
        gap: 8px;
        flex-direction: row-reverse;
      }
      .weapon-slot {
        width: 50px;
        height: 50px;
        border: 2px solid rgba(255, 255, 255, 0.4);
        background: rgba(20, 20, 30, 0.7);
        color: #fff;
        display: flex;
        align-items: center;
        justify-content: center;
        font-size: 11px;
        font-weight: bold;
        letter-spacing: 1px;
        transition: 0.2s;
      }
      .weapon-slot.active {
        border-color: #0ff;
        box-shadow: 0 0 15px rgba(0, 255, 255, 0.5);
        color: #0ff;
      }
      #boss-hud {
        position: absolute;
        top: 30px;
        left: 50%;
        transform: translateX(-50%);
        width: 800px;
        text-align: center;
        display: none;
      }
      #boss-bar-container {
        width: 100%;
        height: 30px;
        background: rgba(20, 20, 30, 0.8);
        border: 3px solid #ff3333;
        box-shadow: 0 0 20px rgba(255, 50, 50, 0.5);
      }
      #boss-hp-bar {
        width: 100%;
        height: 100%;
        background: #ff3333;
        transition: width 0.1s;
      }
      #boss-name {
        color: #fff;
        font-size: 24px;
        font-weight: bold;
        letter-spacing: 5px;
        margin-bottom: 10px;
        text-shadow: 0 0 10px #f00;
      }
      #hit-marker {
        position: absolute;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -50%);
        color: #ffeb3b;
        font-size: 24px;
        font-weight: bold;
        opacity: 0;
        pointer-events: none;
        text-shadow: 0 0 5px #f00;
      }
      #overlay {
        position: absolute;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        background: rgba(0, 0, 0, 0.85);
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        pointer-events: auto;
      }
      #overlay h1 {
        color: #0ff;
        font-size: 64px;
        text-shadow: 0 0 20px #0ff;
        margin: 0 0 20px 0;
        letter-spacing: 5px;
        animation: pulse 2s infinite;
      }
      @keyframes pulse {
        0%, 100% { text-shadow: 0 0 20px #0ff; }
        50% { text-shadow: 0 0 50px #0ff, 0 0 80px #f00; }
      }
      #overlay p {
        color: #fff;
        font-size: 20px;
        margin-bottom: 15px;
      }
      #overlay .controls-info {
        color: #aaa;
        font-size: 13px;
        margin-bottom: 30px;
        line-height: 1.8;
        text-align: center;
      }
      #start-btn {
        padding: 15px 40px;
        font-size: 24px;
        background: transparent;
        color: #0ff;
        border: 2px solid #0ff;
        cursor: pointer;
        transition: 0.3s;
        box-shadow: 0 0 15px rgba(0, 255, 255, 0.3);
        letter-spacing: 2px;
      }
      #start-btn:hover {
        background: #0ff;
        color: #000;
        box-shadow: 0 0 30px #0ff;
      }
      #damage-flash {
        position: absolute;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        background: rgba(255, 0, 0, 0.3);
        opacity: 0;
        pointer-events: none;
        transition: opacity 0.1s;
      }
      #message-center {
        position: absolute;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -50%);
        color: #ff0;
        font-size: 28px;
        font-weight: bold;
        opacity: 0;
        pointer-events: none;
        text-shadow: 0 0 20px #f00;
        letter-spacing: 3px;
        transition: opacity 0.3s;
      }
      #dash-hud {
        position: absolute;
        bottom: 100px;
        left: 30px;
      }
      #dash-bar-container {
        width: 200px;
        height: 12px;
        background: rgba(20, 20, 30, 0.8);
        border: 1px solid #00ccff;
        box-shadow: 0 0 8px rgba(0, 200, 255, 0.3);
      }
      #dash-bar {
        width: 100%;
        height: 100%;
        background: #00ccff;
        transition: width 0.05s;
      }
      #boss-energy-bar-container {
        width: 300px;
        height: 12px;
        background: rgba(20, 20, 30, 0.8);
        border: 1px solid #ff0;
        margin: 5px auto 0;
        box-shadow: 0 0 8px rgba(255, 255, 0, 0.3);
      }
      #boss-energy-bar {
        width: 0%;
        height: 100%;
        background: #ff0;
        transition: width 0.1s;
      }
      #boss-cooldown-bar-container {
        width: 300px;
        height: 12px;
        background: rgba(20, 20, 30, 0.8);
        border: 1px solid #ff8800;
        margin: 5px auto 0;
        box-shadow: 0 0 8px rgba(255, 136, 0, 0.3);
      }
      #boss-cooldown-bar {
        width: 100%;
        height: 100%;
        background: linear-gradient(90deg, #ff0, #ff8800, #f00);
        transition: width 0.1s;
      }
      #vignette-overlay {
        position: absolute;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        pointer-events: none;
        opacity: 0;
        transition: opacity 0.5s;
        background: radial-gradient(
          ellipse at center,
          transparent 50%,
          rgba(180, 0, 0, 0.5) 80%,
          rgba(100, 0, 0, 0.8) 100%
        );
      }
      #heal-indicator {
        position: absolute;
        bottom: 160px;
        left: 30px;
        color: #0f0;
        font-weight: bold;
        font-size: 16px;
        text-shadow: 0 0 10px #0f0;
        opacity: 0;
        transition: opacity 0.3s;
      }
    </style>
    <script async src="https://unpkg.com/es-module-shims@1.6.3/dist/es-module-shims.js"></script>
    <script type="importmap">
      {
        "imports": {
          "three": "https://unpkg.com/three@0.150.1/build/three.module.js",
          "three/addons/": "https://unpkg.com/three@0.150.1/examples/jsm/"
        }
      }
    </script>
  </head>
  <body>
    <div id="ui-layer">
      <div id="crosshair">
        <div class="crosshair-line ch-top"></div>
        <div class="crosshair-line ch-bottom"></div>
        <div class="crosshair-line ch-left"></div>
        <div class="crosshair-line ch-right"></div>
        <div class="ch-center"></div>
      </div>
      <div id="vignette-overlay"></div>
      <div id="boss-hud">
        <div id="boss-name">TITAN WARLORD - PHASE 1</div>
        <div id="boss-bar-container"><div id="boss-hp-bar"></div></div>
        <div id="boss-energy-bar-container">
          <div id="boss-energy-bar"></div>
        </div>
        <div class="hud-text" style="margin-top: 5px; font-size: 12px">
          BOSS ATTACK COOLDOWN
        </div>
        <div id="boss-cooldown-bar-container">
          <div id="boss-cooldown-bar"></div>
        </div>
      </div>
      <div id="player-hud">
        <div class="hud-text">INTEGRITY</div>
        <div class="bar-container"><div id="hp-bar"></div></div>
      </div>
      <div id="heal-indicator">+ HEALING DRONE ACTIVE +</div>
      <div id="weapon-hud">
        <div id="weapon-name">ASSAULT RIFLE</div>
        <div id="ammo-count">30 / ∞</div>
        <div id="cooldown-bar-container"><div id="cooldown-bar"></div></div>
      </div>
      <div id="weapons-slots">
        <div class="weapon-slot" data-slot="4">ROCKET</div>
        <div class="weapon-slot" data-slot="3">RAILGUN</div>
        <div class="weapon-slot" data-slot="2">SHOTGUN</div>
        <div class="weapon-slot active" data-slot="1">RIFLE</div>
      </div>
      <div id="hit-marker">X</div>
      <div id="damage-flash"></div>
      <div id="message-center"></div>
      <div id="dash-hud">
        <div class="hud-text">DASH</div>
        <div id="dash-bar-container"><div id="dash-bar"></div></div>
      </div>
    </div>
    <div id="overlay">
      <h1>TITAN WARLORD</h1>
      <p>A First-Person Survival Horror Experience</p>
      <div class="controls-info">
        WASD - Move | Mouse - Look | SHIFT - Sprint | SPACE - Jump<br />CTRL -
        Dash (Invincible!) | 1-4 - Switch Weapon | R - Reload | LMB - Fire
      </div>
      <button id="start-btn">INITIATE COMBAT (CLICK)</button>
    </div>

    <script type="module">
      import * as THREE from "three";
      import { PointerLockControls } from "three/addons/controls/PointerLockControls.js";
      import { EffectComposer } from "three/addons/postprocessing/EffectComposer.js";
      import { RenderPass } from "three/addons/postprocessing/RenderPass.js";
      import { UnrealBloomPass } from "three/addons/postprocessing/UnrealBloomPass.js";

      const gameState = {
        isRunning: false,
        playerHP: 100,
        currentWeapon: 1,
        isReloading: false,
        mouseDown: false,
        isInvincible: false,
      };
      const weapons = {
        1: { name: "ASSAULT RIFLE", ammo: 30, maxAmmo: 30, fireRate: 80, damage: 45, cooldown: 0.08, spread: 0.015, reloadTime: 1500, color: 0x00ffff, infinite: true },
        2: { name: "COMBAT SHOTGUN", ammo: 8, maxAmmo: 8, fireRate: 700, damage: 70, pellets: 4, cooldown: 0.7, spread: 0.08, reloadTime: 2000, color: 0xff8800, infinite: true },
        3: { name: "RAILGUN", ammo: 100, maxAmmo: 100, fireRate: 50, damage: 80, cooldown: 0.05, spread: 0.0, reloadTime: 2500, color: 0xff00ff, infinite: true, beam: true },
        4: { name: "ROCKET LAUNCHER", ammo: 5, maxAmmo: 5, fireRate: 1200, damage: 1000, cooldown: 1.2, spread: 0.02, reloadTime: 2500, color: 0xff4400, infinite: true, projectile: true }
      };

      const scene = new THREE.Scene();
      scene.background = new THREE.Color(0x0a0505);
      scene.fog = new THREE.FogExp2(0x0a0505, 0.0015);
      const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 2000);
      const renderer = new THREE.WebGLRenderer({ antialias: false, powerPreference: "high-performance" });
      renderer.setSize(window.innerWidth, window.innerHeight);
      renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
      renderer.toneMapping = THREE.ACESFilmicToneMapping;
      renderer.toneMappingExposure = 0.8;
      renderer.shadowMap.enabled = true;
      renderer.shadowMap.type = THREE.PCFSoftShadowMap;
      document.body.appendChild(renderer.domElement);

      const renderScene = new RenderPass(scene, camera);
      const bloomPass = new UnrealBloomPass(new THREE.Vector2(window.innerWidth, window.innerHeight), 1.5, 0.4, 0.85);
      bloomPass.threshold = 0.35;
      bloomPass.strength = 0.8;
      bloomPass.radius = 0.3;
      const composer = new EffectComposer(renderer);
      composer.addPass(renderScene);
      composer.addPass(bloomPass);

      const ambientLight = new THREE.AmbientLight(0x111111, 0.35);
      scene.add(ambientLight);
      const hemiLight = new THREE.HemisphereLight(0x443322, 0x000000, 0.15);
      hemiLight.position.set(0, 200, 0);
      scene.add(hemiLight);
      const dirLight = new THREE.DirectionalLight(0xddccaa, 0.5);
      dirLight.position.set(-100, 150, -100);
      dirLight.castShadow = true;
      dirLight.shadow.mapSize.width = 1024;
      dirLight.shadow.mapSize.height = 1024;
      dirLight.shadow.camera.near = 1;
      dirLight.shadow.camera.far = 500;
      dirLight.shadow.camera.left = -200;
      dirLight.shadow.camera.right = 200;
      dirLight.shadow.camera.top = 200;
      dirLight.shadow.camera.bottom = -200;
      scene.add(dirLight);
      const bossLight = new THREE.PointLight(0xff2200, 20, 250, 1.5);
      bossLight.position.set(0, 50, -200);
      scene.add(bossLight);
      const skyBeamLight = new THREE.PointLight(0xffff00, 100, 500, 1);
      skyBeamLight.position.set(0, 300, 0);
      skyBeamLight.visible = false;
      scene.add(skyBeamLight);

      const floorGeo = new THREE.PlaneGeometry(3000, 3000, 30, 30);
      const posAttribute = floorGeo.attributes.position;
      for (let i = 0; i < posAttribute.count; i++) posAttribute.setZ(i, (Math.random() - 0.5) * 8);
      floorGeo.computeVertexNormals();
      const floor = new THREE.Mesh(floorGeo, new THREE.MeshStandardMaterial({ color: 0x1a1a1a, roughness: 0.95, metalness: 0.05 }));
      floor.rotation.x = -Math.PI / 2;
      floor.receiveShadow = true;
      scene.add(floor);

      for (let i = 0; i < 50; i++) {
        const blood = new THREE.Mesh(new THREE.CircleGeometry(2 + Math.random() * 8, 16), new THREE.MeshBasicMaterial({ color: 0x330000, transparent: true, opacity: 0.4 + Math.random() * 0.3 }));
        blood.rotation.x = -Math.PI / 2;
        blood.position.set((Math.random() - 0.5) * 600, 0.1, (Math.random() - 0.5) * 600);
        scene.add(blood);
      }

      const bldgGeo = new THREE.BoxGeometry(1, 1, 1);
      const bldgMat = new THREE.MeshStandardMaterial({ color: 0x1a1a1a, roughness: 0.9, metalness: 0.2 });
      const bldgCount = 120;
      const bldgMesh = new THREE.InstancedMesh(bldgGeo, bldgMat, bldgCount);
      bldgMesh.castShadow = true;
      bldgMesh.receiveShadow = true;
      const buildingColliders = [];
      const dummy = new THREE.Object3D();
      for (let i = 0; i < bldgCount; i++) {
        const x = (Math.random() - 0.5) * 2000, z = (Math.random() - 0.5) * 2000;
        if (Math.abs(x) < 250 && Math.abs(z) < 250) continue;
        const width = 10 + Math.random() * 40, depth = 10 + Math.random() * 40, height = 20 + Math.random() * 200;
        dummy.position.set(x, height / 2, z);
        dummy.scale.set(width, height, depth);
        dummy.updateMatrix();
        bldgMesh.setMatrixAt(i, dummy.matrix);
        buildingColliders.push({ x, z, halfW: width / 2 + 5, halfD: depth / 2 + 5 });
      }
      bldgMesh.instanceMatrix.needsUpdate = true;
      scene.add(bldgMesh);

      const debrisGeo = new THREE.BoxGeometry(3, 2, 5);
      const debrisMat = new THREE.MeshStandardMaterial({ color: 0x333333, roughness: 0.6, metalness: 0.4 });
      for (let i = 0; i < 80; i++) {
        const debris = new THREE.Mesh(debrisGeo, debrisMat);
        debris.position.set((Math.random() - 0.5) * 800, 1, (Math.random() - 0.5) * 800);
        debris.rotation.y = Math.random() * Math.PI * 2;
        debris.castShadow = true;
        scene.add(debris);
      }

      const skyBeam = new THREE.Mesh(new THREE.CylinderGeometry(3, 8, 600, 8), new THREE.MeshBasicMaterial({ color: 0xffff00, transparent: true, opacity: 0.6, blending: THREE.AdditiveBlending, depthWrite: false }));
      skyBeam.position.y = 300;
      skyBeam.visible = false;
      scene.add(skyBeam);

      const controls = new PointerLockControls(camera, document.body);
      const velocity = new THREE.Vector3();
      const direction = new THREE.Vector3();
      let moveForward = false, moveBackward = false, moveLeft = false, moveRight = false, canJump = false;
      let isSprinting = false;
      let dashCooldown = 0;
      const dashCooldownMax = 3.0;
      let isDashing = false, dashTimer = 0;
      const dashDuration = 0.15, dashSpeed = 1400;

      function checkBuildingCollision(x, z) {
        for (const b of buildingColliders) if (Math.abs(x - b.x) < b.halfW && Math.abs(z - b.z) < b.halfD) return true;
        return false;
      }

      function triggerDash() {
        if (dashCooldown > 0 || isDashing || !gameState.isRunning) return;
        isDashing = true;
        gameState.isInvincible = true;
        dashTimer = dashDuration;
        dashCooldown = dashCooldownMax;
        showMessage("DASH - INVINCIBLE!");
      }

      document.getElementById("start-btn").addEventListener("click", () => { controls.lock(); });
      controls.addEventListener("lock", () => {
        document.getElementById("overlay").style.display = "none";
        document.getElementById("boss-hud").style.display = "block";
        gameState.isRunning = true;
        gameState.playerHP = 100;
        document.getElementById("hp-bar").style.width = "100%";
        document.getElementById("hp-bar").style.background = "#00ffaa";
        document.getElementById("vignette-overlay").style.opacity = "0";
        document.getElementById("heal-indicator").style.opacity = "0";
        bossState.spawnTimer = 0;
        bossState.spawning = true;
        bossGroup.scale.set(0.1, 0.1, 0.1);
        bossGroup.position.set(0, 0, -200);
        bossState.damageSinceLastRegen = 0;
        bossState.lastRegenHpThreshold = 100;
        dashCooldown = 0;
        isDashing = false;
        gameState.isInvincible = false;
        renderer.toneMappingExposure = 0.8;
        if (healDrone) { scene.remove(healDrone); healDrone = null; }
        healTimer = 0;
        lastHpThreshold = 100;
        showMessage("TITAN RISES...");
      });
      controls.addEventListener("unlock", () => {
        document.getElementById("overlay").style.display = "flex";
        gameState.isRunning = false;
        gameState.mouseDown = false;
        gameState.isInvincible = false;
      });

      document.addEventListener("keydown", (event) => {
        if (!gameState.isRunning) return;
        switch (event.code) {
          case "ArrowUp": case "KeyW": moveForward = true; break;
          case "ArrowLeft": case "KeyA": moveLeft = true; break;
          case "ArrowDown": case "KeyS": moveBackward = true; break;
          case "ArrowRight": case "KeyD": moveRight = true; break;
          case "Space": if (canJump) velocity.y += 200; canJump = false; break;
          case "ShiftLeft": case "ShiftRight": isSprinting = true; break;
          case "ControlLeft": case "ControlRight": triggerDash(); break;
          case "KeyR": reloadWeapon(); break;
          case "Digit1": switchWeapon(1); break;
          case "Digit2": switchWeapon(2); break;
          case "Digit3": switchWeapon(3); break;
          case "Digit4": switchWeapon(4); break;
        }
      });
      document.addEventListener("keyup", (event) => {
        switch (event.code) {
          case "ArrowUp": case "KeyW": moveForward = false; break;
          case "ArrowLeft": case "KeyA": moveLeft = false; break;
          case "ArrowDown": case "KeyS": moveBackward = false; break;
          case "ArrowRight": case "KeyD": moveRight = false; break;
          case "ShiftLeft": case "ShiftRight": isSprinting = false; break;
        }
      });

      const weaponGroup = new THREE.Group();
      camera.add(weaponGroup);
      scene.add(camera);
      let gunModel, barrelModel, secondaryModel;
      let railgunBeam = null;

      function createWeaponModel(wepDef) {
        while (weaponGroup.children.length > 0) weaponGroup.remove(weaponGroup.children[0]);
        if (railgunBeam) { scene.remove(railgunBeam); railgunBeam = null; }
        gunModel = new THREE.Group();
        const bodyMat = new THREE.MeshStandardMaterial({ color: 0x444444, metalness: 0.9, roughness: 0.2 });
        const body = new THREE.Mesh(new THREE.BoxGeometry(0.12, 0.18, 0.7), bodyMat);
        gunModel.add(body);
        const grip = new THREE.Mesh(new THREE.BoxGeometry(0.08, 0.2, 0.15), bodyMat);
        grip.position.set(0, -0.18, 0.15); grip.rotation.x = 0.3; gunModel.add(grip);
        barrelModel = new THREE.Mesh(new THREE.CylinderGeometry(0.025, 0.03, 0.5, 8), new THREE.MeshStandardMaterial({ color: 0x111111, metalness: 0.95, roughness: 0.1 }));
        barrelModel.rotation.x = Math.PI / 2; barrelModel.position.set(0, 0.03, -0.5); gunModel.add(barrelModel);
        if (wepDef.name === "COMBAT SHOTGUN") {
          [[0, 0], [0.06, 0.04], [-0.06, 0.04], [0, -0.04]].forEach(([ox, oy]) => { const sb = barrelModel.clone(); sb.position.x += ox; sb.position.y += oy; gunModel.add(sb); });
          gunModel.remove(barrelModel);
        }
        if (wepDef.name === "RAILGUN") {
          barrelModel.scale.set(1.8, 1, 1.8); barrelModel.position.z = -0.7;
          const coilMat = new THREE.MeshStandardMaterial({ color: 0xff00ff, emissive: 0xff00ff, emissiveIntensity: 2 });
          for (let i = 0; i < 4; i++) { const coil = new THREE.Mesh(new THREE.TorusGeometry(0.06, 0.02, 8, 16), coilMat); coil.position.set(0, 0.03, -0.35 - i * 0.12); gunModel.add(coil); }
        }
        if (wepDef.name === "ROCKET LAUNCHER") {
          barrelModel.scale.set(1.4, 1, 1.4); barrelModel.position.z = -0.45;
          const tube = new THREE.Mesh(new THREE.CylinderGeometry(0.08, 0.1, 1.1, 8), new THREE.MeshStandardMaterial({ color: 0x555555, metalness: 0.9, roughness: 0.2 }));
          tube.rotation.x = Math.PI / 2; tube.position.set(0, 0.03, -0.65); gunModel.add(tube);
        }
        gunModel.position.set(0.35, -0.35, -0.55); weaponGroup.add(gunModel);
        secondaryModel = new THREE.Mesh(new THREE.PlaneGeometry(0.6, 0.6), new THREE.MeshBasicMaterial({ color: wepDef.color, transparent: true, opacity: 0, blending: THREE.AdditiveBlending, depthWrite: false }));
        secondaryModel.position.set(0.35, -0.3, -1.3); weaponGroup.add(secondaryModel);
      }
      createWeaponModel(weapons[1]);

      const raycaster = new THREE.Raycaster();
      let lastFireTime = 0, currentCooldown = 0, currentCooldownMax = 0;

      document.addEventListener("mousedown", (e) => { if (e.button === 0 && gameState.isRunning) { gameState.mouseDown = true; if (!weapons[gameState.currentWeapon].beam) fireWeapon(); } });
      document.addEventListener("mouseup", (e) => { if (e.button === 0) { gameState.mouseDown = false; if (railgunBeam) railgunBeam.visible = false; } });
      const rockets = [];

      function switchWeapon(slot) {
        if (gameState.isReloading || gameState.currentWeapon === slot) return;
        gameState.currentWeapon = slot; gameState.mouseDown = false; if (railgunBeam) railgunBeam.visible = false;
        createWeaponModel(weapons[slot]); currentCooldown = 0; currentCooldownMax = weapons[slot].cooldown;
        document.getElementById("weapon-name").innerText = weapons[slot].name;
        document.getElementById("ammo-count").innerText = weapons[slot].ammo + " / ∞";
        document.getElementById("ammo-count").style.color = "#ffaa00";
        document.querySelectorAll(".weapon-slot").forEach((el) => { el.classList.remove("active"); if (parseInt(el.dataset.slot) === slot) el.classList.add("active"); });
      }

      function reloadWeapon() {
        const wep = weapons[gameState.currentWeapon];
        if (gameState.isReloading || wep.ammo === wep.maxAmmo) return;
        gameState.isReloading = true;
        document.getElementById("ammo-count").innerText = "REL..."; document.getElementById("ammo-count").style.color = "#ff0";
        const startRot = weaponGroup.rotation.x; weaponGroup.rotation.x = Math.PI / 4; weaponGroup.position.y -= 0.1;
        setTimeout(() => { wep.ammo = wep.maxAmmo; gameState.isReloading = false; weaponGroup.rotation.x = startRot; weaponGroup.position.y += 0.1; document.getElementById("ammo-count").innerText = wep.ammo + " / ∞"; document.getElementById("ammo-count").style.color = "#ffaa00"; }, wep.reloadTime);
      }

      function fireWeapon() {
        const wep = weapons[gameState.currentWeapon]; const now = performance.now();
        if (now - lastFireTime < wep.fireRate || gameState.isReloading || wep.ammo <= 0 || currentCooldown > 0) return;
        lastFireTime = now; wep.ammo--; currentCooldown = wep.cooldown; currentCooldownMax = wep.cooldown;
        document.getElementById("ammo-count").innerText = wep.ammo + " / ∞";
        if (wep.ammo <= 0 && wep.infinite) reloadWeapon();
        weaponGroup.position.z += 0.06; weaponGroup.rotation.x += 0.03;
        if (secondaryModel) { secondaryModel.material.opacity = 1.0; secondaryModel.rotation.z = Math.random() * Math.PI; }
        camera.position.y += (Math.random() - 0.5) * 0.6; camera.position.x += (Math.random() - 0.5) * 0.6;
        if (wep.pellets) { for (let i = 0; i < wep.pellets; i++) { raycaster.setFromCamera(new THREE.Vector2((Math.random() - 0.5) * wep.spread * 2, (Math.random() - 0.5) * wep.spread * 2), camera); checkBossHit(wep); } }
        else if (wep.projectile) { spawnRocket(wep); }
        else { raycaster.setFromCamera(new THREE.Vector2(0, 0), camera); checkBossHit(wep); }
      }

      function spawnRocket(wep) {
        const rocket = new THREE.Mesh(new THREE.SphereGeometry(1.0, 8, 8), new THREE.MeshBasicMaterial({ color: 0xff4400 }));
        const startPos = camera.position.clone(); const dir = new THREE.Vector3(); camera.getWorldDirection(dir); startPos.add(dir.clone().multiplyScalar(3));
        rocket.position.copy(startPos); rocket.velocity = dir.clone().multiplyScalar(350); rocket.life = 3.5; rocket.damage = bossState.maxHp * 0.2;
        scene.add(rocket); rockets.push(rocket);
        const glow = new THREE.Mesh(new THREE.SphereGeometry(0.6, 8, 8), new THREE.MeshBasicMaterial({ color: 0xffaa00, transparent: true, opacity: 0.7, blending: THREE.AdditiveBlending, depthWrite: false }));
        glow.position.copy(startPos); scene.add(glow); rocket.glow = glow;
      }

      function checkBossHit(wep) {
        const intersects = raycaster.intersectObject(bossGroup, true);
        if (intersects.length > 0) {
          let obj = intersects[0].object;
          if (obj.userData.isCore || obj.userData.isArmor || obj.userData.isBoss) { let dmg = obj.userData.isCore ? wep.damage * 2.5 : wep.damage; bossTakeDamage(dmg, intersects[0].point); }
        }
      }

      const bossState = { hp: 30000, maxHp: 30000, phase: 1, timer: 0, spawnTimer: 0, spawning: true, targetScale: 1.0, attackTimer: 0, energyTimer: 0, isChanneling: false, channelDuration: 0, currentAttack: "none", attackAnimTimer: 0, damageSinceLastRegen: 0, lastRegenHpThreshold: 100 };
      const bossGroup = new THREE.Group(); bossGroup.position.set(0, 0, -200); bossGroup.scale.set(0.1, 0.1, 0.1); scene.add(bossGroup);
      const fleshMat = new THREE.MeshStandardMaterial({ color: 0x3a1515, roughness: 0.8, metalness: 0.1 });
      const boneMat = new THREE.MeshStandardMaterial({ color: 0xccccaa, roughness: 0.3, metalness: 0.3 });
      const armorMat = new THREE.MeshStandardMaterial({ color: 0x1a1a2e, roughness: 0.3, metalness: 0.9 });
      const coreMat = new THREE.MeshStandardMaterial({ color: 0xff2200, roughness: 0.2, metalness: 0.5, emissive: 0xff0000, emissiveIntensity: 2 });
      const torsoGeo = new THREE.CylinderGeometry(12, 16, 35, 8, 4); const torsoPos = torsoGeo.attributes.position;
      for (let i = 0; i < torsoPos.count; i++) { const x = torsoPos.getX(i), y = torsoPos.getY(i), z = torsoPos.getZ(i); const distort = 1 + Math.sin(y * 0.5) * 0.3 + Math.random() * 0.2; torsoPos.setX(i, x * distort); torsoPos.setZ(i, z * distort); }
      torsoGeo.computeVertexNormals(); const torso = new THREE.Mesh(torsoGeo, fleshMat); torso.position.y = 45; torso.userData = { isBoss: true, isArmor: true }; torso.castShadow = true; bossGroup.add(torso);
      for (let i = 0; i < 8; i++) { const rib = new THREE.Mesh(new THREE.CylinderGeometry(1, 1.5, 8, 6), boneMat); rib.position.y = 40 + i * 4; rib.position.x = Math.sin(i * 1.2) * 8; rib.position.z = Math.cos(i * 1.2) * 6; rib.rotation.z = Math.PI / 2; rib.userData = { isArmor: true }; rib.castShadow = true; bossGroup.add(rib); }
      const core = new THREE.Mesh(new THREE.SphereGeometry(5, 16, 16), coreMat); core.position.set(0, 50, 10); core.userData = { isCore: true }; bossGroup.add(core);
      const coreBack = new THREE.Mesh(new THREE.SphereGeometry(3, 12, 12), coreMat.clone()); coreBack.position.set(0, 42, -10); coreBack.userData = { isCore: true }; bossGroup.add(coreBack);
      const headGroup = new THREE.Group(); headGroup.position.set(0, 65, 0); const skullGeo = new THREE.SphereGeometry(7, 8, 8); const skullPos = skullGeo.attributes.position;
      for (let i = 0; i < skullPos.count; i++) { const y = skullPos.getY(i); if (y < 0) skullPos.setY(i, y * 0.6); }
      skullGeo.computeVertexNormals(); const skull = new THREE.Mesh(skullGeo, fleshMat); skull.scale.set(1, 1.2, 0.9); skull.userData = { isBoss: true }; skull.castShadow = true; headGroup.add(skull);
      for (let side = -1; side <= 1; side += 2) { const horn = new THREE.Mesh(new THREE.ConeGeometry(2, 12, 8, 4), boneMat); horn.position.set(side * 4, 8, -2); horn.rotation.x = -0.3; horn.rotation.z = side * 0.3; horn.userData = { isArmor: true }; horn.castShadow = true; headGroup.add(horn); const horn2 = new THREE.Mesh(new THREE.ConeGeometry(1.2, 7, 6, 4), boneMat); horn2.position.set(side * 5.5, 4, -1); horn2.rotation.x = -0.2; horn2.rotation.z = side * 0.5; horn2.userData = { isArmor: true }; headGroup.add(horn2); }
      for (let side = -1; side <= 1; side += 2) { headGroup.add(new THREE.Mesh(new THREE.SphereGeometry(1.2, 8, 8), new THREE.MeshBasicMaterial({ color: 0x000000 }))).position.set(side * 2.5, 2, 6); headGroup.add(new THREE.Mesh(new THREE.SphereGeometry(0.6, 8, 8), new THREE.MeshBasicMaterial({ color: 0xff0000 }))).position.set(side * 2.5, 2, 6.8); }
      for (let i = -3; i <= 3; i++) { const tooth = new THREE.Mesh(new THREE.ConeGeometry(0.5, 3, 6), boneMat); tooth.position.set(i * 1.2, -3, 5.5); tooth.rotation.x = -0.2; headGroup.add(tooth); }
      bossGroup.add(headGroup);

      const rightArmGroup = new THREE.Group(); rightArmGroup.position.set(14, 50, 4); rightArmGroup.add(new THREE.Mesh(new THREE.CylinderGeometry(3, 4, 15, 8), fleshMat)).userData = { isArmor: true }; rightArmGroup.children[0].castShadow = true;
      const swordGroup = new THREE.Group(); swordGroup.position.y = -12; const blade = new THREE.Mesh(new THREE.BoxGeometry(3, 30, 0.8), new THREE.MeshStandardMaterial({ color: 0xddccaa, roughness: 0.2, metalness: 0.7, emissive: 0x331100, emissiveIntensity: 0.5 })); blade.position.y = -12; blade.userData = { isArmor: true }; blade.castShadow = true; swordGroup.add(blade);
      for (let s = -1; s <= 1; s += 2) { const gs = new THREE.Mesh(new THREE.ConeGeometry(2, 6, 6), boneMat); gs.position.set(s * 3, -2, 0); gs.rotation.z = (s * Math.PI) / 2; swordGroup.add(gs); }
      rightArmGroup.add(swordGroup); bossGroup.add(rightArmGroup);

      const leftArmGroup = new THREE.Group(); leftArmGroup.position.set(-14, 50, 4); leftArmGroup.add(new THREE.Mesh(new THREE.CylinderGeometry(3, 4, 15, 8), fleshMat)).userData = { isArmor: true }; leftArmGroup.children[0].castShadow = true;
      const chainGroup = new THREE.Group(); for (let c = 0; c < 6; c++) { const link = new THREE.Mesh(new THREE.TorusGeometry(1.5, 0.3, 8, 8), new THREE.MeshStandardMaterial({ color: 0x666666, metalness: 0.9, roughness: 0.2 })); link.position.y = -6 - c * 3; link.rotation.x = Math.PI / 2; link.userData = { isArmor: true }; chainGroup.add(link); }
      const ballGroup = new THREE.Group(); ballGroup.add(new THREE.Mesh(new THREE.SphereGeometry(4, 12, 12), new THREE.MeshStandardMaterial({ color: 0x444444, metalness: 0.9, roughness: 0.2 })));
      for (let s = 0; s < 20; s++) { const spike = new THREE.Mesh(new THREE.ConeGeometry(0.6, 3, 6), new THREE.MeshStandardMaterial({ color: 0x888888, metalness: 0.9, roughness: 0.1 })); spike.position.setFromSphericalCoords(4.2, Math.random() * Math.PI, Math.random() * Math.PI * 2); spike.lookAt(new THREE.Vector3(0, 0, 0)); ballGroup.add(spike); }
      ballGroup.position.y = -24; ballGroup.userData = { isArmor: true }; chainGroup.add(ballGroup); leftArmGroup.add(chainGroup); bossGroup.add(leftArmGroup);

      for (let side = -1; side <= 1; side += 2) { const pauldron = new THREE.Mesh(new THREE.SphereGeometry(8, 8, 6, 0, Math.PI * 2, 0, Math.PI / 2), armorMat); pauldron.position.set(side * 12, 58, 2); pauldron.scale.set(1.2, 0.5, 1); pauldron.userData = { isArmor: true }; pauldron.castShadow = true; bossGroup.add(pauldron); }
      for (let i = 0; i < 6; i++) { const spike = new THREE.Mesh(new THREE.ConeGeometry(2, 10, 6), boneMat); spike.position.set((Math.random() - 0.5) * 8, 38 + Math.random() * 20, -11); spike.rotation.x = -0.3; spike.userData = { isArmor: true }; spike.castShadow = true; bossGroup.add(spike); }
      for (let side = -1; side <= 1; side += 2) { const legGroup = new THREE.Group(); const thigh = new THREE.Mesh(new THREE.CylinderGeometry(4, 5, 20, 8), fleshMat); thigh.position.y = -10; thigh.userData = { isArmor: true }; thigh.castShadow = true; legGroup.add(thigh); const shin = new THREE.Mesh(new THREE.CylinderGeometry(3, 3.5, 18, 8), fleshMat); shin.position.y = -28; shin.userData = { isArmor: true }; shin.castShadow = true; legGroup.add(shin); const hoof = new THREE.Mesh(new THREE.BoxGeometry(4, 4, 6), boneMat); hoof.position.y = -38; hoof.userData = { isArmor: true }; legGroup.add(hoof); legGroup.position.set(side * 8, 28, 0); bossGroup.add(legGroup); }

      function bossTakeDamage(amount, hitPoint) {
        bossState.hp -= amount; bossState.damageSinceLastRegen += amount; const extraCount = amount > 500 ? 50 : amount > 100 ? 25 : 8; createExplosion(hitPoint, amount > 500 ? 0xff0000 : amount > 100 ? 0xff4400 : 0xffaa00, extraCount); const hpPct = Math.max(0, (bossState.hp / bossState.maxHp) * 100); document.getElementById("boss-hp-bar").style.width = hpPct + "%";
        if (hpPct <= 60 && bossState.phase === 1) { bossState.phase = 2; coreMat.color.setHex(0xff6600); coreMat.emissive.setHex(0xff4400); bossLight.color.setHex(0xff4400); bossLight.intensity = 40; document.getElementById("boss-name").innerText = "TITAN WARLORD - PHASE 2 (RAGE)"; showMessage("TITAN ENRAGED!"); bossState.targetScale = 1.3; }
        else if (hpPct <= 25 && bossState.phase === 2) { bossState.phase = 3; coreMat.color.setHex(0xff0000); coreMat.emissive.setHex(0xff0000); bossLight.color.setHex(0xff0000); bossLight.intensity = 60; document.getElementById("boss-name").innerText = "TITAN WARLORD - PHASE 3 (BERSERK)"; showMessage("TITAN GOES BERSERK!!!"); bossState.targetScale = 1.6; }
        if (bossState.damageSinceLastRegen >= 8000 && !bossState.isChanneling && !bossState.spawning) { triggerBossRegen(); }
        if (!bossState.isChanneling && !bossState.spawning) { const thresholds = [90, 75, 60, 45, 30, 15]; for (const t of thresholds) { if (hpPct <= t && bossState.lastRegenHpThreshold > t) { bossState.lastRegenHpThreshold = t; triggerBossRegen(); break; } } }
        const marker = document.getElementById("hit-marker"); marker.style.opacity = 1; marker.style.transform = `translate(-50%, -50%) scale(${amount > 500 ? 3.0 : amount > 100 ? 2.0 : 1.4})`; marker.innerText = amount > 500 ? "MASSIVE!" : amount > 200 ? "CRITICAL!" : amount > 100 ? "CRIT!" : "X"; setTimeout(() => { marker.style.opacity = 0; marker.style.transform = "translate(-50%, -50%) scale(1)"; }, 200);
        if (bossState.hp <= 0) triggerVictory();
      }

      function showMessage(msg) { const el = document.getElementById("message-center"); el.innerText = msg; el.style.opacity = 1; setTimeout(() => { el.style.opacity = 0; }, 2000); }

      function triggerBossRegen() { if (bossState.isChanneling || bossState.spawning) return; bossState.isChanneling = true; bossState.channelDuration = 3.0; bossState.energyTimer = 0; bossState.damageSinceLastRegen = 0; bossState.currentAttack = "channel"; showMessage("TITAN CHANNELS ENERGY FROM THE SKY!"); skyBeam.visible = true; skyBeamLight.visible = true; skyBeamLight.intensity = 100; skyBeam.position.set(bossGroup.position.x, 300, bossGroup.position.z); skyBeamLight.position.set(bossGroup.position.x, 300, bossGroup.position.z); document.getElementById("boss-energy-bar").style.width = "0%"; }

      const particles = []; const partGeo = new THREE.BoxGeometry(0.5, 0.5, 0.5);
      function createExplosion(position, colorHex, count) { const mat = new THREE.MeshBasicMaterial({ color: colorHex }); for (let i = 0; i < count; i++) { const p = new THREE.Mesh(partGeo, mat); p.position.copy(position); p.velocity = new THREE.Vector3((Math.random() - 0.5) * 5, (Math.random() - 0.5) * 5 + 2, (Math.random() - 0.5) * 5); p.life = 1.0; scene.add(p); particles.push(p); } }

      function createBlastExplosion(position) {
        createExplosion(position, 0xff4400, 80);
        for (let a = 0; a < 30; a++) { const angle = (a / 30) * Math.PI * 2; const ringPos = position.clone().add(new THREE.Vector3(Math.cos(angle) * 5, 0, Math.sin(angle) * 5)); createExplosion(ringPos, 0xffff00, 3); }
        setTimeout(() => { for (let a = 0; a < 20; a++) { const angle = (a / 20) * Math.PI * 2; const ringPos = position.clone().add(new THREE.Vector3(Math.cos(angle) * 15, 2, Math.sin(angle) * 15)); createExplosion(ringPos, 0xff8800, 4); } }, 100);
        setTimeout(() => { for (let i = 0; i < 20; i++) { const p = new THREE.Mesh(new THREE.SphereGeometry(1.5 + Math.random() * 3, 4, 4), new THREE.MeshBasicMaterial({ color: 0x333333, transparent: true, opacity: 0.6 })); p.position.copy(position).add(new THREE.Vector3((Math.random() - 0.5) * 8, Math.random() * 5, (Math.random() - 0.5) * 8)); p.velocity = new THREE.Vector3((Math.random() - 0.5) * 1, (Math.random() - 0.5) * 2 + 1, (Math.random() - 0.5) * 1); p.life = 0.8; scene.add(p); particles.push(p); } }, 150);
      }

      let screenShakeIntensity = 0, screenShakeDecay = 5;
      function addScreenShake(intensity) { screenShakeIntensity = Math.max(screenShakeIntensity, intensity); }

      let hasWon = false;
      function triggerVictory() {
        if(hasWon) return;
        hasWon = true;

        gameState.isRunning = false;
        for (let i = 0; i < 8; i++) setTimeout(() => { createExplosion(bossGroup.position.clone().add(new THREE.Vector3((Math.random() - 0.5) * 50, (Math.random() - 0.5) * 50 + 40, (Math.random() - 0.5) * 50)), 0xff4400, 150); }, i * 200);
        document.getElementById("overlay").style.display = "flex";
        document.querySelector("#overlay h1").innerText = "VICTORY";
        document.querySelector("#overlay h1").style.color = "#0f0";
        document.querySelector("#overlay p").innerText = "The Titan Warlord is defeated!";
        document.getElementById("start-btn").style.display = "none";
        document.getElementById("boss-hud").style.display = "none";
        document.getElementById("vignette-overlay").style.opacity = "0";
        controls.unlock();
        sendWinSignalToESP();
      }

      function sendWinSignalToESP() {
        console.log("Triggering Motor 3...");
        fetch("/win3").catch(e => console.log(e));
        setTimeout(() => { window.location.href = "/"; }, 10000);
      }

      let healDrone = null; let healTimer = 0; let lastHpThreshold = 100;
      function createHealDrone() {
        if (healDrone) return;
        const droneGroup = new THREE.Group();
        const bodyGeo = new THREE.SphereGeometry(1.2, 8, 8);
        const bodyMat = new THREE.MeshStandardMaterial({ color: 0x00ff88, emissive: 0x00ff44, emissiveIntensity: 1.5, metalness: 0.5, roughness: 0.2 });
        const droneBody = new THREE.Mesh(bodyGeo, bodyMat); droneGroup.add(droneBody);
        for (let i = 0; i < 4; i++) { const wing = new THREE.Mesh(new THREE.BoxGeometry(0.3, 2, 0.1), new THREE.MeshStandardMaterial({ color: 0x00ccff, emissive: 0x0088ff, emissiveIntensity: 1 })); wing.rotation.z = (i / 4) * Math.PI * 2; wing.position.set(Math.cos((i / 4) * Math.PI * 2) * 1.2, 0, Math.sin((i / 4) * Math.PI * 2) * 1.2); droneGroup.add(wing); }
        const ring = new THREE.Mesh(new THREE.TorusGeometry(1.6, 0.15, 8, 16), new THREE.MeshBasicMaterial({ color: 0x00ff88, transparent: true, opacity: 0.7 })); droneGroup.add(ring);
        droneGroup.position.copy(camera.position).add(new THREE.Vector3(2, 3, -3)); scene.add(droneGroup); healDrone = droneGroup; document.getElementById("heal-indicator").style.opacity = "1"; showMessage("HEALING DRONE DEPLOYED!");
      }

      function removeHealDrone() { if (healDrone) { scene.remove(healDrone); healDrone = null; } document.getElementById("heal-indicator").style.opacity = "0"; }

      function playerTakeDamage(amount) {
        if (!gameState.isRunning || gameState.isInvincible) return;
        gameState.playerHP -= amount; document.getElementById("hp-bar").style.width = Math.max(0, gameState.playerHP) + "%"; const hpPct = gameState.playerHP;
        if (hpPct < 30) { document.getElementById("hp-bar").style.background = "#ff0000"; } else if (hpPct < 70) { document.getElementById("hp-bar").style.background = "#ffaa00"; }
        const vignette = document.getElementById("vignette-overlay");
        if (hpPct <= 10) { vignette.style.opacity = "1"; vignette.style.background = "radial-gradient(ellipse at center, transparent 30%, rgba(200,0,0,0.7) 70%, rgba(150,0,0,0.9) 100%)"; renderer.toneMappingExposure = 0.5; }
        else if (hpPct <= 40) { vignette.style.opacity = "0.7"; vignette.style.background = "radial-gradient(ellipse at center, transparent 40%, rgba(180,0,0,0.5) 75%, rgba(100,0,0,0.7) 100%)"; renderer.toneMappingExposure = 0.65; }
        else if (hpPct <= 70) { vignette.style.opacity = "0.35"; vignette.style.background = "radial-gradient(ellipse at center, transparent 50%, rgba(180,0,0,0.35) 80%, rgba(100,0,0,0.5) 100%)"; renderer.toneMappingExposure = 0.75; }
        else { vignette.style.opacity = "0"; renderer.toneMappingExposure = 0.8; }
        if (hpPct <= 30 && lastHpThreshold > 30) { createHealDrone(); addScreenShake(2); } if (hpPct > 30 && healDrone) { removeHealDrone(); } lastHpThreshold = hpPct;
        const flash = document.getElementById("damage-flash"); flash.style.opacity = "1"; setTimeout(() => (flash.style.opacity = "0"), 200); addScreenShake(amount * 0.3);
        if (hpPct <= 0) { gameState.isRunning = false; gameState.mouseDown = false; document.getElementById("overlay").style.display = "flex"; document.querySelector("#overlay h1").innerText = "YOU DIED"; document.querySelector("#overlay h1").style.color = "#ff0000"; document.querySelector("#overlay p").innerText = "The Titan devours your soul. Refresh to try again."; document.getElementById("start-btn").style.display = "none"; document.getElementById("boss-hud").style.display = "none"; document.getElementById("vignette-overlay").style.opacity = "0"; removeHealDrone(); controls.unlock(); }
      }

      let prevTime = performance.now(); let bossSwingAngle = 0, bossFlailAngle = 0;

      function animate() {
        requestAnimationFrame(animate);
        const time = performance.now();
        const delta = Math.min((time - prevTime) / 1000, 0.1);
        prevTime = time;

        if (gameState.isRunning) {
          const currentWep = weapons[gameState.currentWeapon];
          if (currentWep.beam && gameState.mouseDown) {
            const now = performance.now();
            if (now - lastFireTime >= currentWep.fireRate && !gameState.isReloading && currentWep.ammo > 0 && currentCooldown <= 0) {
              lastFireTime = now; currentWep.ammo--; currentCooldown = currentWep.cooldown; currentCooldownMax = currentWep.cooldown;
              document.getElementById("ammo-count").innerText = currentWep.ammo + " / ∞";
              if (currentWep.ammo <= 0 && currentWep.infinite) reloadWeapon();
              if (!railgunBeam) { railgunBeam = new THREE.Mesh(new THREE.CylinderGeometry(0.12, 0.18, 1, 8), new THREE.MeshBasicMaterial({ color: 0xff00ff, transparent: true, opacity: 0.9, blending: THREE.AdditiveBlending, depthWrite: false })); scene.add(railgunBeam); }
              railgunBeam.visible = true; const beamStart = camera.position.clone(); const beamDir = new THREE.Vector3(); camera.getWorldDirection(beamDir); const beamEnd = beamStart.clone().add(beamDir.clone().multiplyScalar(500)); const midPoint = beamStart.clone().add(beamEnd).multiplyScalar(0.5); railgunBeam.position.copy(midPoint); railgunBeam.scale.y = beamStart.distanceTo(beamEnd); railgunBeam.lookAt(beamEnd); raycaster.setFromCamera(new THREE.Vector2(0, 0), camera); checkBossHit(currentWep); if (secondaryModel) secondaryModel.material.opacity = 1.0;
            }
            if (currentWep.ammo <= 0 && railgunBeam) railgunBeam.visible = false;
          } else if (railgunBeam) { railgunBeam.visible = false; }

          if (isDashing) {
            dashTimer -= delta; const dashDir = new THREE.Vector3(); camera.getWorldDirection(dashDir); dashDir.y = 0; dashDir.normalize();
            const moveX = dashDir.x * dashSpeed * delta, moveZ = dashDir.z * dashSpeed * delta; camera.position.x += moveX; camera.position.z += moveZ;
            if (checkBuildingCollision(camera.position.x, camera.position.z)) { camera.position.x -= moveX; camera.position.z -= moveZ; }
            if (dashTimer <= 0) { isDashing = false; gameState.isInvincible = false; }
          }
          if (dashCooldown > 0) { dashCooldown -= delta; document.getElementById("dash-bar").style.width = Math.max(0, (dashCooldown / dashCooldownMax) * 100) + "%"; if (dashCooldown <= 0) document.getElementById("dash-bar").style.width = "100%"; }

          if (!isDashing) { velocity.x -= velocity.x * 8.0 * delta; velocity.z -= velocity.z * 8.0 * delta; }
          velocity.y -= 9.8 * 60.0 * delta;
          if (!isDashing) {
            direction.z = Number(moveForward) - Number(moveBackward); direction.x = Number(moveRight) - Number(moveLeft); direction.normalize(); const speed = isSprinting ? 600.0 : 300.0;
            if (moveForward || moveBackward) velocity.z -= direction.z * speed * delta;
            if (moveLeft || moveRight) velocity.x -= direction.x * speed * delta;
            controls.moveRight(-velocity.x * delta); controls.moveForward(-velocity.z * delta);
          }
          controls.getObject().position.y += velocity.y * delta; const cp = controls.getObject().position;
          if (!isDashing && checkBuildingCollision(cp.x, cp.z)) { controls.moveRight(velocity.x * delta); controls.moveForward(velocity.z * delta); velocity.x = 0; velocity.z = 0; }
          const arenaRadius = 1100; const distFromCenter = Math.sqrt(cp.x * cp.x + cp.z * cp.z);
          if (distFromCenter > arenaRadius) { const sv = arenaRadius / distFromCenter; cp.x *= sv; cp.z *= sv; }
          if (cp.y < 10) { velocity.y = 0; cp.y = 10; canJump = true; }
          if (screenShakeIntensity > 0) { camera.position.x += (Math.random() - 0.5) * screenShakeIntensity * 0.5; camera.position.y += (Math.random() - 0.5) * screenShakeIntensity * 0.5; screenShakeIntensity -= screenShakeDecay * delta; if (screenShakeIntensity < 0) screenShakeIntensity = 0; }
          weaponGroup.position.lerp(new THREE.Vector3(0, 0, 0), 0.08); if (!gameState.isReloading) weaponGroup.rotation.x = THREE.MathUtils.lerp(weaponGroup.rotation.x, 0, 0.08);
          if (secondaryModel) secondaryModel.material.opacity = Math.max(0, secondaryModel.material.opacity - 0.08);
          if (currentCooldown > 0) { currentCooldown -= delta; document.getElementById("cooldown-bar").style.width = Math.max(0, currentCooldown / currentCooldownMax) * 100 + "%"; if (currentCooldown <= 0) document.getElementById("cooldown-bar").style.width = "100%"; }

          for (let i = rockets.length - 1; i >= 0; i--) {
            const r = rockets[i]; r.position.add(r.velocity.clone().multiplyScalar(delta)); r.life -= delta;
            if (r.glow) { r.glow.position.copy(r.position); r.glow.material.opacity = r.life / 3.5; }
            const bossBodyCenter = bossGroup.position.clone().add(new THREE.Vector3(0, 45 * bossGroup.scale.y, 0)); const distToBoss = r.position.distanceTo(bossBodyCenter); const hitRadius = 40 * Math.max(1, bossGroup.scale.x);
            if (distToBoss < hitRadius) { const impactDamage = bossState.maxHp * 0.2; bossTakeDamage(impactDamage, r.position.clone()); createBlastExplosion(r.position.clone()); addScreenShake(10); showMessage("ROCKET HIT! " + Math.round(impactDamage) + " DMG!"); scene.remove(r); if (r.glow) scene.remove(r.glow); rockets.splice(i, 1); }
            else if (r.life <= 0) { createExplosion(r.position.clone(), 0xff4400, 15); scene.remove(r); if (r.glow) scene.remove(r.glow); rockets.splice(i, 1); }
          }

          if (healDrone && gameState.playerHP > 0) {
            const targetPos = camera.position.clone().add(new THREE.Vector3(2, 3, -3)); healDrone.position.lerp(targetPos, 0.05); healDrone.rotation.y += delta * 3; healDrone.children[2].rotation.z += delta * 2; healTimer += delta;
            if (healTimer > 0.5) { healTimer = 0; gameState.playerHP = Math.min(100, gameState.playerHP + 3); document.getElementById("hp-bar").style.width = gameState.playerHP + "%"; if (gameState.playerHP >= 30) { if (gameState.playerHP < 70) document.getElementById("hp-bar").style.background = "#ffaa00"; else document.getElementById("hp-bar").style.background = "#00ffaa"; } createExplosion(healDrone.position.clone(), 0x00ff88, 5); }
          }

          if (bossState.spawning) {
            bossState.spawnTimer += delta; const t = Math.min(bossState.spawnTimer / 3.0, 1.0); const eased = 1 - Math.pow(1 - t, 3); bossGroup.scale.setScalar(0.1 + eased * (bossState.targetScale - 0.1)); bossGroup.position.y = -50 + eased * 50;
            if (t >= 1.0) { bossState.spawning = false; bossGroup.position.y = 0; }
          } else { bossGroup.scale.setScalar(THREE.MathUtils.lerp(bossGroup.scale.x, bossState.targetScale, 0.02)); }

          bossState.timer += delta; const distToPlayer = camera.position.distanceTo(bossGroup.position); const targetRotation = Math.atan2(camera.position.x - bossGroup.position.x, camera.position.z - bossGroup.position.z); let rotDiff = targetRotation - bossGroup.rotation.y; while (rotDiff > Math.PI) rotDiff -= Math.PI * 2; while (rotDiff < -Math.PI) rotDiff += Math.PI * 2; bossGroup.rotation.y += rotDiff * 3 * delta;

          if (bossState.isChanneling) {
            bossState.channelDuration -= delta; skyBeam.position.x = bossGroup.position.x; skyBeam.position.z = bossGroup.position.z; skyBeamLight.position.x = bossGroup.position.x; skyBeamLight.position.z = bossGroup.position.z; bossGroup.rotation.x = -0.2; document.getElementById("boss-energy-bar").style.width = (1 - bossState.channelDuration / 3.0) * 100 + "%";
            if (Math.random() < 0.5) createExplosion(bossGroup.position.clone().add(new THREE.Vector3((Math.random() - 0.5) * 20, 40 + Math.random() * 30, (Math.random() - 0.5) * 20)), 0xffff00, 3);
            skyBeamLight.intensity = 100 + Math.sin(bossState.channelDuration * 10) * 50;
            if (bossState.channelDuration <= 0) { bossState.isChanneling = false; bossGroup.rotation.x = 0; skyBeam.visible = false; skyBeamLight.visible = false; document.getElementById("boss-energy-bar").style.width = "0%"; const healAmount = bossState.phase === 3 ? 12000 : bossState.phase === 2 ? 8000 : 5000; bossState.hp = Math.min(bossState.maxHp, bossState.hp + healAmount); addScreenShake(5); renderer.toneMappingExposure = 1.2; setTimeout(() => (renderer.toneMappingExposure = 0.8), 600); document.getElementById("boss-hp-bar").style.width = Math.max(0, (bossState.hp / bossState.maxHp) * 100) + "%"; showMessage("TITAN REGENERATED!"); createExplosion(bossGroup.position.clone().add(new THREE.Vector3(0, 50, 0)), 0xffff00, 40); addScreenShake(3); bossState.attackTimer = 0; }
          }

          if (!bossState.isChanneling && !bossState.spawning) {
            const bossSpeed = 20 + bossState.phase * 15; if (distToPlayer > 60) { bossGroup.position.x += Math.sin(targetRotation) * bossSpeed * delta; bossGroup.position.z += Math.cos(targetRotation) * bossSpeed * delta; } const bDist = Math.sqrt(bossGroup.position.x ** 2 + bossGroup.position.z ** 2); if (bDist > 550) { bossGroup.position.x *= 550 / bDist; bossGroup.position.z *= 550 / bDist; }
          }
          bossLight.position.copy(bossGroup.position); bossLight.position.y += 50; bossSwingAngle += delta * (2 + bossState.phase); bossFlailAngle += delta * (3 + bossState.phase); bossState.attackAnimTimer += delta;

          if (!bossState.isChanneling && !bossState.spawning) {
            bossState.attackTimer += delta; const attackCooldown = 4.0 / bossState.phase; const attackRange = 70 + bossState.phase * 20; const cooldownProgress = Math.min(100, (bossState.attackTimer / attackCooldown) * 100); document.getElementById("boss-cooldown-bar").style.width = cooldownProgress + "%";
            if (bossState.attackTimer > attackCooldown && distToPlayer < attackRange) {
              bossState.attackTimer = 0; document.getElementById("boss-cooldown-bar").style.width = "0%";
              if (distToPlayer < 35) { bossState.currentAttack = "sword_slash"; rightArmGroup.rotation.z = -1.5; rightArmGroup.rotation.x = -1.0; showMessage("SWORD SLASH!"); setTimeout(() => { if (gameState.isRunning) { playerTakeDamage(2 + bossState.phase); addScreenShake(1.5); createExplosion(camera.position.clone(), 0xff0000, 10); } }, 300); setTimeout(() => { bossState.currentAttack = "flail_smash"; leftArmGroup.rotation.z = 1.5; leftArmGroup.rotation.x = 1.0; showMessage("FLAIL SMASH!"); setTimeout(() => { if (gameState.isRunning) { playerTakeDamage(2 + bossState.phase); addScreenShake(2); createExplosion(camera.position.clone().add(new THREE.Vector3(0, -2, 0)), 0xff4400, 12); } }, 300); }, 600); }
              else if (distToPlayer < 80) { bossState.currentAttack = "ground_slam"; showMessage("GROUND POUND!"); bossGroup.position.y -= 5; setTimeout(() => { if (gameState.isRunning) { bossGroup.position.y += 5; for (let ring = 0; ring < 3; ring++) setTimeout(() => { for (let a = 0; a < 12; a++) createExplosion(bossGroup.position.clone().add(new THREE.Vector3(Math.cos((a / 12) * Math.PI * 2) * (10 + ring * 15), 0, Math.sin((a / 12) * Math.PI * 2) * (10 + ring * 15))), 0xff6600, 4); }, ring * 150); playerTakeDamage(3 + bossState.phase * 2); addScreenShake(4); } }, 400); }
              else { headGroup.rotation.x = -0.5; for (let fb = 0; fb < 5; fb++) setTimeout(() => { if (gameState.isRunning) { const fp = bossGroup.position.clone().add(new THREE.Vector3(0, 60, 10)); createExplosion(fp, 0xff4400, 8); const tp = camera.position.clone().sub(bossGroup.position).normalize(); createExplosion(fp.clone().add(tp.clone().multiplyScalar(fb * 8)), 0xff2200, 4); playerTakeDamage(bossState.phase); addScreenShake(0.5); } }, fb * 200); setTimeout(() => { headGroup.rotation.x = 0; }, 1000); }
            }
          }

          if (bossState.currentAttack === "none" && !bossState.isChanneling) { rightArmGroup.rotation.z = Math.sin(bossSwingAngle) * 0.6 - 0.3; rightArmGroup.rotation.x = Math.cos(bossSwingAngle * 0.7) * 0.4; leftArmGroup.rotation.z = Math.cos(bossFlailAngle) * 0.5 + 0.3; leftArmGroup.rotation.x = Math.sin(bossFlailAngle * 0.8) * 0.5; if (chainGroup) chainGroup.rotation.z = Math.sin(bossFlailAngle * 1.5) * 0.8; headGroup.rotation.x = 0; }

          if (bossState.phase >= 2 && !bossState.isChanneling) {
            if (bossState.phase >= 3 && Math.random() < 0.003 && distToPlayer < 180) { createExplosion(bossGroup.position.clone().add(new THREE.Vector3(0, 0, 0)), 0xff0000, 50); playerTakeDamage(10); addScreenShake(4); showMessage("GROUND SLAM!"); }
            if (distToPlayer < 20 && !bossState.spawning) playerTakeDamage(delta * 2 * bossState.phase);
          }

          for (let i = particles.length - 1; i >= 0; i--) { const p = particles[i]; p.position.add(p.velocity.clone().multiplyScalar(delta * 60)); p.velocity.y -= 0.15; p.life -= delta * 1.5; p.scale.setScalar(Math.max(0, p.life)); if (p.life <= 0) { scene.remove(p); particles.splice(i, 1); } }
         
          if (!bossState.spawning) { const b = 1 + Math.sin(time * 0.002) * 0.02; bossGroup.scale.x = bossState.targetScale * b; bossGroup.scale.z = bossState.targetScale * b; }
        }
        composer.render();
      }

      animate();
      window.addEventListener("resize", () => {
        camera.aspect = window.innerWidth / window.innerHeight;
        camera.updateProjectionMatrix();
        renderer.setSize(window.innerWidth, window.innerHeight);
        composer.setSize(window.innerWidth, window.innerHeight);
      });
    </script>
  </body>
</html>
)rawliteral";


void setup() {
  Serial.begin(115200);

  // Allow allocation of all timers for ESP32 PWM
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Attach servos to pins
  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);
  servo3.setPeriodHertz(50);
  servo1.attach(servo1Pin, 500, 2400);
  servo2.attach(servo2Pin, 500, 2400);
  servo3.attach(servo3Pin, 500, 2400);

  // Reset all servos to 0 degrees on boot
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("Access your games at: http://");
  Serial.println(WiFi.localIP());

  // --- HTML PAGE ROUTING (Using Content Streaming to prevent memory crashes) ---
 
  server.on("/", HTTP_GET, []() {
    server.setContentLength(sizeof(game1_html) - 1);
    server.send(200, "text/html", "");
    server.sendContent(game1_html);
  });

  server.on("/game2", HTTP_GET, []() {
    server.setContentLength(sizeof(game2_html) - 1);
    server.send(200, "text/html", "");
    server.sendContent(game2_html);
  });

  server.on("/game3", HTTP_GET, []() {
    server.setContentLength(sizeof(game3_html) - 1);
    server.send(200, "text/html", "");
    server.sendContent(game3_html);
  });

  // --- SERVO TRIGGER ENDPOINTS (Handles any type of request, GET or POST) ---

  // Motor 1 Trigger (Triggers on Game 1 Win)
  server.on("/win1", HTTP_ANY, []() {
    Serial.println("Game 1 Won! Rotating Servo 1 to 180 degrees.");
    servo1.write(180);
    server.send(200, "text/plain", "Servo 1 Triggered");
  });

  // Motor 2 Trigger (Triggers on Game 2 Win)
  server.on("/win2", HTTP_ANY, []() {
    Serial.println("Game 2 Won! Rotating Servo 2 to 180 degrees.");
    servo2.write(180);
    server.send(200, "text/plain", "Servo 2 Triggered");
  });

  // Motor 3 Trigger (Triggers on Game 3 Win)
  server.on("/win3", HTTP_ANY, []() {
    Serial.println("Game 3 Won! Rotating Servo 3 to 180 degrees.");
    servo3.write(180);
    server.send(200, "text/plain", "Servo 3 Triggered");
  });

  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
}Interactive-Car-Track-Bot-M2M
