
import subprocess
import uncertainties
from uncertainties       import covariance_matrix
from uncertainties       import ufloat
from uncertainties.umath import *

#http://pythonhosted.org/uncertainties/numpy_guide.html

#https://pypi.python.org/pypi/uncertainties/

#params_results = [(1,2), (2,3), (3,4)]

#for param in pamams_results:
#    out = subprocess.getoutput('mycompiledprogram %s' % param[0])
#    assert out == param[1]

params_results = [ (0.01,0.005), (0.01,0.0005), (0.01,0.00005) ]
params_values  = [ 0.01, 0.01, 0.01 ]
params_errors  = [ 0.005, 0.0005, 0.00005 ]

print (params_results)

for x,y in params_results:
  print(ufloat(x,y))

#for x,y in zip(params_values,params_errors):
#  print ufloat(x,y)


for x in params_results:
  y = ufloat(x[0],x[1])
  print(x[0])
  print(x[1])
  print('Result = {:10.2f}'.format(y))
  print('1 significant digit on the uncertainty: {:.1u}'.format(y))
  print('3 significant digits on the uncertainty: {:.3u}'.format(y))
  print('1 significant digit, exponent notation: {:.1ue}'.format(y))
  print('1 significant digit, percentage: {:.1u%}'.format(y))
  print('Result = {:10.1e}'.format(y*1e-10))
  print('{:+.1uS}'.format(y))
  print('{:L}'.format(y*1e7))
  print(u'{:.2eP}'.format(y))

#An uncertainty which is exactly zero is always formatted as an integer:
#>>> print ufloat(3.1415, 0)
#3.1415+/-0
#>>> print ufloat(3.1415e10, 0)
#(3.1415+/-0)e+10
#>>> print ufloat(3.1415, 0.0005)
#3.1415+/-0.0005
#>>> print '{:.2f}'.format(ufloat(3.14, 0.001))
#3.14+/-0.00
#>>> print '{:.2f}'.format(ufloat(3.14, 0.00))
#3.14+/-0


u = ufloat(1, 0.1, "u variable")  # Tag
v = ufloat(10, 0.1, "v variable")

sum_value = u+2*v
print(sum_value)

cov_matrix = covariance_matrix([u, v, sum_value])
print(cov_matrix)

(u2, v2, sum2) = uncertainties.correlated_values([1, 10, 21], cov_matrix)
print(sum2)

for (var, error) in sum_value.error_components().items():
  print("{}: {}".format(var.tag, error))


output = subprocess.check_output(["echo", "Hello World!"])
print(subprocess.getoutput('ls /bin/ls'))
print(subprocess.getoutput('echo %s' %"Hello World!"))
print(b'hi'.decode('ascii'))
print(output)


