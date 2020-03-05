from flask import Flask
from flask import request
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# http://192.168.29.242:5000/ard
# http://127.0.0.1:5000/hello
app = Flask(__name__)
humidity = []
temperature = []
count = 0
def animate(xs, ys):
    # Add x and y to lists
    xs.append(xs)
    ys.append(ys)

    # Limit x and y lists to 20 items
    xs = xs[-20:]
    ys = ys[-20:]

    # Draw x and y lists
    ax.clear()
    ax.plot(xs, ys)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('TMP102 Temperature over Time')
    plt.ylabel('Temperature (deg C)')

def dht_plot(y_dht):
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    xs = list(range(count, count + len(y_dht)))
    ys = y_dht



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
