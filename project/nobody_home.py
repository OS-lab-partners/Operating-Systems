import tkinter as tk

class NobodyHomeApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Nobody Home...")
        self.root.geometry("800x480")

        self.canvas = tk.Canvas(self.root, width=800, height=480, highlightthickness=0)
        self.canvas.pack()

        self.create_gradient_background()

    def create_gradient_background(self):
        # creates gradient from blue to green
        for i in range(480):
            red_value = 0
            green_value = int((i / 480) * 255)
            blue_value = int((i / 480) * 255)

            color = "#{:02x}{:02x}{:02x}".format(red_value, green_value, blue_value)

            self.canvas.create_line(0, i, 800, i, fill=color, width=1)

        # text initially hidden
        self.text = "Nobody home..."
        self.text_ids = []

        letter_spacing = 32

        # create individual text items for each letter
        for i, char in enumerate(self.text):
            x_position = 400 - (len(self.text) // 2 - i) * letter_spacing
            text_id = self.canvas.create_text(x_position, 240, text=char, font=("Quicksand Bold", 40), fill="white", state=tk.HIDDEN)
            self.text_ids.append(text_id)

        self.reveal_text()
        
        self.root.after(5000, self.close_window)

    def reveal_text(self, index=0):
        # make each letter visible one by one
        self.canvas.itemconfig(self.text_ids[index], state=tk.NORMAL)
        self.canvas.update()

        self.root.after(100)

        # move to the next letter
        index += 1

        # schedule the next iteration if there are more letters
        if index < len(self.text):
            self.root.after(10, self.reveal_text, index)

    def close_window(self):
    	self.root.destroy()

if __name__ == "__main__":
    root = tk.Tk()
    app = NobodyHomeApp(root)
    root.mainloop()
