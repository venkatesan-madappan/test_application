"""
Author : Venkatesan Madappan
Test Automation Framework
"""
from threading import Thread, Event
from queue import Queue
from Transport.transport import Transport
import serial


class SerialTransport(Transport):
    """
    Serial Port Class
    """
    def __init__(self, port):
        self.port_no = port
        self.ser_ins = None
        self.read_thread = None
        self.msgq = Queue()
        self.exit_reading = Event()

    def serial_thread_read(self):
        """
        Serial Thread function to read data from Queue
        :return:
        """
        while not self.exit_reading.isSet():
            data = self.ser_ins.read()
            self.msgq.put(data)

    def open(self):
        """
        Open the Serial Port
        :return: None
        """
        self.ser_ins = serial.Serial()
        self.ser_ins.port = self.port_no
        self.ser_ins.baudrate = 115200
        self.ser_ins.open()
        self.read_thread = Thread(target=self.serial_thread_read, args=())
        self.read_thread.start()

    def send(self, data):
        """
        Send Message to target board
        :param data: bytes to send
        :return: None
        """
        self.ser_ins.write(data)

    def receive(self):
        """
        Complete pending messages from Queue
        :return:
        """
        received_data = []
        while not self.msgq.empty():
            data = self.msgq.get(1).decode('utf-8')
            received_data.append(data)
        return ''.join(received_data)

    def clean_received_messages(self):
        """
        Complete pending messages from Queue
        :return:
        """
        while not self.msgq.empty():
            data = self.msgq.get(1).decode('utf-8')

    def confirm_message(self, msg):
        """
        Confirm given Messge is being received or not
        :param msg: Message
        :return: the bool value received or not
        """
        data = None
        msg_check = ""
        msg_found = False
        try:
            while not self.msgq.empty():
                data = self.msgq.get(1).decode('utf-8')
                if data is not None:
                    ascii_data = ord(data)
                    if ascii_data == 10 or ascii_data == 13:
                        if ascii_data == 10:
                            if msg == msg_check:
                                msg_found = True
                                break
                            else:
                                msg_check = ""
                    else:
                        msg_check = msg_check+data
            #else:
                #print("Seems like we have reached the Empty")
                #print(f"Message is  : {msg_check} : {msg_found}")

        except Exception as e:
            print("There is an Exception "+str(e))
            pass
        return msg_found, msg_check

    def cleanup(self):
        """
        Clean up function
        :return: None
        """
        self.exit_reading.set()
        self.ser_ins.close()


if __name__ == "__init__":
    print("Executing the Serial Transport Class")
