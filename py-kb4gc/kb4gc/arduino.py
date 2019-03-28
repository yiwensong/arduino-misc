"""arduino.py
Generates the .ino file that goes on the arduino.
"""
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


def create_arduino_file(
        template: str,
        values: typing.Dict[str, int],
        mapping: typing.Dict[str, str],
        gc_output_port: int,
) -> str:
    """Creates the arduino sketch file from a yaml config file."""
    # Create a safe loading dict with only the requisite values
    safe_values = {
        k: values.get(k, v)
        for k, v
        in DEFAULT_VALUES.items()
    }

    keycode_mapping = {
        k: keyboard.KEY_CODES_MAP.get(v, 256)
        for k, v in mapping.items()
    }

    return ENV.get_template(template).render(
        gc_output=gc_output_port,
        **safe_values,
        **keycode_mapping,
    )
