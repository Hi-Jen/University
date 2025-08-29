import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy.signal import spectrogram

file_paths = [
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival.wav",  
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order4_20kHz_HiFi.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order6_18kHz_Balanced.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order8_15kHz_NoiseSensitive.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order2_3kHz.wav",
    r"C:\Users\tv365\Desktop\newjeans\newjeans_festival_LPF_Order4_18kHz_PhaseSafe.wav"
]


num_files = len(file_paths)
ncols = 3
nrows = int(np.ceil(num_files / ncols))
fig, axes = plt.subplots(nrows=nrows, ncols=ncols, figsize=(18, nrows * 3), dpi=120)
axes = axes.flatten()

for i, path in enumerate(file_paths):
    sample_rate, data = wavfile.read(path)
    if data.ndim > 1:
        data = data[:, 0]

    f, t, Sxx = spectrogram(data, fs=sample_rate, nperseg=1024, noverlap=512)
    Sxx_dB = 10 * np.log10(Sxx + 1e-10)

    ax = axes[i]
    im = ax.pcolormesh(t, f, Sxx_dB, shading='gouraud', cmap='magma')
    
    filename = os.path.basename(path).replace("newjeans_festival_", "").replace(".wav", "")
    if filename == "newjeans_festival":
        filename = "Original"
    else:
        filename = filename.replace("Order", "O").replace("cutoff", "C").replace("kHz", "k")

    ax.set_title(filename, fontsize=9)
    ax.set_ylabel('Freq [Hz]')
    ax.set_xlabel('Time [s]')
    ax.set_ylim(0, 20000)

for j in range(i+1, len(axes)):
    fig.delaxes(axes[j])

plt.tight_layout()
plt.subplots_adjust(top=0.92, wspace=0.3, hspace=0.4)
plt.suptitle("Spectrogram Comparison of Filtered Audio", fontsize=16)

fig.colorbar(im, ax=axes.tolist(), orientation='vertical', fraction=0.02, pad=0.02)

plt.show()
