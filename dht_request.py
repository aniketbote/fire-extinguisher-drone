import requests
import random
import time
import json
while True:
    pload = {}
    humid = []
    temperature = []
    count = 0
    while count <= 10:
        humid.append(random.choice(list(range(30,36))))
        temperature.append(random.choice(list(range(40,90))))
        count += 1
    pload['humid'] = humid
    pload['temperature'] = temperature
    r = requests.post('http://127.0.0.1:5000/ard', json = pload)
    # print(r)
    # print('Done')
    time.sleep(5)
