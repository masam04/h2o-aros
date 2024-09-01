# H2O Projekat (AROS)

Ovaj je studentski rad za predmet AROS. Simulira stvaranje molekula vode (H2O) korišćenjem niti u C jeziku.

## Sadržaj

- **`aros-projekat.c`**: Glavni kod projekta.
- **`Makefile`**: Fajl za kompajliranje projekta.

## Kako pokrenuti projekat

1. **Kompajliranje**:
   ```bash
   make
   ```

2. **Pokreni program**:
   ```bash
   ./a.out
   ```

Program će simulirati stvaranje molekula vode.

## Opis

- Program koristi niti i semafore za sinhronizaciju.
- Kiseonik i vodonik se pojavljuju nasumično.
- Kada su dostupna dva atoma vodonika i jedan atom kiseonika, formira se molekul vode.

## Zahtevi

- **GCC kompajler** sa podrškom za niti (`pthread`).
