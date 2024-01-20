class User:
    def __init__(self, name, email):
        self._name = name
        self._email = email

    def get_name(self):
        return self._name

    def get_email(self):
        return self._email
     
    def do_something_cool(self):
        print (self._name + ", Welcome to GetIoT")

    def __str__(self):
        return self._name + " , " + self._email

if __name__ == "__main__":
    users = [ User("Rudy", "rudy@getiot.tech"), User("Tina", "tina@getiot.tech")]

    for user in users:
        user.do_something_cool()
