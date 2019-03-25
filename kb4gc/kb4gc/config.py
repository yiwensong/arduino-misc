"""config.py

Loads the config to set up the controls.
"""
import textwrap
import typing

import yaml


class InvalidConfigException(Exception):
    def __init__(self, missing: str, config_file: str) -> None:
        super().__init__(
            textwrap.dedent(
                f'''
                Config expects {missing} to be present. Please make sure that
                all {missing} is present in {config_file}.
                '''
            ),
        )


def load_config(config_file: str) -> typing.Dict:
    """Reads the config file and creates a dictionary output."""
    config = yaml.safe_load(config_file)

    for check in ('mapping', 'wiring', 'values'):
        if check not in config:
            raise InvalidConfigException(
                check,
                config_file,
            )
    return config
