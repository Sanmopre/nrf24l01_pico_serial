import serial
import time

# Replace '/dev/ttyACM0' with the correct port for your Pico
pico_port = "/dev/ttyACM0"
baud_rate = 115200

# Open the serial connection
with serial.Serial(pico_port, baud_rate, timeout=1) as ser:
    time.sleep(2)  # Wait for the connection to establish

    # Send a command to the Pico
    #ser.write(b"4\n")  # Request temperature
    #print("Sent command: 4")

    # Wait and read response from Pico
    while True:
        response = ser.readline().decode('utf-8').strip()  # Read a line of data
        if response:
            print(f"Received: {response}")