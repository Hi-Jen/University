import numpy as np
import scipy.signal as signal
import matplotlib.pyplot as plt
import soundfile as sf
import os

file_path = r"C:\Users\tv365\Desktop\newjeans\newjeans_festival.wav"
if not os.path.exists(file_path):
    raise FileNotFoundError("지정한 경로에 파일이 없습니다.")

data, samplerate = sf.read(file_path)
print(f"샘플링 주파수: {samplerate} Hz, 데이터 shape: {data.shape}")

def rms(x):
    return np.sqrt(np.mean(np.square(x)))

experiments = [
    ("LPF_Order6_3kHz", 6, 3000),                     # 기준 필터 – 차수: 6, 컷오프: 3kHz
    ("LPF_Order10_3kHz", 10, 3000),                   # 높은 차수 – 차수: 10, 컷오프: 3kHz
    ("LPF_Order2_3kHz", 2, 3000),                     # 낮은 차수 – 차수: 2, 컷오프: 3kHz
    ("LPF_Order6_5kHz", 6, 5000),                     # 중역 일부만 보존 – 차수: 6, 컷오프: 5kHz
    ("LPF_Order6_15kHz_MusicZone", 6, 15000),         # 음악 정보 보존 + 초고역 노이즈 제거 – 차수: 6, 컷오프: 15kHz
    ("LPF_Order8_12kHz_DynamicSlope", 8, 12000),      # 디지털 노이즈 제거 – 차수: 8, 컷오프: 12kHz
    ("LPF_Order4_18kHz_PhaseSafe", 4, 18000),         # 위상 왜곡 최소화 – 차수: 4, 컷오프: 18kHz
    ("LPF_Order4_20kHz_HiFi", 4, 20000),              # 고품질 음악 감상 – 차수: 4, 컷오프: 20kHz
    ("LPF_Order6_18kHz_Balanced", 6, 18000),          # 일반 재생 균형 – 차수: 6, 컷오프: 18kHz
    ("LPF_Order8_15kHz_NoiseSensitive", 8, 15000),    # 노이즈 민감 환경 – 차수: 8, 컷오프: 15kHz
]



original_rms = rms(data) if data.ndim == 1 else np.array([rms(data[:, ch]) for ch in range(data.shape[1])])

# 시각화 저장 폴더
plot_dir = os.path.join(os.path.dirname(file_path), "plots")
os.makedirs(plot_dir, exist_ok=True)

for label, order, cutoff_hz in experiments:
    nyquist = 0.5 * samplerate
    normalized_cutoff = cutoff_hz / nyquist
    b, a = signal.butter(order, normalized_cutoff, btype='low')

    # 필터 주파수 응답 시각화
    w, h = signal.freqz(b, a, worN=8000)
    plt.figure(figsize=(8, 4))
    plt.plot((w / np.pi) * nyquist, 20 * np.log10(abs(h)), 'b')
    plt.title(f"Frequency Response: {label}")
    plt.xlabel("Frequency [Hz]")
    plt.ylabel("Gain [dB]")
    plt.grid()
    plt.tight_layout()
    plt.savefig(os.path.join(plot_dir, f"{label}_freq_response.png"))
    plt.close()

    # 필터링
    if data.ndim == 2:
        filtered = np.zeros_like(data)
        for ch in range(data.shape[1]):
            if len(data[:, ch]) <= 3 * max(len(a), len(b)):
                raise ValueError(f"{label} - 채널 {ch}의 길이가 필터 패딩보다 짧습니다.")
            filtered[:, ch] = signal.filtfilt(b, a, data[:, ch])
            filtered_rms = rms(filtered[:, ch])
            gain = original_rms[ch] / filtered_rms if filtered_rms > 0 else 1.0
            filtered[:, ch] *= gain
    else:
        if len(data) <= 3 * max(len(a), len(b)):
            raise ValueError(f"{label} - 오디오 길이가 필터 패딩보다 짧습니다.")
        filtered = signal.filtfilt(b, a, data)
        filtered_rms = rms(filtered)
        gain = original_rms / filtered_rms if filtered_rms > 0 else 1.0
        filtered *= gain

    output_path = file_path.replace(".wav", f"_{label}.wav")
    sf.write(output_path, filtered, samplerate)
    print(f"{label} - 저장 완료: {output_path}")
