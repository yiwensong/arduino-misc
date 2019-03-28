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
    with open(config_file, 'r') as cfg_fd:
        config = yaml.safe_load(cfg_fd)

    for check in (
            'mapping',
            'values',
            'hardware',
    ):
        if check not in config:
            raise InvalidConfigException(
                check,
                config_file,
            )
    config['mapping'] = {
        k: str(v)
        for k, v in config['mapping'].items()
    }
    return config
