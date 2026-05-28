# Tumor-Immune Dynamics Simulation in C

Simulasi dinamika sel tumor, sel sehat, dan sel imun menggunakan model **Lotka-Volterra** dengan metode numerik **Euler**, diimplementasikan dalam bahasa C.

## Model

Sistem tiga ODE yang diselesaikan secara simultan:

```
dH/dt = rH·H·(1 - H/kH) - β·H·T
dT/dt = rT·T·(1 - T/kT) + β·H·T - α·I·T
dI/dt = γ·I·T - δ·I
```

- `H` — sel sehat, `T` — sel tumor, `I` — sel imun

## Cara Pakai

**Kompilasi:**
```bash
gcc tumor_simulation.c -o tumor_simulation -lm
```

**Jalankan:**
```bash
./tumor_simulation
```

Pilih skenario di menu, masukkan kondisi awal dan pengaturan waktu, lalu hasil tersimpan otomatis ke `hasil_simulasi.csv`.

## Skenario

| # | Nama | rT | α |
|---|------|----|---|
| 1 | Respons imun lemah | 0.08 | 0.00005 |
| 2 | Respons imun kuat | 0.08 | 0.0002 |
| 3 | Tumor agresif | 0.15 | 0.0001 |
| 4 | Parameter kustom | — | — |

## Output

File `hasil_simulasi.csv` berisi data per timestep:

```
Time,HealthyCells,TumorCells,ImmuneCells
0.00,900.0000,50.0000,20.0000
0.10,899.8712,50.3421,20.1123
...
```

## Persyaratan

- GCC atau compiler C lainnya
- Tidak ada dependensi eksternal
