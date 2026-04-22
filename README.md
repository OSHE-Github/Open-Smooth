# Open-Smooth

# Project Overview
OPENSmooth introduces an open-source 3D print post-processor that uses acetone vapor and heat to smooth filament layer lines. The system integrates electronic monitors to regulate exposure time and ensure safe operation, reducing risks associated with manual methods. By combining automated vapor control with real-time safety monitoring, the design provides a low-cost, accessible solution to improve the surface quality of 3D-printed parts.
# Bill of Materials
## Bill of Materials

### Physical Construction
| Category | Item | Part Number | Source | Cost |
|----------|------|------------|--------|------|
| Physical Construction | PETG filament | - | Amazon | $15 (per spool) |
| Physical Construction | Enclosure bin | - | Amazon | $12 |
| Physical Construction | Plastic bottles | - | Amazon | $7 |
| Physical Construction | Fan grill | - | Amazon | $5 |
| Physical Construction | Epoxy | - | Amazon | $8 |

### Electronics
| Category | Item | Part Number | Source | Cost |
|----------|------|------------|--------|------|
| Electronics | Heater | - | Amazon | $35 |
| Electronics | Atomizers | - | Amazon | $23 |
| Electronics | Fans (x2) | - | Amazon | $18 |
| Electronics | E-stop | - | Amazon | $12 |
| Electronics | Touchscreen | - | Amazon | $16 |
| Electronics | Servo | - | Amazon | $19 |
| Electronics | IEC plug | - | Amazon | $8 |
| Electronics | IEC cable | - | Amazon | $6 |
| Electronics | RGB lights | - | Amazon | $13 |

### Circuitry
| Category | Item | Part Number | Source | Cost |
|----------|------|------------|--------|------|
| Circuitry | PCB | - | - | $10 |
| Circuitry | Arduino Mega | - | - | $30 |
| Circuitry | ATMEGA328 (x2) | - | DigiKey | $6 |
| Circuitry | Relays (x2) | - | Amazon | $14 |
| Circuitry | Buck converters | - | Amazon | $8 |
| Circuitry | 2N2222A Transistors (x20) | - | DigiKey | $1 |
| Circuitry | Thermistor | - | - | $8 |
| Circuitry | Acetone sensor | - | - | $8 |
| Circuitry | 12V power supply | - | Amazon | $10 |

### Consumables
| Category | Item | Part Number | Source | Cost |
|----------|------|------------|--------|------|
| Consumables | Acetone | - | Amazon | $10 |
| Consumables | Carbon pellets | - | Amazon | $12 |

---

## Tools Used

### Testing and Planning
| Category | Item | Part Number | Source | Cost |
|----------|------|------------|--------|------|
| Testing and Planning | Breadboard | ZYJ-102 | Adafruit | $5.95 |
| Testing and Planning | Multimeter | Fluke 179 | Fluke | $479.99 |
| Testing and Planning | Oscilloscope | MSO6012A | Test Equity | $2955.00 |

### Assembly
| Category | Item | Part Number | Source | Cost |
|----------|------|------------|--------|------|
| Assembly | Solder Iron | FX-888D | Hakko | $121.47 |
| Assembly | Dremel | - | Milwaukee | - |
| Assembly | Drill | - | Milwaukee | - |

### Programming
| Category | Item | Part Number | Source | Cost |
|----------|------|------------|--------|------|
| Programming | Arduino IDE | Arduino IDE 2.3.2 | Arduino | $0 |

# Future Improvements
### Enclosure Stability and Sealing Capability
The enclosure currently uses duct tape to keep a seal with the lid. This works well but it could be improved. Adding a lid locking mechanism with a layered rubber seal at the base would prevent the lid from unintentionally opening as well as provide a better seal.

### Atomizer bottles
The atomizer bottles we used for this project are made of PET plastic. PET plastic is susceptible to acetone over long periods of time, causing the bottles to likely leak. In our testing the bottles showed minimal wear, but this doesn't mean they are 100% safe. Bottles made of PP or HDPE plastic would be much better suited for this application.
