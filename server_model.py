from load_and_sample import Model
import cherrypy
import requests

class ModelServer():

    def __init__(self):
        self.model = Model()
        self.url = 'http://127.0.0.1:8080'

    @cherrypy.expose
    def load(self, ckpt_path='C:/Users/lenovo/Tesi/prova/Transformer/unconditional_model_16.ckpt'):
        self.model.load(ckpt_path)


    @cherrypy.expose
    def sample(self):
        return self.model.sample()
        #f = requests.get(url)
        # print(f.text)
        #rispondere in http con un file

if __name__ == '__main__':
    cherrypy.quickstart(ModelServer())

