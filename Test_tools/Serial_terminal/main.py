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

        #Events 
        self.ui.connectBtn.clicked.connect(self.connect_serial)
        self.ui.sendBtn.clicked.connect(self.send_data)
        self.ui.updateBtn.clicked.connect(self.update_ports)
        self.ui.clearBtn.clicked.connect(self.clear_terminal)

    def connect_serial(self): 
        print("Connect button clicked")

    def send_data(self):
        print("Sending")


    def update_ports(self):
        self.serial.update_ports()
        self.ui.portList.addItems(self.serial.portList)

    def clear_terminal(self):
        print("Clearing terminal")
    

    


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())