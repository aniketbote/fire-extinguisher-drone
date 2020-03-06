import requests
import random
import time
import json
while True:
    pload = {}
    humid = []
    temperature = []
    gas = []
    humid.append(random.choice(list(range(40,90))))
    temperature.append(random.choice(list(range(30,36))))
    gas.append(random.uniform(0.0,8.5))
    pload['humid'] = humid
    pload['temperature'] = temperature
    pload['gas'] = gas
    r = requests.post('http://127.0.0.1:5000/ard', json = pload)
    print(r)
    print('Done')
    time.sleep(1)
