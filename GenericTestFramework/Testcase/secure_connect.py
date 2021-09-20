"""
Author : Venkatesan Madappan
Test Automation Framework
"""

import sys
import os
import time
from time import sleep

from Template.basetest import TestBase


class SecureConnectTest(TestBase):
    """
    Connect TestCase
    """
    def __init__(self):
        super().__init__()
        sys.path.append(os.getcwd())

    def run(self):
        super().run()
        self.dut.get_to_initial_condition()

        TestBase.wait_for_advertisement()

        mytest.dut.send_message("ADVERTISE")

        data = mytest.dut.confirm_message("ADVERTISE_SUCCESSFULL")
        if data:
            self.logger.info(f"====>Advertisement for DIS Application Successfully")
        else:
            self.logger.info("====>Sorry There is some issue in Staring Advertisement")
            self.logger.info("====>Testcase Failed")

        self.logger.info("\n\nWaiting for the Mobile App to Connect with the Board  MAX Duration : 25 Seconds \n")

        mytest.dut.send_message("AUTHENTICATION_CONFIRMED")
        #mytest.dut.send_message("AUTHENTICATION_CANCELED")

        for i in range(100):
            print(".", end="")
            sys.stdout.flush()
            sleep(0.25)
            data = mytest.dut.confirm_message("CONNECT")
            if data:
                self.logger.info("\n====>Mobile APP and NRF Board Connected Successfully")
                self.logger.info("Connect Passed")
                break
        else:
            self.logger.info("\n====>Connection Failed between Mobile APP and NRF Board")
            self.logger.info("\nConnect Failed")

        time.sleep(5)
        mytest.dut.send_message("GET_SECURITY_LEVEL")

        for i in range(10):
            sleep(0.25)
            data = mytest.dut.confirm_message("BT_SECURITY_L4")
            if data:
                self.logger.info("\nSecurity Level is 4\nSecure Connect Test has Passed\n")
                break
        else:
            self.logger.info("\nSecure Connect Test has Failed\n")

        mytest.cleanup()


if __name__ == "__main__":

    sys.path.append(os.getcwd())
    mytest = SecureConnectTest()
    mytest.run()
