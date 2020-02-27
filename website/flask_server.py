from flask import Flask, flash, render_template, request,session
from firebase import firebase
import pyrebase
import hashlib
import os
from PIL import Image
app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'temp'
#configuration for firebase
CONFIG = {
    "apiKey": "AIzaSyCs1J_PXXG3HEs1B19YVN7Z-d3JESrui3E",
    "authDomain": "firebird-7ef02.firebaseapp.com",
    "databaseURL": "https://firebird-7ef02.firebaseio.com",
    "projectId": "firebird-7ef02",
    "storageBucket": "firebird-7ef02.appspot.com",
    "messagingSenderId": "574864460908",
    "appId": "1:574864460908:web:c317c3217ae1fcd4899c49",
    "measurementId": "G-15LBYQ506Y"
}

##------------------------------------------------------------------------------##

def logincheck(u_email, u_pass):
    fb_pyre = pyrebase.initialize_app(CONFIG)
    auth = fb_pyre.auth()
    try:
        signin = auth.sign_in_with_email_and_password(u_email, u_pass)
    except Exception as e:
        return False
    return True

def signupcheck(u_dict):
    fb = firebase.FirebaseApplication('https://firebird-7ef02.firebaseio.com/')
    email = u_dict['email']
    res = hashlib.sha256(email.encode())
    sha_email = res.hexdigest()
    result = fb.get('/{}'.format(sha_email), None)
    if result != None:
        valid = False
        msg = 'Email already exists'
        return valid, msg
    else:
        valid = True
        msg = 'Succesfully created profile'
        return valid, msg

def update_db(user_dict):
    fb = firebase.FirebaseApplication('https://firebird-7ef02.firebaseio.com//')
    fb_pyre = pyrebase.initialize_app(CONFIG)
    auth = fb_pyre.auth()
    email = user_dict['email']
    res = hashlib.sha256(email.encode())
    sha_email = res.hexdigest()
    result = fb.post('/{}'.format(sha_email), user_dict)
    flag = auth.create_user_with_email_and_password(email, user_dict['password'])
    if result != None and flag != None:
        status = True
        return status


##------------------------------------------------------------------------------##
##__________________pages__________________________
@app.route('/login_page')
def login_page():
    return render_template('login.html')

@app.route('/forgotpass_page')
def forgotpass_page():
    return render_template('forgotpass.html')

@app.route('/accounts_page')
def accounts_page():
    return render_template('accounts.html')

@app.route('/index_page')
def index_page():
    if session['logged_in']:
        return render_template('index.html')
    else:
        flash('Please Login')
        return render_template('login.html')



##________________functions________________________
@app.route("/logout")
def logout():
    session['logged_in'] = False
    session.pop(session['username'])
    print(session)
    return render_template('login.html')


@app.route("/forgotpassword", methods = ['POST'])
def forgotpassword():
    email = request.form['email']
    fb_pyre = pyrebase.initialize_app(CONFIG)
    auth = fb_pyre.auth()
    auth.send_password_reset_email(email)
    return render_template('forgotpass.html')



@app.route("/login", methods = ['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    valid = logincheck(email, password)
    if valid:
        session['logged_in'] = True
        session['username'] = email
        print(session)
        return render_template('index.html')
    else:
        flash('Incorrect Username or Password')
        return render_template('login.html')



@app.route("/signup", methods = ['POST'])
def signup():
    user = {}
    temp = request.files['file']
    temp.save(os.path.join(app.config["UPLOAD_FOLDER"], 'temp.png'))
    user['photo'] = Image.open(os.path.join(app.config["UPLOAD_FOLDER"], 'temp.png'))
    # print('\n' * 10)
    # print(type(temp))
    # print(temp)
    # print('\n' * 10)
    user['name'] = request.form['name']
    user['email'] = request.form['email']
    user['title'] = request.form['title']
    user['password'] = request.form['password']
    # update_db(user)
    valid, msg = signupcheck(user)
    print(valid, msg)
    if valid:
        status = update_db(user)
        if status:
            flash(msg)
            return render_template('login.html')
        else:
            flash('Error in creating profile')
            return render_template('accounts.html')
    else:
        flash(msg)
        return render_template('accounts.html')

if __name__ == "__main__":
    app.secret_key = os.urandom(100)
    app.run(host='0.0.0.0', port=5000, debug = True )

# if __name__ == "__main__":
#     app.run(debug=True)
