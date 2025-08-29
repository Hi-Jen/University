import os
import librosa
import soundfile as sf
import numpy as np

START_TIME = 37.0
DURATION = 10.0

file_paths = [
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order2_3kHz.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order4_18kHz_PhaseSafe.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order4_20kHz_HiFi.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order6_3kHz.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order6_5kHz.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order6_15kHz_MusicZone.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order6_18kHz_Balanced.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order8_12kHz_DynamicSlope.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order8_15kHz_NoiseSensitive.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order10_3kHz.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival.wav", 
]

original_file = r"C:\Users\tv365\Desktop\newjeans\newjeans_festival.wav"

def extract_segment(filepath, output_path, start_sec, duration_sec):
    y, sr = librosa.load(filepath, sr=None, offset=start_sec, duration=duration_sec)
    sf.write(output_path, y, sr)

def calculate_snr(original, processed):
    noise = original - processed
    signal_power = np.mean(original**2)
    noise_power = np.mean(noise**2)
    snr = 10 * np.log10(signal_power / (noise_power + 1e-10))
    return snr

base_dir = os.path.dirname(original_file)
original_10s_path = os.path.join(base_dir, "newjeans_festival_10s.wav")
extract_segment(original_file, original_10s_path, START_TIME, DURATION)

original_10s, sr = librosa.load(original_10s_path, sr=None)

print("SNR 분석 결과:\n")

self_snr = calculate_snr(original_10s, original_10s)
print(f"원본 자기자신(newjeans_festival_10s.wav): SNR = {self_snr:.2f} dB")

for filepath in file_paths:
    name = os.path.splitext(os.path.basename(filepath))[0]
    output_path = os.path.join(base_dir, f"{name}_10s.wav")

    extract_segment(filepath, output_path, START_TIME, DURATION)

    if "festival.wav" not in filepath:
        y, _ = librosa.load(output_path, sr=None)
        y = librosa.util.fix_length(y, size=len(original_10s))
        snr = calculate_snr(original_10s, y)
        print(f"{name}: SNR = {snr:.2f} dB")
