## **🔍 Debugging Cheat Sheet**  
| Symptom | Likely Cause | Fix |  
|---------|--------------|-----|  
| `#include` not found | Missing dev package | `sudo apt-get install libXXX-dev` |  
| Implicit function warnings | Missing header | Add `#include <header.h>` |  
| Pointer type mismatches | API version changes | Update function signatures |  
| Undefined reference | Forgot `-l` flag | Add `-lmicrohttpd` |  