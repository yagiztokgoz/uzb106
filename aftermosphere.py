import tkinter as tk 
from tkinter import messagebox
from PIL import ImageTk, Image


class LoginPage(tk.Tk):
    
    def __init__(self, *args, **kwargs):

        tk.Tk.__init__(self)

        self.geometry("626x431")
        self.resizable(0, 0)


        main_frame = tk.Frame(self, width=600, height=400)
        main_frame.pack()
        main_frame.anchor(anchor="center")

        image = Image.open("earth.jpg")
        image = ImageTk.PhotoImage(image)

        label = tk.Label(main_frame, image=image)
        label.pack()


        title_styles = {"font": ("Trebuchet Ms Bold", 16), "background": "blue"}

        text_styles = {"font": ("Verdana", 14),
                    "background": "blue",
                    "foreground": "#E1FFFF"}


        frame_login = tk.Frame(main_frame, bg="blue", relief="groove", bd=2)
        frame_login.place(rely = 0.30, relx=0.17, height=130, width=400)

        label_title = tk.Label(frame_login, title_styles, text="Login to Aftermosphere")
        label_title.grid(row=0, column=1, columnspan=1)

        label_user = tk.Label(frame_login, text_styles, text="Username:")
        label_user.grid(row=1, column=0)

        label_pw = tk.Label(frame_login, text_styles, text="Password:")
        label_pw.grid(row=2, column=0)

        entry_user = tk.Entry(frame_login, width=45, cursor="xterm")
        entry_user.grid(row=1, column=1)

        entry_pw = tk.Entry(frame_login, width=45, cursor="xterm", show="*")
        entry_pw.grid(row=2, column=1)

        button = tk.Button(frame_login, text="Login", command= lambda: get_login())
        button.place(rely=0.70, relx=0.50)

        signup_button = tk.Button(frame_login, text="Sign Up", command=lambda: get_signup())
        signup_button.place(rely=0.70, relx=0.75)


        def get_signup():

            SignupPage()

        def get_login():

            username = entry_user.get()
            password = entry_pw.get()

            validation = validate(username, password)


            if validation:
                tk.messagebox.showinfo("Aftermosphere - Login Succesful", "Welcome {}!".format(username))

                top.destroy()

            elif username == "" or password == "":
                tk.messagebox.showerror("Aftermosphere - Warning", "Fields must not be empty.")

            else:
                tk.messagebox.showerror("Aftermosphere - Warning", "The username or password you have entered are incorrect.")


        def validate(username, password):

            try:
                with open("users.txt", "r") as users:
                    for line in users:
                        line = line.split(",")

                        if line[1] == username and line[3] == password:
                            return True
                        
                    return False

            except FileNotFoundError:
                pass


class SignupPage(tk.Tk):

    def __init__(self, *args, **kwargs):
        tk.messagebox.showerror("Aftermoshpere - Warning", "You need to ask to Yagiz for registration.")



top = LoginPage()
top.title("Aftermosphere - Ground Control Software -")


top.mainloop()