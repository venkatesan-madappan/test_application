"""
Author : Venkatesan Madappan
Test Automation Framework
"""
from time import sleep
from Transport.serialtransport import SerialTransport
from Protocol.message import Messages
from Device.device import Device



class NrfBoard(Device):
    """
    NRFBoard Module
    """
    def __init__(self):
        super().__init__()
        self.transport = None
        #print("Device Class")

    def create_device_and_transport(self, config_param):
        """
        Create the NRFBoard and Serial Interface Transport
        :param config_param: Json configuration parameters
        :return: None
        """
        if config_param["Transport"] == "Serial":
            self.transport = SerialTransport(config_param["PortNumber"])
        self.transport.open()
        sleep(0.01)

    def get_to_initial_condition(self):
        self.send_message("ADVERTISE_STOP")
        data = self.confirm_message("ADVERTISE_STOP_SUCCESSFULL")
        if data:
            print("Set to Initial Condition")
        else:
            print("Something went wrong")

    def send_message(self, msgstr):
        """
        Send the Message to NRF Board
        :param msgstr: Message String
        :return: None
        """
        if msgstr in Messages.primitives.keys():
            message_val = Messages.data_serialize(msgstr)
            self.transport.send(message_val)
        sleep(0.001)

    def receive_message(self):
        """
        Receive the Message from NRF Board through Serial Interface
        :return: Received bytes
        """
        return self.transport.receive()

    def clean_received_messages(self):
        """
        Clear the Received the Messages from NRF Board through Serial Interface
        :return: Received bytes
        """
        return self.transport.clean_received_messages()

    def confirm_message(self, msgstr):
        """
        Confirm the expected message has been received form Board or not
        :param msgstr: Message to receive from Board
        :return:
        """
        found = False
        found, msg = self.transport.confirm_message(msgstr)

        return found

    def cleanup(self):
        """
        Clean up function
        :return: None
        """
        self.transport.cleanup()


if __name__ == "__init__":
    print("Executing the Device Class")
