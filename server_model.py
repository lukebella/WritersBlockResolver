from load_and_sample import Model
import cherrypy

class ModelServer():

    def __init__(self):
        self.model = Model()
        self.filename = ""

    @cherrypy.expose
    def load(self, ckpt_path='C:/Users/lenovo/Tesi/prova/Transformer/unconditional_model_16.ckpt'):
        self.model.load(ckpt_path)


    @cherrypy.expose
    def sample(self):
        self.filename = self.model.sample()
        with open(self.filename, mode='rb') as file:  # b is important -> binary
            fileContent = file.read()

        return fileContent
       # return self.filename



if __name__ == '__main__':
    cherrypy.quickstart(ModelServer())

