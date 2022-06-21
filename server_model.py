from load_and_sample import Model
import cherrypy
from cherrypy.lib.static import serve_file

class ModelServer():

    def __init__(self):
        self.model = Model()
        self.filename = ""

    @cherrypy.expose
    def load(self, ckpt_path='C:/Users/lenovo/Tesi/prova/Transformer/unconditional_model_16.ckpt'):
        self.model.load(ckpt_path)
        return

    @cherrypy.expose
    def sample(self):
        self.filename = self.model.sample()
        return serve_file(self.filename, "application/x-download", "attachment")



if __name__ == '__main__':
    cherrypy.quickstart(ModelServer())

