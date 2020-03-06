import requests
import random
import time
import json
while True:
    pload = {}
    humid = random.choice(list(range(40,90)))
    temperature = random.choice(list(range(30,36)))
    pload['humid'] = humid
    pload['temperature'] = temperature
    r = requests.post('http://127.0.0.1:5000/ard', json = pload)
    print(r)
    print('Done')
    time.sleep(1)
