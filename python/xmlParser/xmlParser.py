
from xml.dom.minidom import parseString

class Parser ():
    def __init__(self, path):
        self.domContents = open(path).read()

    def getData (self, name):
        nodes = []
        dom = parseString (self.domContents)
        nodes=dom.getElementsByTagName (name)

        (nodes[0].getElementsByTagName(name)[0])

        return (nodes)

Parser('test.xml').getNodes('estate')
