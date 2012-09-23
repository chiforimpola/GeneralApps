

from sys import path, exit, stdout, argv
from os import system
from term import Color
from pygame import display, draw, init, event, QUIT, KEYDOWN
from time import sleep
from  GameCore import GameCore, LEFT, RIGHT, UP, DOWN
import random

term = Color()
defaultMessageColor = 'white'
windowSize = (640, 480)

class Snake ():
	
	def __init__(self, x, y):
		term.cout (defaultMessageColor, 'Snake initialize')
		self.x = x
		self.y = y
		self.partDimension = 10
		self.color = (255, 0, 0)
		self.foodColor = (0, 255, 0)
		self.parts = []
		self.direction = LEFT
		self.foodCoord = []
		
		if len (argv) > 1:
			maxParts = int (argv[1])
		else:
			maxParts = 3
		
		x2 = self.x
		y2 = self.y
		for i in range (maxParts):
			self.parts.append ( (x2, y2) )
			x2 += self.partDimension
	
	def blit (self, screen):
		for i in self.parts:
			draw.rect (screen, self.color, (i[0], i[1], self.partDimension, self.partDimension))
	
	def move (self, direction):
		auxParts = []
		head = True
		if direction == LEFT and self.direction != RIGHT:
			self.direction = LEFT
			for i in range(len (self.parts)):
				if head:
					head = False
					last = self.parts[i]
					auxParts.append ( (self.parts[i][0]-self.partDimension, self.parts[i][1]) )
				else:
					auxLast = last
					last = self.parts[i]
					auxParts.append (auxLast)
				
		elif direction == RIGHT and self.direction != LEFT:
			self.direction = RIGHT
			for i in range(len (self.parts)):
				if head:
					head = False
					last = self.parts[i]
					auxParts.append ( (self.parts[i][0]+self.partDimension, self.parts[i][1]) )
				else:
					auxLast = last
					last = self.parts[i]
					auxParts.append (auxLast)
		
		elif direction == UP and self.direction != DOWN:
			self.direction = UP
			for i in range(len (self.parts)):
				if head:
					head = False
					last = self.parts[i]
					auxParts.append ( (self.parts[i][0], self.parts[i][1]-self.partDimension) )
				else:
					auxLast = last
					last = self.parts[i]
					auxParts.append (auxLast)
				
		elif direction == DOWN and self.direction != UP:
			self.direction = DOWN
			for i in range(len (self.parts)):
				if head:
					head = False
					last = self.parts[i]
					auxParts.append ( (self.parts[i][0], self.parts[i][1]+self.partDimension) )
				else:
					auxLast = last
					last = self.parts[i]
					auxParts.append (auxLast)
					
		else:
			return (False)

		self.parts = auxParts
		
	def getDirection (self):
		return (self.direction)
	
	def blitFood (self, screen):
		draw.rect (screen, self.foodColor, (self.foodCoord[0], self.foodCoord[1], self.partDimension, self.partDimension))
	
	def generateFood (self, minX, minY, maxX, maxY):
		self.foodCoord.append (random.randint (minX, maxX))
		self.foodCoord.append (random.randint (minY, maxY))
	
	

def main():
	terminou = False
	term.cout (defaultMessageColor, 'Application Started!')
	init ()
	screen = display.set_mode (windowSize)
	snake= Snake(windowSize[0]/2, windowSize[0]/2)
	snake.generateFood (1, 1, screen.get_width(), screen.get_height())
	core = GameCore (screen)
	core.setMainDelay (0.2)
	
	while not terminou:
		for ev in event.get ():
			if ev.type == QUIT:
				terminou = True
				break;
				
			elif ev.type == KEYDOWN:
				term.cout ('warning', 'Keypressed: ' + str (ev.key))
				
				if ev.key == LEFT or ev.key == RIGHT or ev.key == DOWN or ev.key == UP:
					snake.move (ev.key)
		
		core.blitWalls ()
		snake.blit (screen)
		snake.blitFood (screen)
		snake.move (snake.getDirection())
		core.flipDisplay ()




if __name__ == '__main__': main()
