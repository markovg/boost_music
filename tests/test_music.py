import unittest
import boostmusic as music
import sys

class TestStream(unittest.TestCase):
    s = music.Setup(sys.argv)
    sc = s.communicator()

    def test_setup(self):
        c = self.sc
        assert c.rank == 0
        assert c.size == 1

    def test_runtime(self):
        self.r = music.Runtime(self.s,0.1)
        r = self.r
        assert r.time() == 0.0
        r.tick()
        assert r.time() == 0.1

        c = r.communicator()
        assert c.rank == 0
        assert c.size == 1

        

if __name__ == '__main__':
    unittest.main()


        
