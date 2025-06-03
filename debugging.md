# **Debugging a C Credit Card Validator: Common Issues & Solutions**  
*A DevOps Journey from CLI to Web API*  

---

## **🔧 Issues Encountered & Their Fixes**  

### **1. Include Path Errors (`#include` Not Found)**  
**Error:**  
```plaintext
#include errors detected. Please update your includePath.
```
**Cause:**  
- VS Code couldn’t locate system headers (e.g., `microhttpd.h`).  
- Missing development libraries in WSL2.  

**Solution:**  
1. Install dependencies:  
   ```bash
   sudo apt-get install libmicrohttpd-dev
   ```
2. Configure VS Code’s `includePath`:  
   - Open `C/C++: Edit Configurations (UI)` in VS Code.  
   - Add:  
     ```json
     "/usr/include/**",
     "/usr/local/include/**"
     ```

---

### **2. Header File Syntax Errors**  
**Error:**  
```plaintext
warning: extra tokens at end of #ifndef directive
```
**Cause:**  
- Invalid macro name in `credit.h`:  
  ```c
  #ifndef CREDIT.H  // ← Dot (.) is illegal!
  #define CREDIT.H
  ```  
**Solution:**  
Use underscores, not dots:  
```c
#ifndef CREDIT_H  
#define CREDIT_H  
```

---

### **3. Implicit Function Declarations**  
**Error:**  
```plaintext
warning: implicit declaration of 'snprintf'
```
**Cause:**  
- Missing `#include <stdio.h>` for I/O functions.  
- Missing `#include <stdlib.h>` for `atoll()`.  

**Solution:**  
Add to `api.c`:  
```c
#include <stdio.h>   // printf(), snprintf()  
#include <stdlib.h>  // atoll()  
```

---

### **4. Function Pointer Mismatch**  
**Error:**  
```plaintext
warning: incompatible pointer type for MHD_start_daemon
```
**Cause:**  
- Newer `libmicrohttpd` uses `enum MHD_Result` instead of `int`.  

**Solution:**  
Update the handler signature:  
```c
enum MHD_Result handle_request(...) { ... }
```

## Final Thoughts
By modularizing your code (separating core logic from interfaces), you:
✅ Reuse code across projects.
✅ Simplify debugging (isolate issues).
✅ Enable multiple frontends (CLI, API, GUI).

Next steps:

    1. Add unit tests with check.h.
    2. Dockerize for easy deployment.
    3. Set up CI/CD with GitHub Actions.