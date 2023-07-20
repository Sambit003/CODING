from tkinter import *
root = Tk()
root.geometry('600x600')
root.config(background='steelblue')
root.state('zoomed')
root.title('desktop Application')

lable1=Label(root, text = "Register here ->", font = ("Times new roman", 24, "bold"))
lable1.pack()

userName = Label(root, text = "Username", font = ("Times new roman", 24, "bold"), fg="white", bg="steelblue")
userName.place(x=50, y=100)

entry1 = Entry(root, font = ("Times new roman", 24, "bold"))
entry1.place(x=200, y=100)

email

root.mainloop()