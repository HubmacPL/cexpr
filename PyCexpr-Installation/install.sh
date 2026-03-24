#!/bin/bash
# Szybki instalator modułu cexpr
set -e

WHEEL=$(ls "$(dirname "$0")"/*.whl 2>/dev/null | head -1)

if [ -z "$WHEEL" ]; then
    echo "Błąd: nie znaleziono pliku .whl w tym folderze."
    exit 1
fi

echo "Instalowanie: $WHEEL"
python3 -m pip install "$WHEEL" --break-system-packages

echo ""
echo "Sprawdzenie importu:"
python3 -c "import cexpr; print('OK — cexpr.evaluate(1+2) =', cexpr.evaluate('1+2'))"
