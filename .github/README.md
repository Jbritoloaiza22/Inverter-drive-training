# GitHub Workflows

## Available Workflows

### 1. **Build** (`Build.yml`)
Compiles STM32 firmware using Docker.

**Triggers:**
- Push to `main`, `develop`, `master`
- Pull requests to `main`, `develop`, `master`

**Steps:**
1. Builds Docker image with STM32 tools
2. Compiles firmware with `make`
3. Uploads artifacts (`.elf`, `.bin`, `.hex`, `.map`)

---

### 2. **Format Check** (`format-check.yml`)
Verifies code formatting compliance with clang-format.

**Triggers:**
- Push to `main`, `develop`, `master` (when `.c`, `.h`, or `.clang-format` changed)
- Pull requests to `main`, `develop`, `master` (when `.c`, `.h`, or `.clang-format` changed)

**Steps:**
1. Installs clang-format
2. Checks all C/H files formatting
3. Reports any formatting issues
4. Fails CI if issues found

**How to fix:**
- Locally: Run **"Format all C/H files"** task in VS Code
- Or manually: `clang-format -i --style=file <file>`

---

## Format Check Failures

If the format-check workflow fails:

1. **In VS Code:**
   - Press `Ctrl+Shift+B` and select **"Format all C/H files"**
   - Commit and push again

2. **Manually:**
   ```bash
   clang-format -i --style=file src/Board/HAL/uart.c
   git add .
   git commit -m "style: format code"
   git push
   ```

---

## Local Format Checking

### Available Tasks in VS Code

Open **Terminal > Run Task** or press `Ctrl+Shift+B`:

- **Format all C/H files** - Formats entire codebase
- **Format code with clang-format** - Formats current file
- **Check formatting (no changes)** - Verify without modifying

### Command Line

```bash
# Format all files (Windows)
clang-format -i --style=file **/*.c **/*.h

# Format specific file
clang-format -i --style=file src/Board/HAL/uart.c

# Check without modifying
clang-format --style=file src/Board/HAL/uart.c
```
