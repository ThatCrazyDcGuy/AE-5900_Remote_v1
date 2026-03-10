import serial
import time
from flask import Flask, render_template, jsonify

app = Flask(__name__)

SERIAL_PORT = '/dev/ttyACM0' 
BAUD_RATE = 9600


try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    time.sleep(2)  
    print("Verbindung zum Arduino hergestellt.")
except Exception as e:
    print(f"Fehler: Konnte Serial Port nicht öffnen: {e}")
    ser = None

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/cmd/<cmd>')
def send_command(cmd):
    if not ser:
        return jsonify({"error": "Serial nicht verbunden"}), 500

    
    ser.write(cmd.upper().encode())
    

    time.sleep(0.1) 
    

    response = ser.readline().decode('utf-8', errors='ignore').strip()
    

    while response and not response.startswith("STATUS|"):
        response = ser.readline().decode('utf-8', errors='ignore').strip()
    
    return jsonify({"radio_resp": response})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
