
# 🏋️‍♀️ Digital Weighing Scale Using 4 Load Cells and HX711

This project implements a digital weighing scale using **4 load cells**, **HX711 amplifiers**, and an **Arduino microcontroller** with **LCD (I2C)** output. Designed for accurate multi-point weight sensing, the system can measure up to **18 kg** with a **resolution of 0.1 kg**, ideal for lab or domestic applications.

---

## 📦 Features

- ✔️ **Measures weight up to 18 kg**  
- ✔️ **Resolution of 0.1 kg**
- ✔️ Uses **4 load cells** for accurate, evenly distributed sensing
- ✔️ Calibration routine included via serial interface
- ✔️ Real-time output on **16x2 I2C LCD display**
- ✔️ Stable and modular mechanical design with **metal base & top plates**
- ✔️ Experimental comparison using **1 HX711 + switch circuit**
- ✔️ Readings from all 4 sensors aggregated for more precise output

---

## 🧰 Hardware Components

| Component         | Quantity | Description                                  |
|------------------|----------|----------------------------------------------|
| Load Cell (5kg)  | 4        | Measures individual corner weights           |
| HX711 Amplifier  | 4        | 24-bit ADC for converting analog signals     |
| Arduino UNO/Nano | 1        | Main microcontroller                         |
| LCD I2C Display  | 1        | 16x2 character screen                         |
| Metal Sheets     | 2        | Platform structure (Top: 20x20 cm, Bottom: 30x30 cm) |
| Screws/Bolts     | -        | For mounting plates and leveling             |

---



## 🧠 Calibration Approach

Each load cell is **individually calibrated** using a known weight placed directly above it. This improves accuracy regardless of where the object is placed on the platform.

### Calibration Formula:
```text
Weight = (r1 - p) * c

Where:
- r1 = reading with unknown weight
- p  = reading with just the plate
- c  = calibration constant = standard weight / (p - r)
````

---

## 🧪 Experimental Setup

### Mechanical Design

* Top Plate: 20×20 cm (metal)
* Bottom Plate: 30×30 cm (metal)
* Each load cell mounted at 45° to distribute force evenly.
* Spacers used for bolt isolation.

### Electrical Design

* Four HX711 modules connect each load cell to the Arduino.
* Shared SCK pin for all HX711s (Pin D3).
* Unique DOUT pins: D2, D4, D5, D6.
* LCD shows real-time total weight.

---

## 🔄 Working Principle

1. On boot, user is prompted to **tare** the setup by removing all weight and pressing a key.
2. The Arduino reads 10 averaged readings per load cell and stores zero values.
3. Continuous readings are taken from each load cell.
4. Total weight is computed and displayed on the **LCD** and **Serial Monitor**.

---

## 🖥️ Output Example

**LCD Display**

```
Total Weight:
3.4271 kg
```

**Serial Monitor**

```
Weight on load cell 1: 0.8754 kg
Weight on load cell 2: 0.8649 kg
Weight on load cell 3: 0.8513 kg
Weight on load cell 4: 0.8355 kg
Total Weight: 3.4271 kg
```

---

## ⚠️ Challenges Faced

* Acrylic top plate bent under heavy loads → Replaced with metal.
* Calibration error due to non-centered weights → Solved using individual calibration.
* Inaccuracy using single HX711 with switching circuit.
* Difficulty measuring very small weights due to heavy top plate (\~2 kg).

---

## 📈 Performance

| Metric       | Value                                   |
| ------------ | --------------------------------------- |
| Max Range    | 0 – 18 kg                               |
| Resolution   | 0.1 kg                                  |
| Accuracy     | Improved by individual cell calibration |
| Update Speed | 10 samples averaged per second          |

---
