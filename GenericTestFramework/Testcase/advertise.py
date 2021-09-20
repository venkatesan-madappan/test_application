"""
Author : Venkatesan Madappan
Test Automation Framework
"""

import sys
import os
from time import sleep

from Template.basetest import TestBase


class AdvertiseTest(TestBase):
    """
    Advertise TestCase
    """
    def __init__(self):
        super().__init__()
        sys.path.append(os.getcwd())

    def run(self):
        super().run()
        self.dut.get_to_initial_condition()

        TestBase.wait_for_advertisement()

        mytest.dut.send_message("ADVERTISE")
        sleep(0.25)
        data = mytest.dut.confirm_message("ADVERTISE_SUCCESSFULL")
        if data :
            self.logger.info(f"====>Advertisement for DIS Application Successfully")
            self.logger.info(f" Testcase Passed")
        else:
            self.logger.info("====>Sorry There is some issue in Staring Advertisement")
            self.logger.info("====>Testcase Failed")

        mytest.cleanup()


if __name__ == "__main__":

    sys.path.append(os.getcwd())
    mytest = AdvertiseTest()
    mytest.run()
