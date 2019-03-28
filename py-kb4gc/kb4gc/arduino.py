"""arduino.py

Generates the .ino file that goes on the arduino.
"""
import textwrap
import typing

import jinja2

from kb4gc import keyboard

DEFAULT_VALUES = {
    'x1v': 44,
    'x2v': 53,
    'x3v': 73,
    'y1v': 37,
    'y2v': 55,
    'y3v': 73,
}
ENV = jinja2.Environment(
    loader=jinja2.PackageLoader('kb4gc', 'templates'),
    variable_start_string='{$',
    variable_end_string='$}',
)

PiMap = typing.Dict[int, int]
ArduinoMap = typing.Dict[str, int]


class InsufficientWiringException(Exception):
    pass


def create_hardware_map(
        wiring: typing.Dict[int, int],
        mapping: typing.Dict[str, str],
) -> typing.Tuple[ArduinoMap, PiMap]:
    """Creates a map of keycode to GPIO and a corresponding
    map of input pin to GC signal.
    """
    if len(wiring) < len(mapping):
        raise InsufficientWiringException(
            textwrap.dedent(
                '''
                There were more buttons mapped than wiring specifications to
                support them. Add more wiring for this to work.
                '''
            ),
        )
    arduino_mapping: ArduinoMap = {}
    pi_mapping: PiMap = {}
    for gc_button, keyname, gpio, ardpin in zip(
            *list(mapping.items()),
            *list(wiring.items()),
    ):
        keycode = keyboard.KEY_CODES_MAP[keyname]
        arduino_mapping[gc_button] = ardpin
        pi_mapping[keycode] = gpio
    return arduino_mapping, pi_mapping


def create_arduino_sketch(
        values: typing.Dict[str, int],
        hardware_map: ArduinoMap,
        gc_output_port: int,
) -> str:
    """Creates the arduino sketch file from a yaml config file."""
    # Create a safe loading dict with only the requisite values
    safe_values = {
        k: values.get(k, v)
        for k, v
        in DEFAULT_VALUES.items()
    }
    return ENV.get_template('kb4gc.ino').render(
        gc_output=gc_output_port,
        **safe_values,
        **hardware_map,
    )
