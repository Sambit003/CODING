# built in mathematical functions
print(abs(-25))                     #absolute value
print(pow(2,4))                     #power
print(round(3.146579172))           #round off to nearest integer value
print(round(3.146579172,0))         #round off to nearest integer value with 0 decimal places after the decimal point
print(round(3.146579172,1))         #round off to 1 decimal places  #2nd argument is optional
print(round(3.146579172,2))         #round off to 2 decimal places  #2 is the second argument
print(round(3.146579172,3))         #round off to 3 decimal places  #3 is the second argument
print(round(3.146579172,4))         #round off to 4 decimal places  #4 is the second argument
print(round(3.146579172,5))         #round off to 5 decimal places  #5 is the second argument
print(round(3.146579172,6))         #round off to 6 decimal places  #6 is the second argument
print(round(3.146579172,7))         #round off to 7 decimal places  #7 is the second argument
print(min(10,20,30,40,50))          #minimum value in a list of arguments
print(max(10,20,30,40,50))          #maximum value in a list of arguments
print(sum([10,20,30,40,50]))        #sum of values in a list of arguments
print(sum([10,20,30,40,50],100))    #sum with initial value  #100 is the initial value
print(sum([10,20,30,40,50],-100))   #sum with initial value  #-100 is the initial value
print(sum([10,20,30,40,50],0))      #sum with initial value  #0 is the initial value  #default initial value is 0  #sum([10,20,30,40,50]) is same as sum([10,20,30,40,50],0)
print(divmod(17,3))                 #quotient and remainder  #divmod(17,3) is same as (17//3,17%3)  #17//3 is quotient and 17%3 is remainder  #17//3 is 5 and 17%3 is 2
print(bin(64),oct(64),hex(64))      #binary, octal and hexadecimal   #bin(64) is same as bin(0b1000000)  #oct(64) is same as oct(0o100)  #hex(64) is same as hex(0x40)
print(bin(0b1000000),oct(0o100),hex(0x40))  #binary, octal and hexadecimal   #bin(0b1000000) is same as bin(64)  #oct(0o100) is same as oct(64)  #hex(0x40) is same as hex(64)

