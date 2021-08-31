"""
Author : Venkatesan Madappan
Test Automation Framework
"""


class Messages:
    """
    Message for Communication with the Board
    """
    primitives = {
        "ADVERTISE": "ADVERTISE",
        "ADVERTISE_STOP": "ADVERTISE_STOP",
        "ADVERTISE_STOP_SUCCESSFULL": "ADVERTISE_STOP_SUCCESSFULL",
        "ADVERTISE_SUCCESSFUL": "ADVERTISE_SUCCESSFUL",
        "CONNECT": "CONNECT",
        "CONNECT_SUCCESSFUL": "CONNECT_SUCCESSFUL",
        "DISCONNECT": "DISCONNECT",
        "DISCONNECT_SUCCESSFUL": "DISCONNECT_SUCCESSFUL"
        }

    @staticmethod
    def data_serialize(data):
        return bytes(Messages.primitives[data]+'\r', 'utf-8')
