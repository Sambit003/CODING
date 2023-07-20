import tkinter as tk
class BankManagementSystem:
    def __init__(self, master):
        self.master = master
        self.master.title("Bank Management System")
menu_bar = tk.Menu(self.master)
self.master.config(menu=menu_bar)

file_menu = tk.Menu(menu_bar)
file_menu.add_command(label="New Account")
file_menu.add_command(label="Open Account")  
file_menu.add_separator()
file_menu.add_command(label="Exit", command=self.master.quit)
menu_bar.add_cascade(label="File", menu=file_menu)

view_menu = tk.Menu(menu_bar)
view_menu.add_command(label="View Account")
menu_bar.add_cascade(label="View", menu=view_menu)

transaction_menu = tk.Menu(menu_bar)
transaction_m
def new_account(self):
    new_account_frame = tk.Frame(self.master)
    new_account_frame.pack()

    tk.Label(new_account_frame, text="Account Number:").grid(row=0, column=0)
    account_number_entry = tk.Entry(new_account_frame)
    account_number_entry.grid(row=0, column=1)

    tk.Label(new_account_frame, text="Account Name:").grid(row=1, column=0)
    account_name_entry = tk.Entry(new_account_frame)
    account_name_entry.grid(row=1, column=1)

    # add more widgets as needed
def deposit(self):
    deposit_frame = tk.Frame(self.master)
    deposit_frame.pack()

    tk.Label(deposit_frame, text="Account Number:").grid(row=0, column=0)
    account_number_entry = tk.Entry(deposit_frame)
    account_number_entry.grid(row=0, column=1)

    tk.Label(deposit_frame, text="Amount:").grid(row=1, column=0)
    amount_entry = tk.Entry(deposit_frame)
    amount_entry.grid(row=1, column=1)

    # add more widgets as needed
file_menu.add_command(label="New Account", command=self.new_account)
transaction_menu.add_command(label="Deposit", command=self.deposit)
if __name__ == "__main__":
    root = tk.Tk()
    BankManagementSystem(root)
    root.mainloop()