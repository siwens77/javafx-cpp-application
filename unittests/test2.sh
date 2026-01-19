#!/bin/bash

JAVAFX_PATH=PATH_TO_JAVAFX/lib
JUNIT_PATH="lib/junit-4.13.2.jar:lib/hamcrest-core-1.3.jar"

mkdir -p bin

# === 1. Compile Main Project ===
echo "Compiling Project Java files..."
javac --module-path "$JAVAFX_PATH" --add-modules javafx.controls,javafx.fxml,javafx.media \
    -d bin $(find src -name "*.java")

if [ $? -ne 0 ]; then
    echo "❌ Project Java compilation failed!"
    exit 1
fi

echo "=============================="
echo "   Compiling Unit Tests...    "
echo "=============================="

# === 2. Compile Tests (Needs JavaFX path too!) ===
javac --module-path "$JAVAFX_PATH" --add-modules javafx.controls,javafx.fxml,javafx.media \
      -cp "bin:$JUNIT_PATH" \
      -d bin unittests/tests.java

if [ $? -eq 0 ]; then
    echo "Compilation Successful!"
    echo "--------------------------------"
    echo "   Running Java Tests..."
    echo "--------------------------------"

    # === 3. Run Tests (Needs JavaFX path too!) ===
    java --module-path "$JAVAFX_PATH" --add-modules javafx.controls,javafx.fxml,javafx.media \
         --enable-native-access=javafx.graphics,javafx.media \
         -cp "bin:$JUNIT_PATH" \
         org.junit.runner.JUnitCore tests
    
    echo "--------------------------------"
else
    echo "❌ Test Compilation Failed."
    exit 1
fi