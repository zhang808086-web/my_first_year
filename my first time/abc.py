import tkinter as tk
import pygame
from PIL import Image,ImageTk
from pygame.examples.cursors import image

pygame.mixer.init()
bgm = 'bgm.mp3'
image_files = ['image1.jpg','image2.jpg','image3.jpg']

postcards = [
    "这是第一张明信片的内容",
    "2",
    "第三张明信片"
]


with open('../c.txt.txt', mode ='rt', encoding ='utf-8') as f1:
    word = f1.read()
    postcards[1] = word

class PostcardApp:
    def __init__(self, root):
        self.root = root
        self.root.title("信应用")

        self.current_index = 0

        self.image_label = tk.Label(root)
        self.image_label.pack(pady = 10)
        self.page_image()


        self.postcard_label = tk.Label(root, text=postcards[self.current_index], font=("Arial", 20,'italic'), padx=20, pady=20)
        self.postcard_label.pack(pady=20)

        self.prev_button = tk.Button(root, text="上一页", command=self.prev_page)
        self.prev_button.pack(side=tk.LEFT, padx=20)

        self.next_button = tk.Button(root, text="下一页", command=self.next_page)
        self.next_button.pack(side=tk.RIGHT, padx=20)

        pygame.mixer.music.load(bgm)
        pygame.mixer.music.play(-1)

    def prev_page(self):
        if self.current_index > 0:
            self.current_index -= 1
            self.postcard_label.config(text=postcards[self.current_index])
            self.page_image()

    def next_page(self):
        if self.current_index < len(postcards) - 1:
            self.current_index += 1
            self.postcard_label.config(text=postcards[self.current_index])
            self.page_image()

    def page_image(self):
        if 0<=self.current_index<len(image_files):
            image = Image.open(image_files[self.current_index])
            image = image.resize((300,200), Image.LANCZOS)
            photo = ImageTk.PhotoImage(image)
            self.image_label.config(image = photo)
            self.image_label.photo = photo




if __name__ == "__main__":
    root = tk.Tk()
    app = PostcardApp(root)
    root.mainloop()
    pygame.mixer.music.stop()
    pygame.mixer.quit()







