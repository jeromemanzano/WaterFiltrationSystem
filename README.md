# Water Filtration System Controller

This Arduino-based **Water Filtration System** automates the treatment of **waste water**, making it safer for reuse or discharge. It is part of a larger initiative to provide clean water access in the Philippines through a multi-stage filtration process, powered and controlled by microcontroller logic.

> 💧 **This system is being developed in support of a real-world waste water treatment effort. Learn more and support the project here: [GoFundMe – Donate to Help Clean Water in the Philippines](https://www.gofundme.com/f/donate-to-help-clean-water-in-the-philippines)**

---

## Setup Instructions

Before building the project, required libraries must be copied to your Arduino sketchbook's `libraries` folder. This ensures that all dependencies are available for compilation.

### Step 1: Copy Libraries

Run the appropriate script based on your operating system:

* **Windows**:
  Double-click or run the following script in the command line:

  ```bash
  win_copyLib.bat
  ```

* **macOS**:
  Run the following script in your terminal:

  ```bash
  ./macos_copyLib.sh
  ```

> ⚠️ Make sure your Arduino sketchbook location is set properly in the Arduino IDE before running these scripts.

### Step 2: Upload Code

1. Open `WaterFiltrationSystem.ino` in the Arduino IDE.
2. Select the correct board and port from the **Tools** menu.
3. Click **Upload** to flash the firmware onto the board.

## Usage

Once deployed, the controller will:

* Monitor sensor inputs for water levels or flow conditions
* Trigger pumps accordingly to move water through the filtration stages
* Log activity to the serial console or display (optional)
