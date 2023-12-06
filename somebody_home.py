import tkinter as tk
# import pygame

class SomebodyHomeApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Somebody's home!")
        self.root.geometry("800x480")

        # Initialize pygame for sound
        # pygame.mixer.init()

        # Load the sparkle sound
        # self.sparkle_sound = pygame.mixer.Sound("sparkle.mp3")

        # Create a canvas to draw the gradient background and text
        self.canvas = tk.Canvas(self.root, width=800, height=480, highlightthickness=0)
        self.canvas.pack()

        # Create a smooth gradient background from orange to pink
        self.create_gradient_background()

    def create_gradient_background(self):
        # Create a smooth gradient from orange to pink
        for i in range(480):
            red_value = int(255-(i / 480) * (255-255))
            green_value = int((i / 480) * 69)
            blue_value = int((i / 480) * 180)

            color = "#{:02x}{:02x}{:02x}".format(red_value, green_value, blue_value)

            # Draw a line of the gradient
            self.canvas.create_line(0, i, 800, i, fill=color, width=1)

        # Draw the text on the canvas (initially hidden)
        self.text = "Somebody's home!"
        self.text_ids = []

        # Adjusted spacing between letters
        letter_spacing = 32

        # Create individual text items for each letter
        for i, char in enumerate(self.text):
            x_position = 400 - (len(self.text) // 2 - i) * letter_spacing
            text_id = self.canvas.create_text(x_position, 240, text=char, font=("Quicksand Bold", 40), fill="white", state=tk.HIDDEN)
            self.text_ids.append(text_id)

        # Start the text reveal animation
        self.reveal_text()

        # Play the sparkle sound effect
        # self.sparkle_sound.play()
        
        self.root.after(5000, self.close_window)

    def reveal_text(self, index=0):
        # Make each letter visible one by one
        self.canvas.itemconfig(self.text_ids[index], state=tk.NORMAL)
        self.canvas.update()

        # Wait for a short duration
        self.root.after(100)

        # Move to the next letter
        index += 1

        # Schedule the next iteration if there are more letters
        if index < len(self.text):
            self.root.after(10, self.reveal_text, index)

    def close_window(self):
    	self.root.destroy()
    	
if __name__ == "__main__":
    root = tk.Tk()
    app = SomebodyHomeApp(root)
    root.mainloop()
