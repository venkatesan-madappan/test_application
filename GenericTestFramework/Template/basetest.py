"""
Author : Venkatesan Madappan
Test Automation Framework
"""
import os

from config.configmodule import ConfigModule
from Device.nrfboard import NrfBoard
from Template.logmodule import Log


class TestBase:
    """
    Base Test Class
    """
    def __init__(self):
        filename = os.path.join(os.getcwd(), './config/deviceconfig.json')
        self.config_module = ConfigModule(filename)
        self.config_module.get_config_parameters()
        logfile = os.path.join(os.getcwd(), './log/logfile.txt')
        self.logger = Log(logfile)
        if self.config_module.config_data["Board"] == "NRF5340":
            self.dut = NrfBoard()
        else:
            assert True, "Unknown Device, unable to create device Object"
        self.logger.info("TestCase Base")

    def run(self):
        """
        Generic Method to run the test
        :return:
        """
        self.dut.create_device_and_transport(self.config_module.config_data)
        self.logger.info("Run the Test Case")

    def cleanup(self):
        """
        Clean up method
        :return: None
        """
        self.dut.cleanup()


if __name__ == "__main__":
    print("Test Framework Main Test base")
