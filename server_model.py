from load_and_sample import Model
import cherrypy

class ModelServer():

    def __init__(self):
        self.model = Model()

    @cherrypy.expose
    def load(self, ckpt_path='C:/Users/lenovo/Tesi/prova/Transformer/unconditional_model_16.ckpt'):
        print(ckpt_path)
        self.model.load(ckpt_path)


    @cherrypy.expose
    def sample(self):
        self.model.sample()
        #rispondere in http con un file

if __name__ == '__main__':
    cherrypy.quickstart(ModelServer())
    """m = ModelServer()

    m.load()
    m.sample()"""
