from load_and_sample import Model
import cherrypy
from cherrypy.lib.static import serve_file


class ModelServer():

    def __init__(self):
        self.model = Model()

    @cherrypy.expose
    def load(self, ckpt_path):   #'./Transformer/unconditional_model_16.ckpt'
        self.model.load(ckpt_path)
        return

    @cherrypy.expose
    def sample(self):
        filename = self.model.sample()
        return serve_file(filename, "audio/midi", "attachment", "Unconditional Midi File")


if __name__ == '__main__':
    cherrypy.quickstart(ModelServer())

