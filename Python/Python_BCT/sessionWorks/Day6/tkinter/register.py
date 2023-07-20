from tkinter import *
import sqlite3

conn = sqlite3.connect('./sessionWorks/Day6/tkinter/library.db')
cr = conn.cursor()
cr.execute('create table if not exists users (username text, email text, password text, address text)')
conn.commit()

root = Tk()

# Global Variables
W = StringVar()
X = StringVar()
Y = StringVar()
Z = StringVar()

# Render the GUI
root.geometry('700x700')
root.config(background='steelblue')
root.state('zoomed')
root.title('desktop Application')

# Frame
frame1=Frame(root, bg='white')
frame1.place(x=100,y=100, width=500, height=500)

registerForm = Label(frame1, text='Register Form', bg='black' ,fg='yellow' ,font=('times new roman', 24, 'bold'))
registerForm.place(x=155,y=10)

userName=Label(frame1, text='Username', bg='white' ,fg='black' ,font=('times new roman', 22, 'bold'))
userName.place(x=10,y=80)
userNameEntry = Entry(frame1, bg='white', fg='grey', font=('times new roman', 22, 'bold'), textvariable=W)
userNameEntry.place(x=150,y=80)

email=Label(frame1, text='Email', bg='white' ,fg='black' ,font=('times new roman', 22, 'bold'))
email.place(x=10,y=150)
emailEntry = Entry(frame1, bg='white', fg='grey', font=('times new roman', 22, 'bold'), textvariable=X)
emailEntry.place(x=150,y=150)

confirmPassword=Label(frame1, text='Password', bg='white' ,fg='black' ,font=('times new roman', 22, 'bold'))
confirmPassword.place(x=10,y=220)
confirmPasswordEntry = Entry(frame1, bg='white', fg='grey', font=('times new roman', 22, 'bold'),textvariable=Y)
confirmPasswordEntry.place(x=150,y=220)

address = Label(frame1, text='Address', bg='white' ,fg='black' ,font=('times new roman', 22, 'bold'))
address.place(x=10,y=290)
addressEntry = Entry(frame1, bg='white', fg='grey', font=('times new roman', 22, 'bold'), textvariable=Z)
addressEntry.place(x=150,y=290, height= 50)

def register():
    cr.execute('insert into users values(?,?,?,?)', (W.get(), X.get(), Y.get(), Z.get()))
    conn.commit()
    print("Data inserted successfully")
    W.set('')
    X.set('')
    Y.set('')
    Z.set('')
    userNameEntry.focus()

register = Button(frame1, text='Register', bg='black', fg='white', font=('times new roman', 22, 'bold'), command=register)
register.place(x=180,y=370)

def reset():
    W.set('')
    X.set('')
    Y.set('')
    Z.set('')
    userNameEntry.focus()
reset = Button(frame1, text='Reset', bg='black', fg='white', font=('times new roman', 22, 'bold'), command=reset)
reset.place(x=300,y=370)

def delete():
    cr.execute('delete from users where email = ?'), (X.get(),)
    conn.commit()
    print("Data deleted successfully")
delete = Button(frame1, text='Delete', bg='red', fg='white', font=('times new roman', 22, 'bold'), command=delete)
delete.place(x=180,y=440)

root.mainloop()