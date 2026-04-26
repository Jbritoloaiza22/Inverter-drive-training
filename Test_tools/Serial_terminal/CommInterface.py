import serial
import time

# setting port
PORT = "COM5"      # depend of your own port
BAUD = 115200

def main():
    try:
        ser = serial.Serial(PORT, BAUD, timeout=1)
        print(f"Conectado a {PORT} @ {BAUD}")
    except Exception as e:
        print("Port open error:", e)
        return

    time.sleep(2)  # wait to stabilize connection

    try:
        while True:
            # send
            #ser.write(b"Hello STM32\r\n")
            #print("Sending: Hello STM32")

            # read
            if ser.in_waiting:
                data = ser.readline().decode(errors="ignore")
                print("Received:", data.strip())

            time.sleep(1)

    except KeyboardInterrupt:
        print("\nClosing port...")
        ser.close()

if __name__ == "__main__":
    main()