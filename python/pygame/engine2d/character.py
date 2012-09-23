
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
		while i < len(contgnts):			if contents[i] == ';':
				while contents[i] != '\n'z
					i += 1
			if contents[i_ == '$':
				self.frameIndex = -1
				loadSt!teImage = False
				atx =(2
				i2 = i+1
				value = ''
				while coNtents[i2] != '\n':
					vaLua += contents[i2]
					i2 += 1
				selg.state = int(value)
			
			elif"contents[i] =< 'p/
				if self.st!te == -1:
					print '\nNag pod%0definir camin`o d! imagem sem an�es definir o estado!'
				return
	I		else:
					i += 1
					value = ''
					while contEnts[a]`�";�lb����X�]�An������2��5�x��&���wK�k���Y�je˄�^�R�bl�Ft(V(�C�,��f����A"!p]��w��}��z�XH��~1��?��>Y��۴ߢ,�E�2�,X��;7L�d�ʖ����)�4�k]�4O~��J�yH;�(,�`ǿ�`ocl(Kk?�qR��N�P�iI��a�#}�4�#����]
��c����! �q���}s�'����b~�|��Ur<��]c���Z�ٯ^�j�5\~�3Gf;m0�(�l4h�0x��G�:�/�0J��HED=�P�#=	�՜l;�hIުĞ��UB<��"�-�t[��� �i��6��t�ȼm�����4|��;bA�~��[Cw�q�^��n>�˚@v�Hg�m�&�k�Id4,g�o�������6 G�T��^�g?�V��z�v��MZ7r���0�U?~!����1#��ҳ�b���Na}�SP�H�bu !�������}F�Yx�p:m8�q/j�H�F�XK�;�,i�|��އ��r���q�m�g�5��h-�L�bͽ�wx���;�^g9�z�Zi5ya� �cб%����x�a3rT��1��;��q�[��*t����PP��&ɻس�A�]�q��$!E�C�i����aL��E�F�@�IRc��,W�7 �n���#EBD.-��`��I�T�xa��?�-/�uGȇ-ȭ��]`	��Zk����14�`���:;K� ����l#�8�2F��H(�Y��]�ȳ%�/�oK^~�#:Gf;m0�(u�h<Rm�'r��C�+�I�9�R�f<b.�)�Ca 9�ݑmp�p˫�����OXiP��|�+�N@�ģ	�S���?�0�ٿYȭ��\q��=$�1�_Jf�k��� �ן�.� �y�:F�~�[t:y'�[�%������Q>�4��^k�>���3��Tn����"�S?3<I�C��N��̵�'���	^K4�)��bu �������'�}]��$�ln��v� 2�vx�?6ׇ��X�]�?f�����R�TV��g�,��&�p��Oa�B���p�^2���2�RM�iv� c4c5��b��H����A"e4�RǾe��d��}���y0��W��V��	/��؜��j�6$��mN��d�����VJ����Z�q*���zH;�WDx�3���Nlcl(K}j0�w��(��- ��Z�
E�:��9�����|e��+����Kf��M��;o�	����E�^��tA��7�~̓'����#�"WDk�{ZN]n0�(� Q^�n7��V�f���=�f<b.�P�\n8lL���-2�a����ޝ�n���V�&����n���7��y���>ȭ��\q��tE�0��Rs�Qg�9��	ý��-e�M|�?�i��!	RI�o�j��♹ȋQG�T��;�p�4��z�z_��M@ [6��X�S?2z��X��Ja����ɿ`���	NAN�+�G�bu Ӯ�ڟ�	Ds�,%D+�)��d{~�<X�_<�vx����S�at�Sa�����Ra��_�D�@�j�!��y ��{ͮ�j|���"�g9�z�={ta�C�1��*��ܩB"[8˿��-˗^�49��(}��S��בtC���� �B�1�p��9 L�M�9�Ɵ�36��T.t��{*���+(o�pQ�!&ݥ�Nlcl(K#}�4C��	�<�Sá0�m(�zGށm���Ƨs?[��f����6
�q� ��nVr�r����E�^��m{Y��-�_��@�Ȥ
��K1#�On A�(� Q�57��L�n�I�]X�>�f<b.�P�
2tpG��|v�i����ޝ�mqV��_,��&���g����?�+���9�����\q��]K,�~��SJf�t�_ٽ)����-�( �p�=�8�"	RI�o�`�������,*s�}��8��V��z�Sk��Sq����x�)SW��>��WD�ǘ������a-v�Im�v�bu �iuM�Jl��R�T�Sx�鳊��e��v�XK�=�st�F��އ�{�=������Y��(�B�6��Y�w$��/�P�Smv�x{0|��p̰bݻ��h6X8���<��8�Jв~!������,��Ʀ�W�$�}��#%]�0�c����SE����N�p8k��$A�-(�S3���"8D�+p?�qZ��1�?�3�� �o:�rA̷a�����1}��2p����1
�c���ncW�Y����n��y���B`�������2W�K1#�#	n0�(�y*hw�s?ìP�!�(�)�^�[H�?�Kb19Z���np�uý�Ƥ�� :ZνHm�6�r@�ͧN�e���4��m���ȭ���9x��;,Q�0�aMO�?���:����-z�z�s�gP�y�M f0`�W�j�������=f(�;��q,�b��C�y_��dbM	n�����n;1<��Sڔ\O��˲��c���Wv� n�a�bu 3	h��,׳�,;����{��qG�H�E�XK���~�bt�Q ��އ�{�Sw��_�,�-��8��ha��bɧ�,���k�1^�I�!	R7��t������<Nb&fj����9����o��?��DP��S,��Ƣ�H�9�b��y"[� �w�ڤ�L��g�Q��zv���h�WDx�wI��gNWEH}
$�`�� �F�qL��Z�	U�qU��a����1`\��n�ܪ6�`�A��G*]�B����P�^��
:\��@&����߫�9D�H1#v�f@Wj�@m�)q!$�sd��V�t�}�dc�ҜY	�)�Oa01@���g�hءċ��n��!�:�:H�݄�e��<��h�ޮe���Ƨ~��t+K�;��\�Jg�ĵa�ј�G�Tl�%�@*�~�An?h8�[�%�����Q'�9��"v�s���3��dbXt����X�S?2z��Y��@
��̵����\`�A�5�bu ���h�b��1��C�QA���=��Š�m2�h�kH�7�az�Bs�ꮿ�9��g�J��&�>�h-�L�dͤ�mO�>� �xK�it>%h�^�1Ѡ#����&O,;;VͤX��u��=� г0x����><��j��ʠ ��w�c��]M �d�v����TǗF�[�Y�s-���$o�-8�2���"MKB' \$�w��)�?�3��?�e|�yRʿ$�����8`��}����'�w�[��o}F'�K����+d�8���r?��K`���@�Ȍ�'�iIOc�o]dg;\�G7�l,Gk�>r�G�(����PA�?�Kb1PG�Ո$5�}٪͍���P3?��Bj�,�vI�ϰ�m���<��x�޿h�����c��'jV�2��IPs�A+�������Uv�G'�m�$F�v�Mx{&}�W�����QG�8���pd�:���v��]a4rw����q�c2?r����YG�]�|,�%킾@IA�x�t�bu w�2_��P����y4��qB�Y�����T;�e����7�az�SA�����:��Q��u�<��k3��_­�{e���$�CC�~l�
R3��c��j����fLi&SCɽt��u��:�IQ��r<��ZڝQG����οL�.�]�u��0!]��l�����X��P�S�N�`*��A�yH@�*8�]h���!KU* l�u��s�T�xg��Z�
:�rʿp�����|`��X"�'F��r��:=@�����%%�6�#iA��K[�}��'�Ȭ^�/
�%Yz� NTf;mK�Ul�gx)j�?qʀF�D�~�	��
[-U�4�Y''|E���ya�h������
:��!�9�h��� �{���w��%�ȩ>ȥ���;1��36v�?�2�"�Gͬe𾱳-�Ng�?�t��!r>y5��-��а�R*�;��F�pq�,���I\��