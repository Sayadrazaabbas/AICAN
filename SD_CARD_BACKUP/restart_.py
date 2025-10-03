
import sys
import os 
import RPi.GPIO as GPIO
import time


RESTART_BUTTON = 11
GPIO.setmode(GPIO.BCM)
# GPIO.setup(RESTART_BUTTON, GPIO.IN)
GPIO.setup(RESTART_BUTTON, GPIO.IN, pull_up_down=GPIO.PUD_UP)
elapsed = 0
start= 0
end = 0

def my_callback(channel):
    global start
    global end
    elapsed = 0
    print("Rst button event")
    if GPIO.input(RESTART_BUTTON) == 0:
        start = time.time()
        print("Rst button 0")
    if GPIO.input(RESTART_BUTTON) == 1:
        end = time.time()
        elapsed = end - start
        print("Rst button 1")
        print(elapsed)
        if elapsed >= 2:
            print("restarting...")
            os.execv('/boot/restart_.sh',  [' '])

GPIO.add_event_detect(RESTART_BUTTON, GPIO.BOTH, callback=my_callback, bouncetime=200)

try:
        while True:
            # if GPIO.input(RESTART_BUTTON):
                

            time.sleep(0.2)
except KeyboardInterrupt as e:
    print("Bye Bye ")
    print(str(e))
finally:
    GPIO.cleanup()
