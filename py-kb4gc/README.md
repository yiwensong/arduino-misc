# kb4gc
_______

Turns your keyboard into a gamecube controller
_______

## Developer notes:
* curses and other terminal tools cannot capture the full keyboard
experience. We need a non-terminal app to capture the keyboard in
the so-called "raw mode".
* one possible way is to capture keystrokes in webapp, but it is
not clear if that will create too much latency
* write some tests, we need to make sure somehow that the .ino file
generated is compilable
* there should probably be a CLI tool to configure stuff and load things
