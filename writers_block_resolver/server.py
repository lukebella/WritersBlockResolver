from writers_block_resolver.model import Model
import cherrypy
from cherrypy.lib.static import serve_file

import os
import sys
import logging
import json

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
            self.local = cherrypy._cprequest.Request.local
            self.remote = cherrypy._cprequest.Request.remote
            logging.warning("Model loaded")
        return


    @cherrypy.expose
    def sample(self):
        filename = self.model.sample()
        logging.warning("Unconditional sequence generated")
        return serve_file(filename, "audio/midi", "attachment", "Unconditional Midi File")


    @cherrypy.expose
    def continuation(self, max_primer_seconds):#, myFile):
        logging.warning(max_primer_seconds)
        #logging.warning(str(cherrypy.request.body.read()))
        #logging.warning(cherrypy.serving.request)
        #local = cherrypy.lib.httputil.Host('127.0.0.1', 80, '127.0.0.1')
        #remote = cherrypy.lib.httputil.Host('127.0.0.1', 1111, '127.0.0.1')

        req = cherrypy._cprequest.Request(self.local, self.remote)
        logging.warning(req.config)
        logging.warning(req.body)
        logging.warning("processors ", cherrypy.request.body.processors)

        #httpReq = cherrypy._cprequest._cpreqbody.Entity
        #logging.warning("parts", httpReq.parts)


        # cherrypy.request.body.read_into_file(midiFileToContinue)

        b = cherrypy.request.body.fp.read()
        logging.warning("%s", b)
        #midiFileToContinue.write(b)
        #midiFileToContinue.seek(0)
        self.model.primingSequence(b, max_primer_seconds)


        cont = self.model.continuation()
        logging.warning("Conditional sequence generated")
        return serve_file(cont, "audio/midi", "attachment", "Conditional Midi File")

    @cherrypy.expose
    def shutdown(self):
        cherrypy.engine.exit()



if __name__ == '__main__':
    os.environ["TF_CPP_MIN_LOG_LEVEL"] = "3"
    cherrypy.quickstart(ModelServer(ckpt_path=sys.argv[1]))

