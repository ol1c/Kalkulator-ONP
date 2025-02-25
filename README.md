# Kalkulator ONP

> Prosta aplikacja w konsoli obliczająca wg. formatu ONP (Odwrócona Notacja Polska).
>
> Projekt stworzony na potrzeby przedmiotu Algorytmy i Struktury Danych.

## ⚙️ Użyte technologie

- **C++** – Główny język programowania użyty do stworzenia aplikacji kalkulatora.

## ✖️➗ Przykładowe użycie
**Przykładowy input**:
```input
3
( ( 8 + 16 ) * ( 3 + 8 ) * N ( 8 * 12 ) ) . 
( 11 - 8 * N ( 11 + 17 ) ) . 
( ( 15 - 9 ) * ( 8 / 0 ) - N ( 9 / 0 ) ) . 
```
**Output**:
```output
8  16  +  3  8  +  *  8  12  *  N  *  
+ 16 8 
+ 8 3 24 
* 11 24 
* 12 8 264 
N 96 264 
* -96 264 
-25344 

11  8  11  17  +  N  *  -  
+ 17 11 8 11 
N 28 8 11 
* -28 8 11 
- -224 11 
235 

15  9  -  8  0  /  *  9  0  /  N  -  
- 9 15 
/ 0 8 6 
ERROR 
```

