import sys
from PyQt5.QtWidgets import QMainWindow, QApplication
from MainView import *
from customSerial import customSerial

class MyApp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        #object serial
        self.serial = customSerial()
        self.ui.baudrateList.addItems(self.serial.baudratesDIC.keys())
        self.ui.baudrateList.setCurrentText('115200')
        self.ui.typeList.addItems(self.serial.typeDIC.keys())
        self.ui.typeList.setCurrentText('ascii')

        #Events 
        self.ui.connectBtn.clicked.connect(self.connect_serial)
        self.ui.sendBtn.clicked.connect(self.send_data)
        self.ui.updateBtn.clicked.connect(self.update_ports)
        self.ui.clearBtn.clicked.connect(self.clear_terminal)
        self.serial.data_avaliable.connect(self.update_terminal)

    def update_terminal(self, data):
        self.ui.Terminal.append(data)

    def connect_serial(self): 
        if(self.ui.connectBtn.isChecked()):
            port = self.ui.portList.currentText()
            baudrate = self.ui.baudrateList.currentText()
            self.serial.serialPort.port = port
            self.serial.serialPort.baudrate = baudrate
            self.serial.connect_serial()
            #connected
            if(self.serial.serialPort.is_open):
                self.ui.connectBtn.setText("Disconnect")
            else:
                self.ui.connectBtn.setChecked(False)
        else:
            self.ui.connectBtn.setText("Connect")
            self.serial.disconnect_serial()


    def send_data(self):
        data = self.ui.input.text()
        self.serial.send_data(data) 


    def update_ports(self):
        self.serial.update_ports()
        self.ui.portList.addItems(self.serial.portList)

    def clear_terminal(self):
        self.ui.Terminal.clear()

    def closeEvent(self, e):
        self.serial.disconnect_serial()
    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())