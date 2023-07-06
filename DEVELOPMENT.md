# Development guide

This document describes the process for setting up the utilities needed to build this project on your local machine.

## Getting started

## Installing tools

[todo]: # "Add Linux install guide"

---

### chocolatey

In PowerShell:

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

Restart PowerShell.

---

### clang

In PowerShell:

```powershell
choco install clang; refreshenv;
```

---

### cmake

In PowerShell:

```powershell
choco install cmake; refreshenv;
```

---

## Coding conventions

[todo]: # "Add/remove some."

- We use C++23.
- We use [cmkr](https://github.com/cpp-build/cmkr) for managing CMakeLists.txt. Click [here](https://cmkr.build/) for documentation.
- We don't use non-standart extensions. `__attribute__`, `__forceinline`, inline assembly, `__COUNTER__`, `__PRETTY_FUNCTION__`, the `foo?:bar` operators.
- We use `using` instead of `typedef`.

## Contirbuting

> Any contribution you make are **greatly** appreciated!

1. Fork the project

```commandline
git clone https://github.com/es3n1n/portal2-internal && cd portal2-internal
```

2. Create your feature branch

```commandline
git checkout -b feat/{your-feature-name}
```

3. Commit your changes

```commandline
git commit -m 'feat: add {your feature name}`
```

4. Push out the branch

```commandline
git push origin feat/{your-feature-name}
```

5. Open a Pull Request
