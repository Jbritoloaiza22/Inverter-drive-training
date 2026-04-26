import serial, serial.tools.list_ports


class customSerial(object):
    def __init__(self):
        super().__init__()
        self.serialPort = serial.Serial()

        self.baudratesDIC = {
            '1200': 1200,
            '2400': 2400,
            '4800': 4800,
            '9600': 9600,
            '19200': 19200,
            '38400': 38400,
            '57600': 57600,
            '115200': 115200,
            '230400': 230400,
            '460800': 460800,
            '921600': 921600
        }

        self.portList = []

    def update_ports(self):
        self.portList = [port.device for port in serial.tools.list_ports.comports()]
        print("Available ports:", self.portList)

    def connect_serial(self):
        try:
            self.serialPort.open()
        except serial.SerialException as e:
            print("NO PORT SELECTED OR PORT IS NOT AVAILABLE")

    def disconnect_serial(self):
        self.serialPort.close()
        print("Disconnected")
    
    def read_serial(self):
        pass

    def send_data(self, data):
        print("Sending:", data)

    

    
