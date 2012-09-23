
import sys
import os

class Color:

    foreground = {
        "blue": '\033[94m',
        "warning": "\033[93m",
        "error": "\033[91m",
        'cyan': '\033[36m',
        "default": "\033[0m",
        'white': '\033[37m'
    }

    background = {
        'black': '\033[100m',   # Black
        'red': '\033[101m',     # Red
        'green': '\033[102m',   # Green
        'yellow': '\033[103m',  # Yellow
        'blue': '\033[104m',    # Blue
        'purpule': '\033[95m',  # Purple
        'cyan': '\033[106m',    # Cyan
        'white': '\033[107m',   # White
        'default': '\033[0m'
    }

    def setForeground (self, colorName = ""):
        if colorName != "":
            sys.stdout.write (self.foreground[colorName])
        else:
           sys.stdout.write (self.foreground['default'])

    def setBackground (self, colorName = ""):
        if colorName != "":
            sys.stdout.write (self.background[colorName])
        else:
           sys.stdout.write (self.background['default'])

    def getColors(self):
        result = []
        result.append ('BACKGROUND')
        for i in self.background:
           result.append (i)

        result.append ('FOREGROUND')
        for i in self.foreground:
           result.append (i)
        return (result)
    
    def cout (self, color, msg):
		self.setForeground (color)
		sys.stdout.write (msg + "\n")
		self.setForeground ()


