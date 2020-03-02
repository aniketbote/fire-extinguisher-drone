from flask import Flask

app = Flask(__name__)

@app.route('/helloesp')
def helloHandler():
    return 'Hello ESP8266, from Flask'

app.run(host='0.0.0.0', port= 8090)
