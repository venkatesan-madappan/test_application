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
        "AUTH_CONFIRM": "AUTH_CONFIRM",
        "AUTHENTICATION_CONFIRMED": "AUTHENTICATION_CONFIRMED",
        "AUTHENTICATION_CANCELED": "AUTHENTICATION_CANCELED",
        "LEGACY_PAIRING": "LEGACY_PAIRING",
        "CLEAR_BONDING": "CLEAR_BONDING",
        "GET_SECURITY_LEVEL": "GET_SECURITY_LEVEL",
        "BT_SECURITY_L1": "BT_SECURITY_L1",
        "BT_SECURITY_L4": "BT_SECURITY_L4",

        "CONNECT": "CONNECT",
        "CONNECT_SUCCESSFUL": "CONNECT_SUCCESSFUL",
        "DISCONNECT": "DISCONNECT",
        "DISCONNECT_SUCCESSFUL": "DISCONNECT_SUCCESSFUL"
        }

    @staticmethod
    def data_serialize(data):
        return bytes(Messages.primitives[data]+'\r', 'utf-8')
