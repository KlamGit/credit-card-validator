## **🖥️ Understanding the Compilation Process**  

### **Q1: Why Build Both CLI and API Versions?**  
| Version | Purpose | When to Use |  
|---------|---------|-------------|  
| **CLI** | Command-line tool | Testing locally, quick validation |  
| **API** | HTTP microservice | Web/mobile apps, integrations |  

**Example Workflows:**  
- **CLI:**  
  ```bash
  ./cli  
  Enter card number: 378282246310005  
  AMEX  
  ```
- **API:**  
  ```bash
  curl "http://localhost:8080/validate?card=378282246310005"
  {"valid": true, "type": "AMEX"}
  ```

---

### **Q2: Decoding the Compile Commands**  
#### **For the API:**  
```bash
gcc api.c credit.c -o api -lmicrohttpd
```
- `api.c`: HTTP server code.  
- `credit.c`: Core validation logic.  
- `-o api`: Names the output binary `api`.  
- `-lmicrohttpd`: Links the HTTP library.  

#### **For the CLI:**  
```bash
gcc main.c credit.c -o cli
```
- `main.c`: Handles terminal I/O.  
- No `-lmicrohttpd`: No HTTP dependencies.  

**Key Insight:**  
- The **same core logic** (`credit.c`) is reused in both.  
- Only the **interface** (CLI vs. API) changes.  

---

### **Q3: Why Clean Previous Builds?**  
Running:  
```bash
rm -f api cli  # Delete old binaries
```
**Prevents:**  
- Stale executables causing unexpected behavior.  
- Linking errors during recompilation.  

**Best Practice:**  
Always clean before rebuilding in C!  

---

## **🚀 How to Determine Compilation Needs**  
1. **Identify Dependencies:**  
   - Use `#include` directives as clues.  
   - Example: `#include <microhttpd.h>` → Requires `-lmicrohttpd`.  

2. **Check for External Libraries:**  
   ```bash
   ldd ./api  # Lists shared library dependencies
   ```
   Output:  
   ```plaintext
   libmicrohttpd.so.12 => /usr/lib/x86_64-linux-gnu/libmicrohttpd.so.12
   ```

3. **Separate Interface from Logic:**  
   - Shared logic → Compiled once (`credit.c`).  
   - Interface-specific code → Added as needed (`main.c`/`api.c`).  