
import pygame
from pygame.locals import *
from Frame import *

class Character():
	def __init__(self, id):
		self.id = USEREVENT+id
		self.frames = []
		self.frameIndex = -1
		self.colorKey = { }
		self.pathToImage = { }
		self.images = { }
		self.state = -1
		self.actualImage = None
	
	def setState(self, state):
		self.state = state
	def getState(self):
		return (self)
	def getPathToImage(self):
		return (self.pathToImage[self.state])
	
	def initialize(self, path):
		'''
		 Forma de leitura do arquivo de configuracao:
		  #Cada estado pode estar vinculado a mais de um frame
		  #Cada estado pode definir uma cor de transparencia para seu conjunto de frames
		  
		  $x define o id do estado
		  pPathToFile define o caminho para a imagem do estado
		  cx,y,z define a cor de transparencia para os frames daquele estado
		  %x,y,w,h define as coordenadas para realizar o blit do frame
		  !x define o atraso para realizar a troca do frame
		'''
		contents=open(path).read()
		i = 0
		loadStateImage = False
		while i < len(contents):
			if contents[i] == ';':
				while contents[i] != '\n':
					i += 1
			if contents[i] == '$':
				self.frameIndex = -1
				loadStateImage = False
				aux = 2
				i2 = i+1
				value = ''
				while contents[i2] != '\n':
					value += contents[i2]
					i2 += 1
				self.state = int(value)
			
			elif contents[i] == 'p':
				if self.state == -1:
					print '\nNao pode definir caminho da imagem sem antes definir o estado!'
					return
				else:
					i += 1
					value = ''
					while contents[i] != '\n':
						value += contents[i]
						i += 1
					self.pathToImage[self.state] = value
					print 'Carregando imagem: ' + self.pathToImage[self.state]
					self.images[self.state] = pygame.image.load (self.pathToImage[self.state])
					self.images[self.state].set_colorkey(self.colorKey[self.state])
					loadStateImage = True
					print 'image loaded ' + self.pathToImage[self.state]
			
			elif contents[i] == 'c':
				if self.state == -1:
					print '\nNao pode definir cor sem antes definir estado'
					return
				else:
					i += 1
					cont = 0
					value = ''
					R = G = B = 0
					while i < len (contents):
						if contents[i] != ',' and contents[i] != '\n':
							value += contents[i]
						else:
							if cont == 0:
								R = int (value)
								value = ''
								cont = 1
							elif cont == 1:
								G = int (value)
								value = ''
								cont = 2
							elif cont == 2:
								B = int (value)
								value = ''
								cont = 0
								break
						i += 1
					self.colorKey[self.state] = (R, G, B)
			
			elif contents[i] == '%':
				if self.state != -1 and loadStateImage == True:
					x = y = w = h = 0
					cont = 0
					value = ''
					self.frameIndex += 1
					while contents[i] != '\n':
						i += 1
						if contents[i] != ',' and contents[i] != '\n':
							value += contents[i]
						else:
							if cont == 0:
								x = int (value)
								cont = 1
							elif cont == 1:
								y = int (value)
								cont = 2
							elif cont == 2:
								w = int (value)
								cont = 3
							elif cont == 3:
								h = int (value)
								cont = 0
							value = ''
					if x == y and x == w and x == h and x == 0:
						x, y, w, h = 0, 0, self.images[self.state].get_size()[0], self.images[self.state].get_size()[1]
					self.frames.append (Frame(self.id, x,y,w,h,self.state,self.frameIndex))
				else:
					print ('Erro!\nDefinindo frame sem definir estado ou caminho de imagem!')
			
			elif contents[i] == '!':
				if self.state == -1 or len(self.frames) == 0:
					print '\nNao pode definir delay sem estado ou frame'
					return
				else:
					value = ''
					i += 1
					while contents[i] != '\n':
						value += contents[i]
						i += 1
					self.frames[len(self.frames)-1].setDelay(int(value))
				
			i += 1
		return (self)
		
	def getFrames (self, state):
		result = []
		for i in self.frames:
			if i.getState() == state:
				result.append(i)
		return (result)
	
	def getFrame(self, state = None, index = None, image = True):
		if index == None:
			index = self.index
		else:
			self.index = index
		if state == None:
			state = self.state
		else:
			self.state = state
		for i in self.frames:
			if i.getState() == state and i.getIndex() == index:
				if image == True:
					return (self.images[state].subsurface(i.get_rect()))
				elif image == False:
					return (i)
		return (None)
	
	def changeFrame (self):
		self.getFrame(self.state, self.frameIndex, False).stop()
		if self.frameIndex < self.lenFrames(self.state) - 1:
			self.frameIndex += 1
		else:
			self.frameIndex = 0
		print 'Change Frame: ' + str(self.state) + ' [' + str(self.frameIndex) + ']'
		self.getFrame(self.state, self.frameIndex, False).start()
		return (self.getFrame(self.state, self.frameIndex))
	
	def getPathToImage(self, state):
		return (self.pathToImage[state])
	
	def getImage(self, state):
		return (self.images[state])
	
	def getId(self):
		return (self.id)
	
	def lenFrames(self, state):
		cont = 0
		for i in self.frames:
			if i.getState() == state:
				cont += 1
		return (cont)
	
	def start(self):
		self.frameIndex = 0
		self.getFrame(self.state, self.frameIndex, False).start()

pygame.init()
sc=pygame.display.set_mode((500,500))
a=Character(0).initialize('prince.dat')
cont = 0
a.getFrame(0, 0)
a.start()
while True:
	sc.fill((0,0,0))
	for ev in pygame.event.get():
		if ev.type == KEYDOWN and ev.key == K_ESCAPE:
			exit()
		else:
			if ev.type == a.getId():
				a.changeFrame()
	sc.blit(a.getFrame(), a.getFrame().get_rect())
	pygame.display.update()
	pygame.time.delay(20)
