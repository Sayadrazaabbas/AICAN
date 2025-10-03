import time

class Recipe:
    def __init__(self, nvalves = 0, nstates = 0, states = {}, dict = None, file = None):
        if dict:
            print("[DEBUG] I was here ")
            self.nValves = dict['nValves']
            self.nStates = dict['nStates']
            self.states = dict['states']
            self.currValveState = [0] * self.nValves
            
        if dict is None:
            assert len(states['stateList']) == len(states['times'])
            assert len(states['stateList']) == nstates
            self.nValves = nvalves
            self.nStates = nstates
            self.states = states
            self.currValveState = [0] * self.nValves
        try:
            assert len(self.states['stateList']) == len(self.states['times'])
            assert len(self.states['stateList']) == self.nStates
        except AssertionError as e:
            print("Corrupt Recipe, problem might be in the json file")
            del self


    def Run(self):
        
        for i in range(len(self.states['stateList'])):
            self.currValveState = self.states['stateList'][i]
            print("Current State of Valves: ", self.currValveState)
            # time.sleep(self.states['times'][i])
            startTime = time.time()
            while time.time() < startTime + self.states['times'][i]:
                time.sleep(0.1)
            print("Next step after secs: ", self.states['times'][i])
            
        print("End of Recipe")


    def modifyRecipe(self, stateIndex, state = None, time = None, operation = 0):
        try:
            assert len(state) == self.nValves
            if operation == 0: #Edit state at index
                assert stateIndex >= 0 and stateIndex < self.nStates
                assert state is not None
                assert time is not None
                self.states['stateList'][stateIndex] = state
                self.states['times'][stateIndex] = time
            elif operation == 1: # Add new State at index
                assert stateIndex >= 0 and stateIndex <= self.nStates
                assert state is not None
                assert time is not None
                self.states['stateList'].insert(stateIndex, state)
                self.states['times'].insert(stateIndex, time)
            
            elif operation == -1: # remove State from index.
                assert stateIndex >= 0 and stateIndex < self.nStates
                del self.states['stateList'][stateIndex]
                del self.states['times'][stateIndex]
            return self.__dict__
        except:
            print("Invalid Paramenters to function")
            

    @staticmethod
    def createRecipe():
        print("Enter the number of states")
        nvalves = 2
        nstates = int(input())
        states ={
            'stateList' : [],
            'times' : []
        }
        for i in range(nstates):
            print("For state number :", i)
            print("Time period:")
            states['times'].append(int(input()))
            thisState = []
            for j in range(nvalves):
                print("V", j, sep='')
                thisState.append(int(input()))
            states['stateList'].append(thisState)
        return Recipe(nvalves, nstates, states= states)