from writers_block_resolver.model import Model
import cherrypy
from cherrypy.lib.static import serve_file
import sys

class ModelServer():

    def __init__(self, ckpt_path):
        self.model = Model()
        self.ckpt_path = ckpt_path

    @cherrypy.expose
    def load(self): #ckpt_path):   ='./Transformer/unconditional_model_16.ckpt'  C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/tt-942969/Transformer/unconditional_model_16.ckpt
        print(self.ckpt_path)
        self.model.load(self.ckpt_path)
        print()
        return

    @cherrypy.expose
    def sample(self):
        filename = self.model.sample()
        return serve_file(filename, "audio/midi", "attachment", "Unconditional Midi File")

    @cherrypy.expose
    def continuation(self):
        cont = self.model.continuation()
        return serve_file(cont, "audio/midi", "attachment", "Conditional Midi File")

    @cherrypy.expose
    def shutdown(self):
        cherrypy.engine.exit()

if __name__ == '__main__':
    cherrypy.quickstart(ModelServer(ckpt_path=sys.argv[1]))

