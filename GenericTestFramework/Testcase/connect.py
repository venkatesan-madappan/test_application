"""
Author : Venkatesan Madappan
Test Automation Framework
"""

import sys
import os
from Template.basetest import TestBase


class ConnectTest(TestBase):
    """
    Connect TestCase
    """
    def __init__(self):
        super().__init__()
        sys.path.append(os.getcwd())

    def run(self):
        super().run()
        print("Send Advertise Command")
        mytest.dut.send_message("ADVERTISE")
        print("Confirm/Response Advertise is received by NRF Board")
        data = mytest.dut.confirm_message("ADVERTISE")
        print(f"Received the ADVERTISE Message is : {data}")
        mytest.cleanup()


if __name__ == "__main__":
    print("Connect Test Case Execution")
    sys.path.append(os.getcwd())
    mytest = ConnectTest()
    mytest.run()
