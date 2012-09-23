
from pygame import draw, display
from time import sleep


UP    = 273
DOWN  = 274
RIGHT = 275
LEFT  = 276


class GameCore ():
	
	main_delay = 0.3
	
	def __init__ (self, screen, color = (255, 0, 0)):
		self.screen = screen
		self.color = color
		self.walls = (0, 0, screen.get_width(), screen.get_height())
	
	def blitWalls (self):
		draw.rect (self.screen, self.color, self.walls, 1)
	
	def flipDisplay (self):
		display.update ()
		draw.rect (self.screen, (0, 0, 0), self.screen.get_rect())
		sleep  (self.main_delay)
	
	def setMainDelay (self, main_delay):
		self.main_delay = main_delay
		
	def getMainDelay (self):
		return (self.main_delay)
	
	def setWindowSize (self, windowSize):
		self.windowSize = windowSize
		
	def getWindowSize (self):
		return (self.windowSize)
