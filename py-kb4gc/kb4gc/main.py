"""main.py

This is the entry point of the codegen script.
"""
import argparse
import os

from kb4gc import arduino
from kb4gc import config


def run(
        cfg_file: str = 'config.yaml',
        output_dir: str = 'build',
) -> str:
    configs = config.load_config(cfg_file)
    mapping = configs['mapping']
    values = configs['values']
    gc_output = configs['hardware'].get('gc_output', 8)
    files = {
        template: arduino.create_arduino_file(
            template,
            values,
            mapping,
            gc_output,
        ) for template in (
            'controller.h',
            'controller.c',
            'kb4gc.ino',
        )
    }

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for template, content in files.items():
        with open(os.path.join(output_dir, template), 'w') as out_file:
            out_file.write(content)
    return output_dir


def main():
    parser = argparse.ArgumentParser(description='Make some templates')
    parser.add_argument(
        '--config',
        default='config.yaml',
        help='path to the config file',
    )
    parser.add_argument(
        '--output',
        default='build',
        help='path to the output directory',
    )
    args = parser.parse_args()
    run(
        args.config,
        args.output,
    )


if __name__ == '__main__':
    main()
