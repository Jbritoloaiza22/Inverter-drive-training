import serial, serial.tools.list_ports
from threading import Thread, Event
from PyQt5.QtCore import QObject,pyqtSignal,pyqtSlot
class customSerial(QObject):
    data_avaliable = pyqtSignal(str)
    
    def __init__(self):
        super().__init__()
        self.serialPort = serial.Serial()
        self.serialPort.timeout = 0.5
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
        self.serialPort.timeout = 0.5
        self.typeDIC= {
            'ascii': 1,
            'hex': 2
        }
        self.portList = []

        #thread 
        self.thread = None
        self.alive = Event()

    def update_ports(self):
        self.portList = [port.device for port in serial.tools.list_ports.comports()]
        print("Available ports:", self.portList)

    def connect_serial(self):
        try:
            self.serialPort.open()
        except serial.SerialException as e:
            print("NO PORT SELECTED OR PORT IS NOT AVAILABLE")
        if(self.serialPort.is_open):
            self.start_thread()

    def disconnect_serial(self):
        self.stop_thread()
        self.serialPort.close()
    
    def read_serial(self):
        while (self.serialPort.is_open and self.alive.isSet()):
            data = self.serialPort.readline().decode('utf-8').strip()
            if(len(data) > 1):
                self.data_avaliable.emit(data)

    def send_data(self, data):
        if(self.serialPort.is_open):
            self.serialPort.write(data.encode('utf-8'))

    def start_thread(self):
        self.thread = Thread(target = self.read_serial)
        self.thread.setDaemon(True)
        self.alive.set()
        self.thread.start()

    def stop_thread(self):
        if(self.thread is not None):
            self.alive.clear()
            self.thread.join()
            self.thread = None

    

    
