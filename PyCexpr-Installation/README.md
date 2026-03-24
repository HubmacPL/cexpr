# cexpr — instalacja Python

Gotowy do instalacji moduł Python wiążący bibliotekę `cexpr` (ewaluator wyrażeń matematycznych napisany w C).

## Wymagania

- Python 3.12, Linux x86_64
- `pip` zainstalowany systemowo

> Jeśli używasz innej wersji Pythona lub innej platformy, musisz zbudować moduł ze źródeł (patrz sekcja niżej).

---

## Szybka instalacja (prekompilowany wheel)

```bash
pip install cexpr-0.1.0-cp312-cp312-linux_x86_64.whl --break-system-packages
```

lub jeśli masz aktywny virtualenv:

```bash
pip install cexpr-0.1.0-cp312-cp312-linux_x86_64.whl
```

Sprawdzenie instalacji:

```bash
python3 -c "import cexpr; print(cexpr.evaluate('1+2'))"
# => 3.0
python3 -c "import cexpr; print(cexpr.evaluate_with_x('x*x + 1', 5))"
# => 26.0
```

---

## Użycie w kodzie Python

```python
import cexpr

# Oblicz wyrażenie bez zmiennych
result = cexpr.evaluate("2 + 3 * 4")
print(result)  # 14.0

# Oblicz wyrażenie ze zmienną x
result = cexpr.evaluate_with_x("sin(x) + x*x", 3.14)
print(result)  # wynik dla x = 3.14
```

### Dostępne funkcje

| Funkcja | Opis |
|---|---|
| `cexpr.evaluate(expr)` | Oblicza wyrażenie tekstowe, zwraca `float` |
| `cexpr.evaluate_with_x(expr, x)` | Oblicza wyrażenie z podstawieniem zmiennej `x` |

---

## Instalacja ze źródeł (inna platforma / inna wersja Pythona)

Pobierz pełne repozytorium i uruchom:

```bash
# wymagania systemowe (Debian/Ubuntu)
sudo apt install python3-dev build-essential

# zainstaluj narzędzia build
python3 -m pip install --upgrade build setuptools wheel --break-system-packages

# zbuduj i zainstaluj
python3 -m build
python3 -m pip install dist/cexpr-*.whl --break-system-packages
```

---

## Odinstalowanie

```bash
pip uninstall cexpr
```
