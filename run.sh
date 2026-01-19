#!/bin/bash

JAVAFX_PATH=PATH_TO_JAVAFX/lib

# === Create bin directory if it doesn't exist ===
mkdir -p bin
mkdir -p bin/resources

# === Compile C++ files ===
echo "Compiling C++ files..."
g++ -std=c++17 -Iinclude src/*.cpp -o bin/CatsBattle
if [ $? -ne 0 ]; then
    echo "C++ compilation failed!"
    exit 1
fi

# === Compile Java files ===
echo "Compiling Java files..."
javac --module-path "$JAVAFX_PATH" --add-modules javafx.controls,javafx.fxml,javafx.media \
    -d bin $(find src -name "*.java")
if [ $? -ne 0 ]; then
    echo "Java compilation failed!"
    exit 1
fi

# === Copy resources ===
echo "Copying resources..."
# Copy everything in src/resources
cp -r src/resources/* bin/resources/

# Copy FXML files if they are directly under src
cp src/*.fxml bin/

# === Run JavaFX application ===
echo "Running JavaFX application..."
java \
--module-path "$JAVAFX_PATH" \
--add-modules javafx.controls,javafx.fxml,javafx.media \
--enable-native-access=javafx.graphics,javafx.media \
-cp bin Main