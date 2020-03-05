from flask import Flask
from flask import request
# http://192.168.29.242:5000/ard
# http://127.0.0.1:5000/hello
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

@app.route('/hello')
def hello():
    return 'It is working'

app.run(host='192.168.43.184', port= 5000, debug = True)
