AI Hardware Acceleration Study: From Python to C++ Silicon Modeling

Project Status: Complete (Functional C++ Inference Engine)
Domain: Hardware-Software Co-Design / Computer Architecture

1. Project Overview

This project demonstrates the end-to-end workflow of an AI Hardware Architect. The goal was not just to train a model, but to deconstruct it into its raw mathematical primitives and execute it on a custom C++ simulation engine, mimicking the behavior of a dedicated hardware accelerator.

The Pipeline:

1. Training (Python/TensorFlow): A "Golden Reference" model (MLP) trained on MNIST to 91% accuracy.

2. Extraction: Raw weights and biases serialized to CSV, acting as the system "ROM".

3. Simulation (C++): A custom-built, library-free inference engine that mimics the ALU and Memory operations of a hardware accelerator.

2. Technical Stack

- Modeling: Python 3.11, TensorFlow (Metal/Mac Optimized), NumPy.

- Simulation: C++11 (Standard Library only - No external ML frameworks).

- Architecture: Multi-Layer Perceptron (784 Input -> 128 Hidden -> 10 Output).

- Data Flow: Matrix Multiplication -> Bias Addition -> ReLU -> Softmax.

3. Results Verification

The C++ Hardware Simulator successfully replicated the Python model's behavior with bit-exact precision on test inputs.

Input: MNIST Digit '5'Python Prediction: Class 5 (99.0%)C++ Simulator Prediction: Class 5 (99.00%)

 [System] Booting AI Hardware Simulator...
 [Memory] Loading Weights...
 [System] System Ready. Waiting for Input...
 [Core] Executing Layer 1...
 [Core] Executing Output Layer...

 [Result] Prediction Probabilities:
 ...
 Digit 5: 0.9900
 ...
 [Final Answer] The Hardware predicts: 5

4. Key Architectural Concepts Demonstrated

- Memory Mapping: Loading "Weights" as read-only memory blocks.

- Control Flow: Manually sequencing the Fetch-Execute cycle for each layer.

- LU Operations: Implementing the core Multiply-Accumulate (MAC) logic from scratch.

- Hardware-Software Interface: Bridging high-level abstract models (Python) with low-level     
execution (C++).

5. How to Run

Prerequisite

- C++ Compiler (clang++ or g++)

- Python 3.x (for weight generation)

1. Generate Weights (Python)

python3 notebooks/2_baseline_model.ipynb
# This creates the /model_data directory with CSV weights


2. Compile & Run Simulator (C++)

clang++ -std=c++11 hardware_sim.cpp -o hardware_sim
./hardware_sim
