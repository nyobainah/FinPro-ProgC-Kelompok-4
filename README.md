# Tumor-Immune Dynamics Simulation in C

Simulasi dinamika sel tumor, sel sehat, dan sel imun menggunakan model **Lotka-Volterra** dengan metode numerik **Euler**, diimplementasikan dalam bahasa C.

## Model

Sistem tiga ODE yang diselesaikan secara simultan:

```
dH/dt = rH·H·(1 - H/kH) - β·H·T
dT/dt = rT·T·(1 - T/kT) + β·H·T - α·I·T
dI/dt = γ·I·T - δ·I
```

| Simbol | Deskripsi |
|--------|-----------|
| `H` | Sel sehat |
| `T` | Sel tumor |
| `I` | Sel imun |
| `rH`, `rT` | Laju pertumbuhan sel sehat / tumor |
| `kH`, `kT` | Kapasitas tampung sel sehat / tumor |
| `β` | Koefisien interaksi sel sehat terhadap tumor |
| `α` | Efektivitas sel imun membunuh tumor |
| `γ` | Laju stimulasi sel imun oleh tumor |
| `δ` | Laju kematian alami sel imun |

## Cara Pakai

**Kompilasi:**
```bash
gcc main.c -o tumor_simulation -lm
```

**Jalankan:**
```bash
./tumor_simulation
```

## Skenario

Terdapat 4 skenario yang dapat dipilih melalui menu interaktif.

Parameter tetap pada semua skenario bawaan:

| Parameter | Nilai |
|-----------|-------|
| `rH` | 0.03 |
| `kH` | 1000.0 |
| `kT` | 800.0 |
| `β` | 0.00005 |
| `δ` | 0.02 |

---

### Skenario 1 - Respons Imun Lemah

Sistem imun tidak cukup efektif untuk membendung pertumbuhan tumor. Sel imun ada, tetapi kemampuan membunuh tumor (`α`) sangat rendah sehingga tumor berpotensi terus berkembang.

| Parameter | Nilai |
|-----------|-------|
| `rT` | 0.08 |
| `α` | 0.00005 |

---

### Skenario 2 - Respons Imun Kuat

Sistem imun bekerja efektif. Nilai `α` empat kali lebih besar dari skenario 1, sehingga sel imun mampu menekan pertumbuhan tumor secara signifikan.

| Parameter | Nilai |
|-----------|-------|
| `rT` | 0.08 |
| `α` | 0.0002 |

---

### Skenario 3 - Tumor Agresif

Tumor tumbuh hampir dua kali lebih cepat dibanding skenario 1 dan 2. Meskipun respons imun moderat, laju proliferasi tumor yang tinggi menantang kemampuan sistem imun untuk mengendalikannya.

| Parameter | Nilai |
|-----------|-------|
| `rT` | 0.15 |
| `α` | 0.0001 |

---

### Skenario 4 - Parameter Kustom

Pengguna memasukkan seluruh parameter secara manual melalui terminal, termasuk `γ` (laju stimulasi imun) yang tidak tersedia di skenario bawaan.

```
Healthy cell growth rate (rH)      :
Healthy cell carrying capacity (kH):
Tumor growth rate (rT)             :
Tumor carrying capacity (kT)       :
Healthy-to-tumor interaction (beta):
Immune killing effectiveness (alpha):
Immune stimulation rate (gamma)    :
Immune natural death rate (delta)  :
```

## Output

Hasil simulasi tersimpan otomatis ke `hasil_simulasi.csv`:

```
Time,HealthyCells,TumorCells,ImmuneCells
0.00,900.0000,50.0000,20.0000
0.10,899.8712,50.3421,20.1123
...
```

Ringkasan nilai akhir juga ditampilkan di terminal setelah simulasi selesai.

## Persyaratan

- GCC atau compiler C lainnya
- Tidak ada dependensi eksternal
