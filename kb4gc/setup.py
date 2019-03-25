"""setup.py"""
import setuptools

with open('README.md', 'r') as readme:
    README_TEXT = readme.read()

    setuptools.setup(
        name='kb4gc',
        version='0.0.1',
        license='MIT',
        author='yiwen song',
        author_email='songzgy@gmail.com',
        url='https://github.com/yiwensong/arduino-misc/kb4gc',
        description=(
            'Use a keyboard as a gamecube controller.'
        ),
        long_description=README_TEXT,
        long_description_content_type='text/markdown',
        packages=setuptools.find_packages(exclude=['tests*']),
        install_requires=[],
        classifiers=[
            'Natural Language :: English',
            'Programming Language :: Python :: 3.7',
            'License :: OSI Approved :: MIT License',
        ],
        entry_points={
        },
    )
