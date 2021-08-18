"""
Author : Venkatesan Madappan
Test Automation Framework
"""

import json


class ConfigModule:
    """
    Configuration Module
    """
    def __init__(self, filename):
        self.config_file = filename
        self.config_data = None

    def get_config_parameters(self):
        """
        Read the Config Data from Json file
        :return: None
        """
        with open(self.config_file, ) as file_ptr:
            self.config_data = json.load(file_ptr)


if __name__ == "__main__":
    print("Config Module Class")
    cm = ConfigModule('deviceconfig.json')
    cm.get_config_parameters()
    print("Config Data Value is ", cm.config_data)
