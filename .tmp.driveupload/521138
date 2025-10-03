from threading import Thread
import time 
import Recipe
import lrdv
import RPi.GPIO as GPIO
VENT_VALVE = 17
VAC_VALVE = 22

class RecipeThread ():
    def __init__(self, dict,mylcd):
        self.running = False
        self.currRecipe = Recipe.Recipe(dict=dict)
        self.paused = False
        self.stopped = True
        self.elapsedTime = 0.0
        self.totalTime = sum(self.currRecipe.states['times'])
        self.currStateNumber = None
        self.mylcd = mylcd
        self.progress=0
        self.kernelrtarTime=0.0
        self.slash="/////////////"
        self.dash="_____________"
        self.refreshDisplayTimer=0.0
        self.aborted = False
        self.completed = False
        self.GPIO = GPIO



    def start(self):
        Thread(target=self.cook, args=()).start()
        print("Total run time is", self.totalTime)
        return self.currRecipe

        

    def cook(self):
        self.running = True
        self.stopped = False
        self.completed = False
        self.aborted = False
        print(self.totalTime)
        self.kernelrtarTime=time.time()
        for i in range(len(self.currRecipe.states['stateList'])):
            self.currStateNumber = i
            self.display_running_state()
            self.display_current_info()
            self.currRecipe.currValveState = self.currRecipe.states['stateList'][i]
            print("Current State of Valves: ", self.currRecipe.currValveState)
            startTime=time.time()
            remainingTime = self.currRecipe.states['times'][i]
            self.refreshDisplayTimer = 0
            self.auto_fire_valves(self.currRecipe.currValveState[0], self.currRecipe.currValveState[1])
            while time.time() < startTime + remainingTime and not self.stopped:
                time.sleep(0.1)

                self.display_progress()
                
                if self.paused:
                    pausedAfter = time.time() - startTime
                    while self.paused and not self.stopped:
                        time.sleep(0.1)
                    remainingTime -= pausedAfter
                    startTime = time.time()
            if self.stopped:
                break

            
        if self.aborted == False:
            self.completed = True    
            self.refreshDisplayTimer = 0
            self.display_progress()
            self.mylcd.lcd_display_string(" Complete",0,5)
            self.mylcd.lcd_display_string(" |Back|     |Home|  ", 3)
        print("End of Recipe")
        self.default_fire_valves()
        self.aborted = False
        self.running = False
        self.stopped = True
    
    def auto_fire_valves(self, V1, V2):
        print("Fire_A")
        if V1 == 1:    
            GPIO.output(VENT_VALVE , GPIO.HIGH)
            print("V1 H")
        elif V1 == 0:
            GPIO.output(VENT_VALVE , GPIO.LOW)
            print("V1 L")

        if V2 == 1:    
            GPIO.output(VAC_VALVE , GPIO.LOW)
            print("V2 H")
        elif V2 == 0:
            GPIO.output(VAC_VALVE , GPIO.HIGH)
            print("V2 L")        

    def default_fire_valves(self):
        GPIO.output(VENT_VALVE , GPIO.HIGH)
        GPIO.output(VAC_VALVE , GPIO.HIGH)

    def switchState(self):
        if self.running:
            self.paused = not self.paused
        

    def abort(self):
        if self.running:
            self.aborted = True
            self.stopped = True
    

    def display_running_state(self):
        if self.running:
            self.mylcd.lcd_display_string(str(self.currStateNumber+1)+"/"+str(len(self.currRecipe.states['stateList'])),0,16)  
        else:
            self.mylcd.lcd_display_string("   ",0,16) 

    def display_progress(self):
        if (time.time()-self.refreshDisplayTimer) >=10:
            self.refreshDisplayTimer=time.time()

            if self.running:
                elapsedTime=time.time() - self.kernelrtarTime
                self.progress = int((elapsedTime/ self.totalTime)*100)
                progressBar=int(self.progress*13/100)

                if self.progress >=100:
                    self.mylcd.lcd_display_string("[/////////////]",2,5)
                    self.mylcd.lcd_display_string("100%",2,0)
                elif self.progress>=0:
                    self.mylcd.lcd_display_string("["+self.slash[0:progressBar]+self.dash[0:(13-progressBar)]+"]",2,5)
                    self.mylcd.lcd_display_string(str(self.progress)+"%",2,0)
                else:
                    self.mylcd.lcd_display_string("[____________]",2,5)
                    self.mylcd.lcd_display_string("100%",2,0)
            else:
                self.mylcd.lcd_display_string("                    ",2)


    def format_sec_to_hhmmss(self, seconds):
        hr=seconds // (60*60)
        seconds %= (60*60)
        minutes = seconds // 60
        seconds %= 60
        return "%02i:%02i:%02i" % (hr, minutes, seconds) 

    def display_current_info(self):
        global kernelr
        self.mylcd.lcd_display_string("                    ",1)
        curr_string = "" 
        for x in self.currRecipe.states['stateList'][self.currStateNumber]:
            curr_string += "OP" if (x == 1) else "CL"
            curr_string += " "
        curr_string += self.format_sec_to_hhmmss(self.currRecipe.states['times'][self.currStateNumber])
        
        self.mylcd.lcd_display_string(curr_string,1,3)

