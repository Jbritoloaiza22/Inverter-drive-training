import sys
from PyQt5.QtWidgets import QMainWindow, QApplication
from MainView import *

class MyApp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        #Events 
        self.ui.connectBtn.clicked.connect(self.connect_serial)
        self.ui.sendBtn.clicked.connect(self.send_data)
        self.ui.updateBtn.clicked.connect(self.update_ports)

    def connect_serial(self):
        print("Connect button clicked")

    def send_data(self):
        print("Sending")

    def read_data(self):
        print("Reading")

    def update_ports(self):
        print("Updating ports")

    


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())