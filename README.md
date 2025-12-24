# Mayın Tarlası Oyunu (Minesweeper)

C++ ile geliştirilmiş, nesneye dayalı programlama ve modern C++20 özelliklerini kullanan Mayın Tarlası oyunu.

## Özellikler

- **Encapsulation (Kapsülleme)**: private/public erişim belirleyicileri
- **Inheritance (Kalıtım)**: Cell sınıfından EmptyCell ve MineCell türetilmesi
- **Polymorphism (Çok Biçimlilik)**: Virtual fonksiyonlar ve saf sanal fonksiyonlar
- **Modern C++**: Smart pointers (std::unique_ptr), lambdas, ranges
- **Bellek Yönetimi**: Dynamic memory allocation
- **Const Mekanizması**: Const metodlar ve const referanslar

## Proje Yapısı

```
├── include/
│   ├── Cell.h      # Soyut taban sınıf ve türetilmiş sınıflar
│   ├── Board.h     # Oyun tahtası yönetimi
│   └── Game.h      # Oyun mantığı
├── src/
│   ├── main.cpp    # Ana program
│   ├── Cell.cpp    # Cell sınıf implementasyonu
│   ├── Board.cpp   # Board sınıf implementasyonu
│   └── Game.cpp    # Game sınıf implementasyonu
└── CMakeLists.txt  # Build konfigürasyonu
```

## Derleme ve Çalıştırma

### Visual Studio Code ile (Recommended)

1. VS Code'da açın
2. `Ctrl+Shift+D` ile Debug sekmesine gidin
3. "Minesweeper - Build and Run" task'ini çalıştırın

### Terminal ile

```bash
mkdir build
cd build
cmake ..
cmake --build .
./minesweeper  (Linux/Mac)
minesweeper.exe  (Windows)
```

## Oyun Kuralları

- 8x8 ızgara, 10 mayın
- Boş hücre açmak: `r <satır> <sütun>` (ör: `r 3 4`)
- Bayrak koymak: `f <satır> <sütun>` (ör: `f 3 4`)
- Çıkmak: `q`

Tabloda:
- `?` = Açılmamış hücre
- `🚩` = Bayraklı hücre
- `.` = Boş (0 komşu mayın)
- `1-8` = Komşu mayın sayısı
- `💣` = Mayın (oyun bittiğinde gösterilir)

## Öğrenilen C++ Kavramları

### 1. Temel Yapılar
- `int`, `bool`, `char` veri tipleri
- `if-else`, `for`, `while` kontrol yapıları
- Dinamik diziler ve vectors

### 2. OOP Temelleri
- Sınıf tanımlama ve nesne oluşturma
- Constructor ve Destructor
- Encapsulation (private/public)

### 3. Bellek Yönetimi
- Pointer'lar ve referanslar
- `new` ve `delete` (smart pointers ile güvenlik)
- Const mekanizması

### 4. Kalıtım ve Polymorphism
- Abstract base class (Cell)
- Derived classes (EmptyCell, MineCell)
- Virtual fonksiyonlar
- Function overriding

### 5. Modern C++20
- `std::unique_ptr` (smart pointers)
- `std::vector` (dynamic arrays)
- Lambda ifadeleri
- Ranges ve algorithms

## Örnek Oynama Senaryo

```
████████████████████████████
    Mayın Tarlası Oyunu
████████████████████████████

  0 1 2 3 4 5 6 7
0 ? ? ? ? ? ? ? ?
1 ? ? ? ? ? ? ? ?
2 ? ? ? ? ? ? ? ?
3 ? ? ? ? ? ? ? ?
4 ? ? ? ? ? ? ? ?
5 ? ? ? ? ? ? ? ?
6 ? ? ? ? ? ? ? ?
7 ? ? ? ? ? ? ? ?

Kalan mayın: 10 | Açılan: 0/54

Komut: r 3 3
Komut: f 2 1
Komut: r 4 4
```

## Yapı Tasarımı

### Cell Hiyerarşisi
```
    Cell (Abstract Base Class)
    ├── Pure Virtual: reveal()
    ├── Pure Virtual: getDisplay()
    ├── Pure Virtual: getInfo()
    └── Virtual: isMine()
    
    ├── EmptyCell
    └── MineCell
```

### Sorumluluk Dağılımı
- **Cell**: Temel hücre davranışı
- **Board**: Izgara yönetimi, oyun mantığı
- **Game**: Kullanıcı arayüzü, giriş işleme

## Author
Yazılan C++ dersi kapsamında - Mayın Tarlası Projesi
