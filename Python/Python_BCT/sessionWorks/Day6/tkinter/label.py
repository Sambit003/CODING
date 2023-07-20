from tkinter import *

root = Tk()

root.geometry("600x600+700+50")
root.config(bg="steelblue")

# Label
label1 = Label(root, text="Library Management System", bg="red", fg="white", font=("Times new roman", 20, "bold"))
label1.pack()

label2 = Label(root, text="Welcome to Library", bg="green", fg="white", font=("Times new roman", 20, "bold"))
label2.place(x=0, y=100)

root.mainloop()