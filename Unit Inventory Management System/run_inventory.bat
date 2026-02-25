@echo off
title Inventory Management System
echo Launching Inventory Management System...
if exist "inventory.exe" (
    .\inventory.exe
) else (
    echo Error: inventory.exe not found. Please compile the project first.
    pause
)
