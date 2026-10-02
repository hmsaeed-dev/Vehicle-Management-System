#!/usr/bin/env bash
# ==============================================================================
# Vehicle Management System - Linux / Codespaces Build & Launch Script
# ==============================================================================

set -e

echo "=================================================="
echo "  Vehicle Management System (VMS) - Linux Build  "
echo "=================================================="

# Ensure output directory exists if needed
mkdir -p build

echo "[BUILD] Compiling C++17 source modules..."
g++ -std=c++17 -Wall -Wextra -IInclude Source/*.cpp -o VehicleManagSys

echo "[SUCCESS] Compilation successful!"
echo "[RUN] Starting Vehicle Management System..."
echo "--------------------------------------------------"

# Run the binary from current working directory
./VehicleManagSys
