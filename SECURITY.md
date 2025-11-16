# Security Policy

## Supported Versions
The project follows a rolling release model. Only the latest commit on the `main` branch is actively supported for security patches.

| Version | Supported |
|---------|-----------|
| Latest `main` branch | Yes |
| Older commits/releases | No |

## Reporting a Vulnerability
If you discover a security vulnerability, please follow these steps:

1. **Do not open a public issue.**
2. Contact the maintainer directly via **GitHub private security advisory**: <https://github.com/Benedek553/cli-calculator/security/advisories/new>
3. Provide clear, reproducible details:
   - A description of the vulnerability
   - Steps to reproduce
   - Expected vs. actual behavior
   - Potential impact

You will receive a confirmation within **48 hours**.

## Security Considerations
- The project does **not** collect or transmit any data.
- All computations are performed locally.
- No external dependencies initiate network connections.

## Responsible Disclosure
Please give the maintainers reasonable time to investigate and fix the issue before any public disclosure. Premature disclosure may put users at risk.

## Code Integrity
- All commits should be signed (recommended).
- Pull requests must pass all CI checks, including static analysis and linter validation.

## Additional Notes
- Memory safety issues (buffer overflows, undefined behavior, pointer misuse) are treated as high‑severity.
- Logic errors that may produce incorrect results are medium‑severity.
- Minor formatting or documentation flaws are low‑severity.
