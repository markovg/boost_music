from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys

def init():

    glutInit(sys.argv)
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION)

    
