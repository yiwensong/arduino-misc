"""raspberry.py

This runs on the raspberry pi.
"""
import pigpio

from kb4gc import arduino


class GPIOController:
    """The controller class for GPIO."""

    def __init__(self, mapping: arduino.PiMap) -> None:
        self.mapping = mapping
        self.pi = pigpio.pi()

    def on_press(self, key_code: int) -> None:
        """Turns on the correct GPIO pin when a corresponding
        key is pressed.
        """
        pin = self.mapping.get(key_code)
        if pin:
            # Set the pin to high
            self.pi.write(pin, 1)

    def on_release(self, key_code: int) -> None:
        """Turns off the correct GPIO pin when a corresponding
        key is released.
        """
        pin = self.mapping.get(key_code)
        if pin:
            # Set the pin to low
            self.pi.write(pin, 0)


def main():
    pass
