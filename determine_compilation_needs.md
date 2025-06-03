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
