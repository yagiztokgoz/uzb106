
import tkinter as tk
import time
from PIL import Image, ImageTk
from tkinter import messagebox


login_flag = 0

def login():

    root = tk.Tk()

    root.geometry("700x600")

    frame = tk.Frame(root, width=600, height=400)
    frame.pack()
    frame.place(anchor="center", relx=0.5, rely=0.5)


    image = Image.open("earth.jpg")
    image = ImageTk.PhotoImage(image)

    label = tk.Label(frame, image=image)
    label.pack()


    root.geometry("626x431")
    root.resizable(0, 0)
            
    title_styles = {"font": ("Trebuchet Ms Bold", 16), "background": "#4169E1"}

    text_styles = {"font": ("Verdana", 14),
                        "background": "#3F00FF",
                        "foreground": "#E1FFFF"}


    frame_login = tk.Frame(root, bg="#3F00FF", relief="raised", bd=5)
    frame_login.place(rely = 0.30, relx=0.17, height=140, width=400)


    label_title = tk.Label(frame_login, title_styles, text="Login to Aftermosphere", relief="groove", bd=3)
    label_title.grid(row=0, column=1, columnspan=1)

    label_user = tk.Label(frame_login, text_styles, text="Username:")
    label_user.grid(row=1, column=0)

    label_pw = tk.Label(frame_login, text_styles, text="Password:")
    label_pw.grid(row=2, column=0)

    entry_user = tk.Entry(frame_login, width=45, cursor="xterm", relief="sunken", bd=3)
    entry_user.grid(row=1, column=1)

    entry_pw = tk.Entry(frame_login, width=45, cursor="xterm", show="*", relief="sunken", bd=3)
    entry_pw.grid(row=2, column=1)

    button = tk.Button(frame_login, text="Login", command= lambda: get_login(), relief="raised", bd=3,  bg="#96DED1", activebackground="#7CFC00")
    button.place(rely=0.76, relx=0.50)

    signup_button = tk.Button(frame_login, text="Sign Up", command=lambda: get_signup(), relief="raised", bd=3, bg="#96DED1", activebackground="#7CFC00")
    signup_button.place(rely=0.76, relx=0.75)


    def get_signup():

        tk.messagebox.showerror("Aftermosphere", "You need to ask to Yagiz for registration.")

    def get_login():

        username = entry_user.get()
        password = entry_pw.get()

        validation = validate(username, password)


        if validation:
            tk.messagebox.showinfo("Aftermosphere", "Welcome {}!".format(username))

            global login_flag
            login_flag = 1

            root.quit()
            root.destroy()
            time.sleep(1)

        elif username == "" or password == "":
            tk.messagebox.showerror("Aftermosphere", "Fields must not be empty.")

        else:
            tk.messagebox.showerror("Aftermosphere", "The username or password you have entered are incorrect.")


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


    root.title("Aftermosphere - Ground Control Station - ")
    root.mainloop()

def main_page():

    root = tk.Tk()
    frame = tk.Frame(root, width=1200, height=800)
    frame.pack()

    image = Image.open("sattelite.jpg")
    image = ImageTk.PhotoImage(image)


    root.geometry("1200x800")
    label = tk.Label(frame, image=image)
    label.pack()




    root.mainloop()





if not login_flag:
    login()
    

main_page()