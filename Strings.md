# char*
## Conversion to `wchar_t*`
```c++
#include <iostream>
#include <cstring>

int main() {
    const char *s = "Out String";
    size_t size = strlen(s) + 1;  
    wchar_t* wc = new wchar_t[size]; 
    mbstowcs(wc, s, size);

    // size_t outSize;                               // Secure version in Visual Studio
    // mbstowcs_s(&outSize, wc, size, s, size-1);    // Secure version in Visual Studio
    std::wcout << wc << std::endl;
    
    return 0;
}
```


# wchar_t*

## Assignment with `new`, Reassignment

```c++
#include <iostream>

int main() {
    wchar_t* wc = new wchar_t[260] {0};
    wc = (wchar_t*)L"Out String\n";
    std::wcout << wc;
    return 0;
}
```

## Assignment without `new`, Reassignment

```c++
#include <iostream>

int main() {
    wchar_t* wc = {0};
    wc = (wchar_t*)L"Out String\n";
    std::wcout << wc;
    return 0;
}
```


# wchar_t
## Reassignment

```c++
#include <iostream>

int main() {
    wchar_t wc[260] = {0};
    wcscpy(wc, L"Out String\n");
    std::wcout << wc;
    return 0;
}
```
