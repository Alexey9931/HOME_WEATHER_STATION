from tkinter import *

def start_window_interface():
    window = Tk()  # Создаем новое окно
    window.title("Панель управления сервером для HomeWeatherStation")  # Добавляем заголовок окна
    window.geometry('700x400')
    btn_start = Button(window, text="Запуск сервера!")
    btn_start.place(x=300, y=20)
    window.mainloop()  # Запускаем бесконечный цикл окна