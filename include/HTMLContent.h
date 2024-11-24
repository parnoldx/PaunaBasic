#pragma once

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Pauna Scale Settings</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 10px;
            background-color: #121212;
            color: #e0e0e0;
        }
        
        .container {
            max-width: 600px;
            margin: 0 auto;
            background: #1e1e1e;
            padding: 15px;
            border-radius: 10px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.3);
        }
        
        h1 {
            color: #ffffff;
            text-align: center;
            margin: 0 0 15px 0;
            font-size: 1.5rem;
        }
        
        .gradient-section {
            background: linear-gradient(to right, #2c5282, #553c9a);
            padding: 1rem;
            border-radius: 0.75rem;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.2);
            margin-bottom: 1rem;
            text-align: center;
        }
        
        .section-label {
            color: white;
            font-size: 0.75rem;
            margin-bottom: 0.25rem;
            text-transform: uppercase;
        }
        
        .section-content {
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 0.5rem;
            margin: 0.5rem 0;
        }
        
        .input-group {
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 0.5rem;
            width: 100%;
            max-width: 400px;
        }
        
        .reading-value {
            font-size: 2rem;
            font-weight: bold;
            color: white;
        }
        
        .reading-unit {
            font-size: 1rem;
            color: white;
            margin-left: 0.25rem;
        }
        
        .section-divider {
            height: 2px;
            background: rgba(255, 255, 255, 0.2);
            width: 75%;
            margin: 0.25rem auto 0.5rem;
        }
        
        input[type="number"], input[type="range"] {
            padding: 6px;
            border: 1px solid rgba(255, 255, 255, 0.3);
            border-radius: 4px;
            box-sizing: border-box;
            background: rgba(255, 255, 255, 0.1);
            color: #ffffff;
        }

        input[type="number"] {
            width: 120px;
        }
        
        input[type="range"] {
            flex: 1;
            max-width: 200px;
        }
        
        button {
            background-color: rgba(255, 255, 255, 0.15);
            color: white;
            padding: 8px 15px;
            border: 1px solid rgba(255, 255, 255, 0.3);
            border-radius: 4px;
            cursor: pointer;
            font-size: 0.9rem;
            transition: background-color 0.2s;
            white-space: nowrap;
        }
        
        button:hover {
            background-color: rgba(255, 255, 255, 0.25);
        }
        
        #finish {
            background-color: #c53030;
            border: none;
            margin-top: 10px;
            width: 100%;
        }
        
        #finish:hover {
            background-color: #9b2c2c;
        }
        
        .status {
            display: none;
            text-align: center;
            color: #48bb78;
            margin-top: 3px;
            font-size: 0.8rem;
        }
        
        #standbyValue {
            color: white;
            font-size: 1.25rem;
            font-weight: bold;
            min-width: 90px;
        }
        
        .logo-container {
            max-width: 300px;
            margin: 0 auto 10px;
        }
        .logo-container svg {
            width: 100%;
            height: 100%;
            transform: scale(0.8);
        }

        .warning-note {
            text-align: center;
            color: #fc8181;
            margin: 1rem 0;
            padding: 0.75rem;
            border: 1px solid #fc8181;
            border-radius: 0.5rem;
            font-size: 0.9rem;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="logo-container">
            <svg viewBox="-5 -5 147.5 60" style="transform: scale(0.8);">
                <defs>
                    <style>
                        @keyframes dotOutline {
                            0%, 100% { stroke-opacity: 0.2; }
                            50% { stroke-opacity: 1; }
                        }
                        .dot-outline {
                            animation: dotOutline 3s infinite ease-in-out;
                        }
                        .dot-outline2 {
                            animation: dotOutline 3s infinite ease-in-out;
                            animation-delay: 1.5s;
                        }
                    </style>
                </defs>
                
                <rect x="-5" y="-5" width="147.5" height="60" fill="#121212" rx="10" ry="10"/>
                <circle cx="25" cy="25" r="17.5" fill="white"/>
                
                <path d="M 18.5 25 Q 25 17.5 31.5 25" stroke="#121212" fill="none" stroke-width="1.5"/>
                
                <circle cx="17.5" cy="25" r="1.75" fill="#121212"/>
                <circle cx="32.5" cy="25" r="1.75" fill="#121212"/>
                
                <circle cx="17.5" cy="25" r="2.25" fill="none" stroke="#121212" stroke-width="0.5" class="dot-outline"/>
                <circle cx="32.5" cy="25" r="2.25" fill="none" stroke="#121212" stroke-width="0.5" class="dot-outline2"/>
                
                <text x="55" y="32.5" fill="white" font-family="Futura, 'Trebuchet MS', sans-serif" font-weight="500" font-size="21" letter-spacing="2">PAUNA</text>
            </svg>
        </div>
        
        <div class="gradient-section">
            <div class="section-label">CURRENT WEIGHT</div>
            <div class="section-content">
                <div>
                    <span id="readingValue" class="reading-value">0.00</span>
                    <span class="reading-unit">g</span>
                </div>
            </div>
            <div class="section-divider"></div>
        </div>
        
        <div class="gradient-section">
            <div class="section-label">CALIBRATION WEIGHT</div>
            <div class="section-content">
                <div class="input-group">
                    <input type="number" id="weight" min="0" step="0.1" value="" placeholder="g">
                    <button onclick="setCalibration()">Set Calibration</button>
                </div>
            </div>
            <div class="section-divider"></div>
            <div id="calStatus" class="status">Calibration saved!</div>
        </div>
        
        <div class="gradient-section">
            <div class="section-label">STANDBY TIME</div>
            <div class="section-content">
                <div class="input-group">
                    <div id="standbyValue">2 min</div>
                    <input type="range" id="standby" min="1" max="15" value="2" oninput="updateStandbyValue(this.value)">
                    <button onclick="setStandby()">Set Standby Time</button>
                </div>
            </div>
            <div class="section-divider"></div>
            <div id="standbyStatus" class="status">Standby time saved!</div>
        </div>

        <div class="warning-note">
            ⚠️ Please remove the calibration weight before finishing setup
        </div>
        
        <button id="finish" onclick="finishSetup()">Finish Setup</button>
    </div>

    <script>
        function updateStandbyValue(val) {
            document.getElementById('standbyValue').innerHTML = val + ' min';
        }

        function showStatus(elementId) {
            const status = document.getElementById(elementId);
            status.style.display = 'block';
            setTimeout(() => {
                status.style.display = 'none';
            }, 1000);
        }

        function setCalibration() {
            const weight = document.getElementById('weight').value;
            fetch('/setCalibration?weight=' + weight)
                .then(response => response.text())
                .then(data => showStatus('calStatus'));
        }

        function setStandby() {
            const standby = document.getElementById('standby').value;
            fetch('/setStandby?min=' + standby)
                .then(response => response.text())
                .then(data => showStatus('standbyStatus'));
        }

        function finishSetup() {
            fetch('/finish')
                .then(response => response.text())
                .then(data => {
                    alert('Setup complete! Device will restart.');
                });
        }

        function updateReading() {
            fetch('/get-reading')
                .then(response => response.json())
                .then(data => {
                    document.getElementById('readingValue').textContent = data.reading.toFixed(2);
                });
        }

        setInterval(updateReading, 100);

        fetch('/getValues')
            .then(response => response.json())
            .then(data => {
                document.getElementById('standby').value = data.standby;
                updateStandbyValue(data.standby);
            });
    </script>
</body>
</html>
)rawliteral";