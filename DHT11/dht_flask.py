from flask import Flask
from flask import request, jsonify, render_template
from collections import deque
import time

# http://192.168.29.242:5000/ard
# http://127.0.0.1:5000/hello
app = Flask(__name__)

humidity = []
temperature = []
gas = []
count = 0


@app.route('/', methods=["GET", "POST"])
def main():
    return render_template('index.html')


@app.route('/ard', methods = ['POST'])
def dht_humid():
    content = request.get_json()
    humidity.append(content['humid'][0])
    temperature.append(content['temperature'][0])
    gas.append(content['gas'][0])
    print(content)
    return 'JSON posted'

@app.route('/data')
def dht_response():
    global count
    response = []
    while len(humidity) == 0:
        time.sleep(1)
    if len(humidity) != 0:
        htemp = humidity.pop(0)
        ttemp = temperature.pop(0)
        gtemp = gas.pop(0)
        response.append(count)
        response.append(ttemp)
        response.append(htemp)
        response.append(gtemp)
        count += 1
        print(response)
        return jsonify(response)



@app.route('/hello')
def hello():
    return 'It is working'


if __name__ == "__main__":
    app.run(host='0.0.0.0', port= 5000, debug = True)
