
import pygame

class Frame:
	x = 0
	y = 0
	w = 0
	h = 0
	parent_state = 0
	parent_id = -1
	index = 0
	delay = 0.0
	colorKey = (255, 0, 255)
	
	def __init__(self, parent_id, x, y, w, h, state, index, delay = None):
		self.parent_id = parent_id
		self.x = x
		self.y = y
		self.w = w
		self.h = h
		self.delay = 0.4
		self.state = state
		self.index = index
		if delay != None:
			self.delay = delay
	
	def setState(self, state):
		self.state = state
		return (self)
	def getState(self):
		return (self.state)
	def setDelay(self, delay):
		self.delay = delay
		return (self)
	def getDelay(self):
		return (self.delay)
	def setIndex(self, index):
		self.index = index
	def getIndex(self):
		return (self.index)
	
	def get_rect(self):
		return ((self.x,self.y,self.w,self.h))
	
	def start(self):
		pygame.time.set_timer(self.parent_id, self.delay)
	
	def stop(self):
		pygame.time.set_timer(self.parent_id, 0)
	
	def debug(self):
		print 'Debug'
		print 'x: ' + str(self.x)
		print 'y: ' + str(self.y)
		print 'w: ' + str(self.w)
		print 'h: ' + str(self.h)
		print 'state: ' + str(self.state)
		print 'index: ' + str(self.index)


