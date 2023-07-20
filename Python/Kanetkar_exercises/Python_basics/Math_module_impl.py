# mathematical functions from math module
import math
x=1.5357
y=2.5
print(math.sqrt(x))             #square root
print(math.factorial(6))        #factorial
print(math.pow(2,4))            #power    #math.pow(2,4) is same as 2**4  
print(math.pow(2,4.5))          #power    #math.pow(2,4.5) is same as 2**4.5
print(math.pow(2.5,4.5))        #power    #math.pow(2.5,4.5) is same as 2.5**4.5
print(math.pow(2.5,4))          #power    #math.pow(2.5,4) is same as 2.5**4
print(math.fabs(x))             #absolute value of float number   #math.fabs(x) is same as abs(x)  #math.fabs(x) is same as abs(float(x))  #math.fabs(x) is same as abs(int(x))  #math.fabs(x) is same as abs(round(x))  #math.fabs(x) is same as abs(math.floor(x))  #math.fabs(x) is same as abs(math.ceil(x))
print(math.log(x))              #natural logarithm of x
print(math.log1p(x))            #natural logarithm of x plus 1
print(math.log2(x))             #base 2 logarithm of x
print(math.log10(x))            #logarithm of x to base 10  #math.log10(x) is same as math.log(x,10)  #math.log10(x) is same as math.log(x)/math.log(10)  #math.log10(x) is same as math.log(x)/math.log(math.e)/math.log(10)   #math.log10(x) is same as math.log(x)/math.log(math.e)/math.log(2)/math.log(5)  #math.log10(x) is same as math.log(x)/math.log(math.e)/math.log(2)/math.log(5)/math.log(2)
print(math.log(x,10))
print(math.log(x,2))            #logarithm of x to base 2
print(math.exp(x))              #exponential of x  #math.exp(x) is same as math.e**x
print(math.expm1(x))            #e raised to the power of x minus 1  #math.expm1(x) is same as math.exp(x)-1
print(math.trunc(x))            #truncation of x  #math.trunc(x) is same as int(x)  #math.trunc(x) is same as int(float(x))  #math.trunc(x) is same as int(round(x))  #math.trunc(x) is same as int(math.floor(x))  #math.trunc(x) is same as int(math.ceil(x))
print(math.floor(x))            #floor of x  #math.floor(x) is same as int(math.floor(x))  #math.floor(x) is same as int(math.trunc(x))  #math.floor(x) is same as int(x)  #math.floor(x) is same as int(float(x))  #math.floor(x) is same as int(round(x))  #math.floor(x) is same as int(math.ceil(x))
print(math.ceil(x))             #ceiling of x  #math.ceil(x) is same as int(math.ceil(x))  #math.ceil(x) is same as int(math.trunc(x))  #math.ceil(x) is same as int(x)  #math.ceil(x) is same as int(float(x))  #math.ceil(x) is same as int(round(x))  #math.ceil(x) is same as int(math.floor(x))
print(math.trunc(-x))           #truncation of -x  #math.trunc(-x) is same as int(-x)  #math.trunc(-x) is same as int(float(-x))  #math.trunc(-x) is same as int(round(-x))  #math.trunc(-x) is same as int(math.floor(-x))  #math.trunc(-x) is same as int(math.ceil(-x))
print(math.floor(-x))           #floor of -x  #math.floor(-x) is same as int(math.floor(-x))  #math.floor(-x) is same as int(math.trunc(-x))  #math.floor(-x) is same as int(-x)  #math.floor(-x) is same as int(float(-x))  #math.floor(-x) is same as int(round(-x))  #math.floor(-x) is same as int(math.ceil(-x))
print(math.ceil(-x))            #ceiling of -x  #math.ceil(-x) is same as int(math.ceil(-x))  #math.ceil(-x) is same as int(math.trunc(-x))  #math.ceil(-x) is same as int(-x)  #math.ceil(-x) is same as int(float(-x))  #math.ceil(-x) is same as int(round(-x))  #math.ceil(-x) is same as int(math.floor(-x))
print(math.mod(x))              #modulus of x  #math.mod(x) is same as x%1
print(math.modf(x))             #fractional and integral parts of x  #math.modf(x) is same as (x%1,x//1)
print(math.modf(-x))            #fractional and integral parts of -x  #math.modf(-x) is same as (-x%1,-x//1)
print(math.sin(x))              #sine of x
print(math.cos(x))              #cosine of x
print(math.tan(x))              #tangent of x
print(math.asin(x))             #arc sine of x
print(math.acos(x))             #arc cosine of x
print(math.atan(x))             #arc tangent of x
print(math.sinh(x))             #hyperbolic sine of x
print(math.cosh(x))             #hyperbolic cosine of x
print(math.tanh(x))             #hyperbolic tangent of x
print(math.asinh(x))            #hyperbolic arc sine of x
print(math.acosh(x))            #hyperbolic arc cosine of x
print(math.atanh(x))            #hyperbolic arc tangent of x
print(math.degrees(x))          #converts x from radians to degrees
print(math.radians(x))          #converts x from degrees to radians
print(math.pi)                  #pi
print(math.e)                   #e
print(math.pi, math.e)          #pi and e constants in one line
print(math.inf)                 #infinity  #math.inf is same as float('inf')
print(math.nan)                 #not a number  #math.nan is same as float('nan')
print(math.isinf(x))            #checks if x is infinity  #math.isinf(x) is same as x==math.inf
print(math.isnan(x))            #checks if x is not a number  #math.isnan(x) is same as x==math.nan
print(math.isfinite(x))         #checks if x is finite  #math.isfinite(x) is same as not math.isinf(x) and not math.isnan(x)
print(math.isclose(x,y))        #checks if x and y are close  #math.isclose(x,y) is same as abs(x-y)<=max(rel_tol*max(abs(x),abs(y)),abs_tol)
print(math.gcd(x,y))            #greatest common divisor of x and y  #math.gcd(x,y) is same as math.gcd(x%y,y) if x>y else math.gcd(x,y%x) if x<y else x
print(math.lcm(x,y))            #least common multiple of x and y  #math.lcm(x,y) is same as x*y//math.gcd(x,y)
print(math.factorial(x))        #factorial of x  #math.factorial(x) is same as math.factorial(x-1)*x if x>0 else 1
print(math.perm(x,y))           #permutation of x and y  #math.perm(x,y) is same as math.factorial(x)//math.factorial(x-y)
print(math.comb(x,y))           #combination of x and y  #math.comb(x,y) is same as math.factorial(x)//math.factorial(y)//math.factorial(x-y)
print(math.erf(x))              #error function of x
print(math.erfc(x))             #complementary error function of x
print(math.gamma(x))            #gamma function of x
print(math.lgamma(x))           #logarithm of the absolute value of the gamma function of x
print(math.tau)                 #tau