"""raspberry.py

This runs on the raspberry pi.
"""
import evdev.ecodes
import pigpio

from kb4gc import arduino


class GPIOController:
    """The controller class for GPIO."""

    def __init__(
            self,
            mapping: arduino.PiMap,
            keyboard_fd: str,
    ) -> None:
        self.mapping = mapping
        self.pi = pigpio.pi()
        self.device = evdev.InputDevice(keyboard_fd)

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

    def run(self) -> None:
        """Runs a loop that looks for keys being pressed and released."""
        for event in self.device.read_loop():
            if event.type == evdev.ecodes.EV_KEY:
                if event.value == evdev.events.KeyEvent.key_down:
                    self.on_press(event.code)
                if event.value == evdev.events.KeyEvent.key_up:
                    self.on_release(event.code)


def main(
        mapping: arduino.PiMap,
        keyboard_fd: str,
) -> None:
    GPIOController(mapping, keyboard_fd).run()
