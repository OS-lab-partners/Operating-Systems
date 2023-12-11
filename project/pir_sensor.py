import RPi.GPIO as GPIO
import time

# Set the GPIO mode to BCM
GPIO.setmode(GPIO.BCM)

# Define the GPIO pin connected to the PIR sensor's output
pir_pin = 17

# Configure the pin as an input
GPIO.setup(pir_pin, GPIO.IN)

try:
    print("PIR Motion Sensor Test (Ctrl+C to exit)")
    time.sleep(2)  # Allow the sensor to stabilize

    while True:
        if not GPIO.input(pir_pin):
            print("No motion detected.")
        else:
            print("Motion detected!")

        time.sleep(1)  # Delay between readings

except KeyboardInterrupt:
    print("\nExiting...")
finally:
    GPIO.cleanup()
