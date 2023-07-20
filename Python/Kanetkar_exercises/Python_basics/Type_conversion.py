#convert to int
print(int(3.14))        #float to int
a=int('485')            #string to int
b=int('768')            #string to int
c=a+b                   #int addition after conversion
print(c)                #int addition print after conversion
print(int('1011',2))    #convert from binary to decimal int         #2 is the base
print(int('341',8))     #convert from octal to decimal int          #8 is the base
print(int('21',16))     #convert from hexadecimal to decimal int    #16 is the base

#convert to float
print(float(35))        #int to float
i=float('3.14')         #string to float
j=float('2.71')         #string to float
k=i+j                   #float addition after conversion
print(k)                #float addition print after conversion

#convert to complex
print(complex(35))     #float to complex
x=complex(4.85,1.1)    #float to complex
y=complex(7.68,2.1)    #float to complex
z=x+y                  #complex addition after conversion
print(z)               #complex addition print after conversion

#convert to bool
print(bool(35))        #int to bool
print(bool(1.2))       #float to bool
print(int(True))       #bool to int
print(int(False))      #bool to int

#convert to string
print(str(35))         #int to string
print(str(1.2))        #float to string
print(str(True))       #bool to string
print(str(False))      #bool to string
print(str(1+2j))       #complex to string
print(str(0b1011))     #binary to string
print(str(0o341))      #octal to string
print(str(0x21))       #hexadecimal to string