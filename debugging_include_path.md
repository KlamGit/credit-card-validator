### **Issue: #include errors detected**

## Full Error Code: 
#include errors detected. Please update your includePath. Squiggles are disabled for this translation unit (/home/zinia/projects/repos/credit-card-validator/api.c).C/C++(1696)

This error occurs because the C/C++ extension in VS Code can't find the required header files (like `microhttpd.h`). Let's fix this step by step.

### **Solution 1: Install Missing Dependencies**
First, ensure `libmicrohttpd` is installed on your WSL2 system:

```bash
sudo apt-get update
sudo apt-get install libmicrohttpd-dev
```

### **Solution 2: Configure VS Code Include Path**
1. **Open VS Code Command Palette** (`Ctrl+Shift+P`).
2. Search for **"C/C++: Edit Configurations (UI)"**.
3. Under **"Include Path"**, add:
   ```
   /usr/include/**
   /usr/local/include/**
   ```
   This tells VS Code where to find system headers.

### **Solution 3: Verify with a Simple Test**
Create a test file `test_microhttpd.c`:
```c
#include <microhttpd.h>
#include <stdio.h>

int main() {
    printf("MHD version: %s\n", MHD_get_version());
    return 0;
}
```
Compile and run:
```bash
gcc test_microhttpd.c -o test -lmicrohttpd
./test
```
If this works, your environment is correctly set up.

### **Solution 4: Rebuild Your Project**
Now try building your API again:
```bash
gcc api.c credit.c -o api -lmicrohttpd
```

### **If Errors Persist**
1. **Find the Header Location**:
   ```bash
   sudo find / -name "microhttpd.h" 2>/dev/null
   ```
   Then add that path to your VS Code `includePath`.

2. **Reset VS Code IntelliSense**:
   - Delete the `.vscode/c_cpp_properties.json` file.
   - Restart VS Code.

This should resolve the include errors and enable proper IntelliSense.