#!/usr/bin/env python

#mcerp
#soerp

import numpy
from uncertainties import ufloat
from uncertainties import ufloat_fromstr
from uncertainties import unumpy
from uncertainties.umath import *


print ufloat(0.1,0.01)
print ufloat(0.001,0.01)
print ufloat(0.001,0.0951)
print ufloat(0.01,0.00356)
print ufloat(0.01,0.2)
print ufloat(0.01,0.949)
print ufloat(0.01,0.951)
print ufloat(9.50,0.951)
print ufloat(91.50,0.951).n
print ufloat(91.50,0.951).s
print ufloat(91.50,12)





#x = ufloat(0.1,  0.01)
#print x

#x = ufloat(0.001,  0.0951)
#print x

#x = ufloat(0.001,  0.01)
#print x

#x = ufloat(0.01,  0.2)
#print x


#x = ufloat(0.001,  0.356)
#print x

#x = ufloat(0.01,0.951)
#print x

#x = ufloat(91.50,0.951)
#print x


#x = ufloat(91.50,12,13)
#print x
#unsure what this does

#x = ufloat(91.50,-0.951)
#print x
##ABOVE throws an exception

#x = ufloat(0.20, 0.01)
#y = ufloat_fromstr("0.20+/-0.01")
#arr = unumpy.uarray([1, 2], [0.01, 0.002])

#print x**2
#print x
#print sin(x**2)
#print arr
#arr = numpy.array([ufloat(1, 0.1), ufloat(2, 0.002)])
#print arr
#print unumpy.umatrix([1, 2], [0.01, 0.002])
#print unumpy.matrix(arr)


