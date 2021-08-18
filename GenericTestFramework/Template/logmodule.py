"""
Author : Venkatesan Madappan
Test Automation Framework
"""

import logging


class Log:
    """
    Log Module
    """
    def __init__(self, fname, log_level=logging.DEBUG):
        logging.basicConfig(filename=fname, encoding='utf-8', level=log_level)

    def info(self, msg):
        """
        Information Messages
        :param msg: string formatted message
        :return: None
        """
        logging.info(msg)

    def debug(self, msg):
        """
        Debug Messages
        :param msg: string formatted message
        :return: None
        """
        logging.debug(msg)

    def warn(self, msg):
        """
        Warning Messages
        :param msg:string formatted message
        :return:
        """
        logging.warning(msg)

    def err(self, msg):
        """
        Error Messages
        :param msg: string formatted message
        :return: None
        """
        logging.warning(msg)


if __name__ == "__init__":
    print("Executing the Log Class")
