from datetime import datetime
import sys

class User:
    def __init__(self, name, email):
        self._name = name
        self._email = email

    def get_name(self):
        return self._name

    def get_email(self):
        return self._email
     
    def do_something_cool(self):
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print (self._name + ", Welcome to GetIoT (" + current_time + ")")

    def __str__(self):
        return self._name + " , " + self._email

if __name__ == "__main__":
    print("Python Version:", sys.version)

    users = [ User("Rudy", "rudy@getiot.tech"), User("Tina", "tina@getiot.tech")]

    for user in users:
        user.do_something_cool()
