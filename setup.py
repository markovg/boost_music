#!/usr/bin/env python

from distutils.core import setup, Extension

import os, numpy

NUMPY_INC=numpy.get_include()
#MUSIC_INC='/opt/music/include/'
#MPI_INC='/opt/mpich2/include'

cpp_files = ['music.cpp','setup.cpp','runtime.cpp','event.cpp']
src_dir = 'boostmusic/cpp_src'
sources = [os.path.join(src_dir,fn) for fn in cpp_files]
libraries = ['m', 'rt', 'boost_python-py26', 'music', 'mpich']

module = Extension('boostmusic._music', sources = sources,
                   libraries = libraries,
                   language="c++")

setup(
    name = "boostmusic",
    version = "0.1",
    #package_dir={'boostmusic': 'src'},
    packages = ['boostmusic'],
    ext_modules = [module],
    #package_data = {'brook': ['extra/*.data']},
    author = "Eilif Muller",
    author_email = "eilif@gmx.de",
    description = "Python bindings for MUSIC (http://software.incf.org/software/music)",
    license = "GPL v3, http://www.gnu.org/licenses",
    keywords = "music boost incf",
    url = "http://github.com/markovg/boost_music",
    classifiers = ['Development Status :: 3 - Alpha',
                   'Environment :: Console',
                   'Intended Audience :: Science/Research',
                   'Intended Audience :: Developers',
                   'License :: OSI Approved :: GNU General Public License (GPL)',
                   'Natural Language :: English',
                   'Operating System :: POSIX',
                   'Programming Language :: Python',
                   'Topic :: Scientific/Engineering'],

)

