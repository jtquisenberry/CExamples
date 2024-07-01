

```c++
#include <iostream>

int main() {
    wchar_t* wc = new wchar_t[260] {0};
    wc = (wchar_t*)L"Out String\n";
    std::wcout << wc;
    return 0;
}
```
