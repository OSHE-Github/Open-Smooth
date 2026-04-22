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


# Assembly Overview
### 1. Print All Components
- 3D print all required parts using PETG filament
- Base components (13 parts)
- Filter components (9 parts)
- Rotating table components (4 parts) + servo housing (1 part)
- Recommended to have ~2kg of filament available
- Use supports only where necessary (mainly the table)

### 2. Assemble the Base
- Fit all base components together using the dovetail joints
- Ensure correct orientation (parts only fit one way)
- Press-fit assembly should hold the structure together
- Apply epoxy if additional strength is needed

### 3. Prepare and Assemble the Lid
- Cut and drill openings for:
  - Heater (rear-center)
  - Filter (top-center)
- Mount heater:
  - Cut a circular hole for the heater body
  - Drill mounting holes
  - Install the gasket and secure the heater
- Mount filter:
  - Cut a square intake hole
  - Drill mounting holes (M3)
- Install a limit switch at the bottom edge of the lid to detect the open/closed state


### 4. Assemble and Install the Filter
- Assemble the main filter housing using M3 screws
- Install a 60 mm fan and secure it with M4 screws
- Prepare pellet drawer:
  - Epoxy if printed in two parts
  - Fill with carbon pellets
- Insert pellet drawer and secure with clips and screws
- Cut mounting holes and vent in enclosure
- Attach filter and gasket to enclosure

### 5. Install the Rotating Table System
- Mount the servo into the servo housing
- Route wires through housing cutouts
- Install housing into base (center cutout)
- Attach the spur gear to the servo shaft
- Install the table spacer and the rotating table
- Snap the fan grille into place

### 6. Assemble Atomizers
- Assemble each atomizer:
  - Insert wick into atomizer
  - Secure wick using trimmed nail or pin
- Extend wiring to reach the control PCB
- Repeat for all atomizers
- Fill with acetone and place into holders

### 7. Final Assembly & Integration
- Ensure all mechanical components are secured
- Verify moving parts (table rotation, fan clearance)
- Confirm proper placement of heater, filter, and sensors
- Connect electronics (fans, heater, atomizers, sensors, etc.)
- Perform a system check before operation

### 8. Final Checks
- Verify all fasteners are tight
- Ensure no air leaks around the filter and heater
- Confirm limit switch functionality
- Test electrical connections safely

**Note:**  
Epoxy is optional in most areas but recommended for long-term durability.


# Future Improvements
### Enclosure Stability and Sealing Capability
The enclosure currently uses duct tape to keep a seal with the lid. This works well, but it could be improved. Adding a lid locking mechanism with a layered rubber seal at the base would prevent the lid from unintentionally opening as well as provide a better seal.

### Atomizer bottles
The atomizer bottles we used for this project are made of PET plastic. PET plastic is susceptible to acetone over long periods of time, causing the bottles to likely leak. In our testing, the bottles showed minimal wear, but this doesn't mean they are 100% safe. Bottles made of PP or HDPE plastic would be much better suited for this application.
