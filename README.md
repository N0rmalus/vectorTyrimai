#  Eksperimentiniai Vector klasės tyrimai

Šioje programoje testuojamas **class Vector** funkcionalumas kaip alternatyva **std::vector** konteineriui.

---

**test.cpp** - programa, kurioje lyginamas **class Vector** ir **std::vector** duomenų įrašymo greitis.
**vectorFunc.h** - failas, kuriame saugojama **class Vector** klasė.

## Aplankalas **main**

Šiame aplankale laikoma programa iš [Dienynas2](https://github.com/N0rmalus/Dienynas2) repozicijos su papildomai sukurta **class Vector** klase, kuri yra naudojama šioje programoje vietoje **std::vector** konteinerio.

### Pildymo sparta 

|  Įrašai           |  std::vector  |  class Vector  |  
|-------------------|---------------|----------------|
|  **10  000**      |  0.001001s    |  0s            |
|  **100 000**      |  0.001001s    |  0.002         |
|  **1 000 000**    |  0.013003s    |  0.018005s     |
|  **10 000 000**   |  0.14003s     |  0.216049s     |
|  **100 000 000**  |  1.40432s     |  2.06604s      |