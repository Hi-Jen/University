import tkinter as tk
import pygame
import soundfile as sf
import numpy as np
import os
from datetime import datetime

pygame.mixer.init()
octave_notes = ['C4', 'D4', 'E4', 'F4', 'G4', 'A4', 'B4', 'C5']
korean_notes = ['도', '레', '미', '파', '솔', '라', '시', '도']
instrument = 'piano'
recorded_data = []

def get_sample_path(note):
    return f"{instrument}_samples/{note}.wav"

def play_note(note):
    global recorded_data
    path = get_sample_path(note)
    try:
        pygame.mixer.music.load(path)
        pygame.mixer.music.play()
        data, samplerate = sf.read(path)
        recorded_data.append(data)
        status_label.config(text=f"{note} 음 재생 중")
    except Exception as e:
        status_label.config(text=f"{note} 음 재생 실패: {e}")

def save_recording():
    if not recorded_data:
        status_label.config(text="녹음된 내용이 없습니다.")
        return
    try:
        output = np.concatenate(recorded_data, axis=0)
        os.makedirs("recording", exist_ok=True)
        now = datetime.now().strftime("%Y%m%d_%H%M%S")
        output_path = f"recording/recording_{now}.wav"
        sf.write(output_path, output, 44100)
        status_label.config(text=f"녹음 저장 완료: {output_path}")
    except Exception as e:
        status_label.config(text=f"녹음 저장 오류: {e}")

root = tk.Tk()
root.title("악기 연주 GUI")
root.geometry("1200x400")
root.configure(bg="#f0f0f0")

title_label = tk.Label(root, text="🎹 피아노 연주 🎶", font=('Arial', 20, 'bold'), bg="#f0f0f0", fg="#333")
title_label.pack(pady=15)

frame = tk.Frame(root, bg="#f0f0f0")
frame.pack(pady=10)

for note, kor_note in zip(octave_notes, korean_notes):
    btn = tk.Button(frame, text=f"{kor_note} ({note})", width=12, height=2,
                    font=('Arial', 12, 'bold'),
                    bg="#4CAF50", fg="white",
                    activebackground="#45A049", activeforeground="white",
                    relief="raised", bd=3,
                    command=lambda n=note: play_note(n))
    btn.pack(side=tk.LEFT, padx=8, pady=5)

save_btn = tk.Button(root, text="💾 녹음 저장", font=('Arial', 14, 'bold'),
                     bg="#2196F3", fg="white",
                     activebackground="#1976D2", activeforeground="white",
                     relief="raised", bd=3,
                     command=save_recording)
save_btn.pack(pady=15)

status_label = tk.Label(root, text="", font=('Arial', 12), bg="#f0f0f0", fg="#333")
status_label.pack()

root.mainloop()
