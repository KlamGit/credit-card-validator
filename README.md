This is my first devops project, albeit very short.
I just completed one of the first week psets of the legendary CS50x called credit, and really enjoyed it due to it mathematical elements and wanted to try to make it a full on devops project.
So here it is.
The app itself is written in C.
It will check if a credit card is valid and who its issuer is.

# Credit Card Validator API (C Version)

A lightweight credit card validator microservice written in C and served over HTTP using `libmicrohttpd`. The service checks if a credit card number is valid (Luhn algorithm) and identifies its type (e.g., VISA, AMEX, etc.).

---

## 🐳 Dockerized Setup

### ✅ Prerequisites

- Docker
- GitHub Codespaces (optional, tested here)

---

## Build & Run

```bash
# Build Docker image
docker build -t credit-validator .

# Run container
docker run -p 8080:8080 --rm --name credit-api credit-validator
````

Open in browser or use curl:

```bash
curl "http://localhost:8080/?card=4111111111111111"
```

---

## ❗ Issues Faced & Solutions

| Issue                                                | Solution                                                                                                       |
| ---------------------------------------------------- | -------------------------------------------------------------------------------------------------------------- |
| 🟨 `a function may not return a value of this type`  | Corrected the return type of `handle_request` from `enum MHD_Result` to `int`.                                 |
| 🚫 Curl returned no response                         | The server wasn't binding to the correct interface. Added socket address binding using `MHD_OPTION_SOCK_ADDR`. |
| 🧊 Container ran but exited immediately              | ENTRYPOINT in Dockerfile was incorrect. Used `ENTRYPOINT ["/bin/bash", "-c"]` with correct CMD.                |
| ❗ Port binding didn't work in Codespaces             | Ensured proper port exposure via `EXPOSE 8080` and `docker run -p 8080:8080`.                                  |
| ❓ API returned `Missing 'card' parameter`            | Accessed the URL without the `?card=` parameter. Correct format is `/?card=4111111111111111`.                  |
| ❌ API returned `{"valid": false, "type": "INVALID"}` | Likely caused by invalid logic or a bad input string — will revisit later.                                     |

---

## Status

The API is now running and accessible. Logic appears to execute correctly. Project is on temporary hold for future DevOps extension.

---

## Future To-Do

* [ ] Write unit tests for credit logic.
* [ ] Add CI/CD using GitHub Actions.
* [ ] Container orchestration with Docker Compose or Kubernetes.
* [ ] Monitor with logs + metrics.
* [ ] Deploy to cloud environment (AWS / Render / Fly.io).