### Operating Systems Project

This is the source code for our Raspberry Pi project that uses a motion sensor to print different alerts onto a screen to indicate whether someone is home.

- `program.py`: driver file with app logic and sensor config
- `nobody_home.py`: GUI that is triggered when sensor detects no motion
- `somebody_home.py`: GUI that is triggered when sensor detects motion

We run this on our pi using the command `python3 program.py`.