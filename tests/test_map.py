import boostmusic as music
import sys

s = music.Setup(sys.argv)

evport = s.publishEventInput("hello")

class X(music.EventHandlerGlobalIndex):
    def __call__(self,f,idx):
        print f,int(idx)

evh = X()

#index_map = music.LinearIndex(music.GlobalIndex(0),evport->width() )
index_map = music.LinearIndex(music.GlobalIndex(0),27)

evport.map(index_map,evh,0.0)

