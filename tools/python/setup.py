""" hobbes Python extension build script """

from distutils.core import setup, Extension

module = Extension('storage', include_dirs=['../../include'], libraries=['rt'], sources=['lib/storagemodule.cc'])

setup(name='hobbes-tools', version='0.1', description='hobbes Python binding', ext_modules=[module])

