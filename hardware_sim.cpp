/*
 * Copyright (c) 2025 Ilyas El Boumashouli
 * Project: Standalone AI Hardware Simulator (The "MVP")
 * Goal: Prove we can run the Neural Network using raw C++ and CSV weights.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

// ==========================================
// 1. HARDWARE PRIMITIVES (The "Silicon")
// ==========================================

// A "Register File" to hold our matrix data
struct Matrix {
    int rows;
    int cols;
    vector<float> data;

    Matrix(int r, int c) : rows(r), cols(c), data(r * c) {}

    // Helper to access data like a 2D array
    float& at(int r, int c) {
        return data[r * cols + c];
    }
};

// The "ALU" (Arithmetic Logic Unit) - Matrix Multiplication
// This represents the physical circuit that multiplies rows by columns.
Matrix multiply(const Matrix& A, const Matrix& B) {
    if (A.cols != B.rows) {
        cerr << "Hardware Error: Dimension Mismatch! " 
             << A.cols << " != " << B.rows << endl;
        exit(1);
    }

    Matrix result(A.rows, B.cols);

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < B.cols; j++) {
            float sum = 0.0f;
            for (int k = 0; k < A.cols; k++) {
                // The core MAC (Multiply-Accumulate) operation
                sum += A.data[i * A.cols + k] * B.data[k * B.cols + j];
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

// The "Activation Unit" - ReLU
void apply_relu(Matrix& M) {
    for (float& val : M.data) {
        if (val < 0) val = 0;
    }
}

// The "Activation Unit" - Softmax
void apply_softmax(Matrix& M) {
    // For stability, we subtract the max value first
    float max_val = -1e9;
    for (float val : M.data) if (val > max_val) max_val = val;

    float sum = 0.0f;
    for (float& val : M.data) {
        val = exp(val - max_val);
        sum += val;
    }
    for (float& val : M.data) {
        val /= sum;
    }
}

// ==========================================
// 2. SYSTEM INTERFACE (Loading Data)
// ==========================================

// Helper to load CSV files into our "Memory"
Matrix load_csv(string filename, int rows, int cols) {
    Matrix M(rows, cols);
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        exit(1);
    }

    string line, val_str;
    for (int i = 0; i < rows; i++) {
        if (!getline(file, line)) break;
        stringstream ss(line);
        for (int j = 0; j < cols; j++) {
            getline(ss, val_str, ',');
            M.at(i, j) = stof(val_str);
        }
    }
    return M;
}

// ==========================================
// 3. MAIN CONTROL LOGIC
// ==========================================

int main() {
    cout << "[System] Booting AI Hardware Simulator..." << endl;

    // 1. Load the "ROM" (Weights from Python)
    cout << "[Memory] Loading Weights..." << endl;
    
    // Layer 1: 784 inputs -> 128 neurons
    Matrix W1 = load_csv("model_data/layer1_weights.csv", 784, 128);
    Matrix B1 = load_csv("model_data/layer1_biases.csv", 1, 128); // Biases are 1x128 row
    
    // Output Layer: 128 inputs -> 10 neurons
    Matrix W2 = load_csv("model_data/output_weights.csv", 128, 10);
    Matrix B2 = load_csv("model_data/output_biases.csv", 1, 10);

    cout << "[System] System Ready. Waiting for Input..." << endl;

    // 2. Create a "Test Input" (A fake image of a '5')
    // Ideally, we'd load this from CSV too, but let's make a dummy one for the test.
    // This represents the 784 pixels coming from the camera.
    Matrix Input(1, 784);
    
    // Fill it with some random noise just to prove the pipeline runs
    // (In the next step, we can load a real image)
    for(int i=0; i<784; i++) Input.at(0, i) = 0.5f; 

    // 3. EXECUTE THE PIPELINE (The "Data Flow")
    cout << "[Core] Executing Layer 1..." << endl;
    
    // Step A: Matrix Multiply (Input * W1)
    Matrix Hidden = multiply(Input, W1);
    
    // Step B: Add Bias
    // (Simplification: We just add the bias row to the result row)
    for(int i=0; i<128; i++) Hidden.at(0,i) += B1.at(0,i);

    // Step C: ReLU Activation
    apply_relu(Hidden);

    cout << "[Core] Executing Output Layer..." << endl;

    // Step D: Matrix Multiply (Hidden * W2)
    Matrix Output = multiply(Hidden, W2);

    // Step E: Add Bias
    for(int i=0; i<10; i++) Output.at(0,i) += B2.at(0,i);

    // Step F: Softmax
    apply_softmax(Output);

    // 4. REPORT RESULTS
    cout << "\n[Result] Prediction Probabilities:" << endl;
    int best_digit = 0;
    float best_prob = 0.0f;

    for (int i = 0; i < 10; i++) {
        cout << "Digit " << i << ": " << fixed << setprecision(4) << Output.at(0, i) << endl;
        if (Output.at(0, i) > best_prob) {
            best_prob = Output.at(0, i);
            best_digit = i;
        }
    }

    cout << "\n[Final Answer] The Hardware predicts: " << best_digit << endl;

    return 0;
}