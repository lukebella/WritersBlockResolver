from writers_block_resolver.model import Model
import cherrypy
from cherrypy.lib.static import serve_file

import os
import sys
import logging

class ModelServer():

    def __init__(self, ckpt_path):
        self.model = Model()
        self.ckpt_path = ckpt_path
        self.isLoaded = False


    # read the uploaded file
    def store(self, myFile):
        return self.model.store(myFile)
    #cherry http body


    @cherrypy.expose
    def load(self): #ckpt_path):   ='./Transformer/unconditional_model_16.ckpt'  C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/tt-942969/Transformer/unconditional_model_16.ckpt
        #print(self.ckpt_path)
        if not self.isLoaded:
            self.model.load(self.ckpt_path)
            self.isLoaded = True
            logging.warning("Model loaded")
        return


    @cherrypy.expose
    def sample(self):
        filename = self.model.sample()
        logging.warning("Unconditional sequence generated")
        return serve_file(filename, "audio/midi", "attachment", "Unconditional Midi File")


    @cherrypy.expose
    def continuation(self):#, myFile):
        logging.warning(str(cherrypy.request.body.read()))
        midiFileToContinue = cherrypy.request.body.read()

        logging.warning(os.path.isfile(midiFileToContinue))

        #midiFileToContinue = self.store(myFile)
        if os.path.exists(midiFileToContinue):
            #and (not(isinstance(midiFileToContinue, str))):
            self.model.primingSequence(midiFileToContinue)
            cont = self.model.continuation()
            logging.warning("Conditional sequence generated")
            return serve_file(cont, "audio/midi", "attachment", "Conditional Midi File")
        else:
            logging.warning("No file istance")

    @cherrypy.expose
    def shutdown(self):
        cherrypy.engine.exit()



if __name__ == '__main__':
    os.environ["TF_CPP_MIN_LOG_LEVEL"] = "3"
    cherrypy.quickstart(ModelServer(ckpt_path=sys.argv[1]))

