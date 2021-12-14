import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")



# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


# export API_KEY=pk_cc8821de4e8d4731ad5c8fdb105c0ee6

@app.route("/")
# @login_required
def index():
    """Show portfolio of stocks"""
    # print(wallet[0])

    if session.get("user_id") is None:
        return render_template("index.html")
    else:

        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        wallet = db.execute("SELECT * FROM wallet WHERE user_id = ?", session["user_id"])
        # names=[]

        total=user[0]["cash"]
        for i in wallet:
            try:
                temp=lookup(i["symbol"])
                i["price"] = temp["price"]
                i["name"] = temp["name"]
                total += int(i["shares"]) * int(i["price"])
                
            except:
                pass

            # wallet.append(names)
            
        return render_template("index.html", session_login=session, user=user[0], wallet=wallet, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # TODO
        # check the symbol, and if the user have cash to buy

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("ops", "choose a symbol")

        if not shares.isnumeric():
            return apology("ops", "shares must be a number")
        elif int(shares) < 1 :
            return apology("ops", "shares must be at least 1")

        dt = datetime.now()
        stock=lookup(symbol)

        # check
        if not stock:
            return apology("oooops", "wrong symbol")


        #check the cash available
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", str(session['user_id']))
        current_cash = int(current_cash[0]["cash"])
        transaction_price = int(shares) * int(stock["price"])

        if current_cash < transaction_price:
            return apology("oh oh", "you dont have enough money")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash - transaction_price, str(session['user_id']))


        # check if the symbol is already in use for this user
        list_id_symbol = db.execute("SELECT user_id_symbol FROM wallet WHERE user_id = ?", str(session['user_id'])) #+'_'+ stock['symbol'])

        user_id_symbol = str(session['user_id'])+'_'+ stock['symbol']

        new_symbol = True
        for id_symbol in list_id_symbol:
            if id_symbol["user_id_symbol"] == user_id_symbol:
                new_symbol = False
                break
        
        #Save transaction in history
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)",session['user_id'], stock['symbol'], shares, stock['price'], dt)


        if new_symbol:
            # Insert new item to wallet
            # TODO: remove price
            db.execute("INSERT INTO wallet(user_id, symbol, shares, user_id_symbol) VALUES (?, ?, ?, ?)", session['user_id'], stock['symbol'], shares, user_id_symbol)

        else:


            previous_shares = db.execute("SELECT shares FROM wallet WHERE user_id_symbol = ?", user_id_symbol )
            shares = int(previous_shares[0]["shares"]) + int(shares)

            db.execute("UPDATE wallet SET shares = ? WHERE user_id_symbol = ? ", shares, user_id_symbol)


        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    
    history = db.execute("SELECT * FROM history WHERE user_id = ? ", session['user_id'])
    
    return render_template("history.html", HISTORY=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["name"] = rows[0]["username"]


        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Symbol required", "ops")

        stock=lookup(request.form.get("symbol"))
        if not stock:
            return apology("Wrong Symbol", "oops")

        return render_template("quoted.html", name=stock["name"],
                                            symbol=stock["symbol"],
                                            price=usd(stock["price"])
                                            )
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # return apology("TODO")

    if request.method == "POST":

        # Ensure username and password were submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif request.form.get("password") != request.form.get("password_confirm"):
            return apology("passwords dont match")

        # Check if username is in use
        users = db.execute("SELECT username FROM users")

        for user in users:
            if request.form.get("username") == user["username"]:
                return apology("Usarname already in use")

        # Insert new user in database
        id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
        
        # Insert new user in history
        dt = datetime.now()
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)",id , "wallet_cash", 1, 100000, dt)


        return render_template("register.html", register_ok="")

    else:
        return render_template("register.html")

@app.route("/cash", methods=["POST"])
@login_required
def cash():
    """Refresh cash value"""
    
    value=int(request.form.get("value"))
    cash_previous = db.execute("SELECT cash FROM users WHERE id =?", session['user_id'] )
    cash_previous = int(cash_previous[0]["cash"])
    print(cash_previous)
    print(value)
    
    if cash_previous + value < 0:
        return apology ("too much money", "xii")
    else:
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_previous + value, session['user_id'] )
        dt = datetime.now()
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)", session['user_id'] , "wallet_cash", 1, value, dt)

        
    
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    SYMBOL = db.execute("SELECT symbol FROM wallet WHERE user_id = ?", session['user_id'] )
    

    symbol_list = []
    for row in SYMBOL:
        symbol_list.append(row["symbol"])

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        user_id_symbol = str(session['user_id'])+'_'+ str(symbol)

        if symbol not in symbol_list:
            return apology("ops", "choose a correct symbol")

        if not shares.isnumeric():
            return apology("ops", "shares must be a number")
        elif int(shares) < 1 :
            return apology("ops", "shares must be at least 1")

        dt = datetime.now()
        stock=lookup(symbol)

        # check
        if not stock:
            return apology("oooopas", "wrong symbol")

        current_shares = db.execute("SELECT shares FROM wallet WHERE user_id_symbol = ?", user_id_symbol)
        current_shares = current_shares[0]["shares"]

        if current_shares < int(shares):
            return apology("ops", "you have to sell less stocks")
        elif current_shares > int(shares):
            db.execute("UPDATE wallet SET shares = ? WHERE user_id_symbol = ?", current_shares - int(shares), user_id_symbol)
        else:
            db.execute("DELETE FROM wallet WHERE user_id_symbol = ?", user_id_symbol)

        #check the cash available
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", str(session['user_id']))
        current_cash = int(current_cash[0]["cash"])
        transaction_price = int(shares) * int(stock["price"])

        db.execute("UPDATE users SET cash = ? WHERE id =?", current_cash + transaction_price, str(session['user_id']))

        #Save transaction in history
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)",session['user_id'], stock['symbol'], -int(shares), stock['price'], dt)


        return redirect("/")

    else:


        return render_template("sell.html", SYMBOL = SYMBOL)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
