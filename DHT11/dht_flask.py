from flask import Flask
from flask import request, jsonify
from collections import deque

# http://192.168.29.242:5000/ard
# http://127.0.0.1:5000/hello
app = Flask(__name__)

humidity = []
temperature = []




@app.route('/ard', methods = ['POST'])
def dht_humid():
    content = request.get_json()
    humidity.append(content['humid'])
    temperature.append(content['temperature'])
    print(content)
    return 'JSON posted'

@app.route('/take')
def dht_response():
    dtemp = {}
    if len(humidity) != 0:
        htemp = humidity.pop(0)
        ttemp = temperature.pop(0)
        dtemp['humidity'] = htemp
        dtemp['temperature'] = ttemp
        return jsonify(dtemp)
    else:
        return 'NULL'



@app.route('/hello')
def hello():
    return 'It is working'

<<<<<<< HEAD
if __name__ == "__main__":
    app.run(host='0.0.0.0', port= 5000, debug = True)
=======
app.run(host='192.168.43.184', port= 5000, debug = True)
>>>>>>> 0f76fc8d52308d9d7cf2fa5fe776b43f2362a3e8
