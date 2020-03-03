from flask import Flask
from flask import request
#http://192.168.29.242:5000/ard
app = Flask(__name__)

humidity = []
temperature = []
@app.route('/ard', methods = ['POST'])
def dht_humid():
    content = request.get_json()
    # humidity = humidity + content['temperature']
    # print (content['temperature'])
    print (content)
    return 'JSON posted'

app.run(host='0.0.0.0', port= 5000, debug = True)
