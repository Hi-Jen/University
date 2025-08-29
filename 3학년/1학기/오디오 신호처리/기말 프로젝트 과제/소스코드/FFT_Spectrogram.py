import matplotlib.pyplot as plt
import numpy as np
from scipy.io import wavfile
from scipy.signal import spectrogram

sample_rate, audio_data = wavfile.read(r"C:\Users\tv365\Desktop\newjeans\newjeans_festival.wav")

if audio_data.ndim > 1:
    audio_data = audio_data[:, 0]

t = np.linspace(0, len(audio_data) / sample_rate, num=len(audio_data))

frequencies, times, Sxx = spectrogram(audio_data, fs=sample_rate)
Sxx_dB = 10 * np.log10(Sxx + 1e-10)

fig, axs = plt.subplots(1, 2, figsize=(14, 5))

axs[0].plot(t, audio_data, color='blue')
axs[0].set_title("Waveform (Original Audio)")
axs[0].set_xlabel("Time (seconds)")
axs[0].set_ylabel("Amplitude")

pcm = axs[1].pcolormesh(times, frequencies, Sxx_dB, shading='gouraud', cmap='viridis')
axs[1].set_title("Spectrogram of Audio")
axs[1].set_xlabel("Time (s)")
axs[1].set_ylabel("Frequency [Hz]")
fig.colorbar(pcm, ax=axs[1], label='Intensity [dB]')

plt.tight_layout()
plt.show()
