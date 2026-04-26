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
        self.ui.clearBtn.clicked.connect(self.clear_terminal)

    def connect_serial(self):
        print("Connect button clicked")

    def send_data(self):
        print("Sending")


    def update_ports(self):
        print("Updating ports")

    def clear_terminal(self):
        print("Clearing terminal")
    

    


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())