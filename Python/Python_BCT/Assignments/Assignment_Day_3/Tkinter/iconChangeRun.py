# Write tkinter program to change the icon of the application

from tkinter import *
from tkinter import messagebox
from tkinter import filedialog
import os

class IconChangeRun:
    def __init__(self):
        self.root = Tk()
        self.root.title("Icon Change Run")
        self.root.geometry("400x400")
        self.root.resizable(0, 0)
        self.root.iconbitmap("images\icon.ico")
        self.root.config(bg="#262626")

        self.iconButton = Button(self.root, text="Change Icon", font=("times new roman", 20), bg="#262626", fg="white", command=self.changeIcon)
        self.iconButton.place(x=100, y=100, width=200, height=50)

        self.root.mainloop()

    def changeIcon(self):
        self.icon = filedialog.askopenfilename(initialdir=os.getcwd(), title="Select Icon", filetypes=(("Icon Files", "*.ico"),))
        self.root.iconbitmap(self.icon)

if __name__ == "__main__":
    IconChangeRun()
