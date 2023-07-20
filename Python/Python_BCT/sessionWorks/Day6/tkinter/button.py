from tkinter import *
root = Tk()
root.geometry('600x600')
root.config(background='steelblue')
root.state('zoomed')
root.title('desktop Application')

def how():
    print('I am fine')
how = Button(root, text='How are you?', bg='red', fg='white', font=('arial', 20, 'bold'), command=how)
how.place(x=0,y=0)

def name():
    print('My name is SAMBIT')

name = Button(root, text='Name', bg='green', fg='white', font=('arial', 20, 'bold'), command=name)
name.place(x=0,y=50)

def college():
    print('I am from Narula Institute of Technology')

college = Button(root, text='College?', bg='blue', fg='white', font=('arial', 20, 'bold'), command=college)
college.place(x=0,y=100)

def age():
    print('I am 20 years old')

age = Button(root, text='How old am I?', bg='yellow', fg='black', font=('arial', 20, 'bold'), command=age)
age.place(x=0,y=150)

def address():
    print('I am from Kolkata')

address = Button(root, text='Where do yI live?', bg='orange', fg='black', font=('arial', 20, 'bold'), command=address)
address.place(x=0,y=200)




root.mainloop()