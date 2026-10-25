"""Creates .venv at the repo root with nanobind (needed to build the module) and
installs the inharmonic Python package in editable mode with its dependencies.

Run once with the Python you want to use, then re-run after changing
python/pyproject.toml:

    python scripts/setup_venv.py
"""

import subprocess
import sys
import venv
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
VENV = ROOT / ".venv"


def main() -> None:
    if not VENV.exists():
        venv.create(VENV, with_pip=True)
    python = VENV / ("Scripts/python.exe" if sys.platform == "win32" else "bin/python")

    def pip(*args: str) -> None:
        subprocess.run([str(python), "-m", "pip", *args], check=True)

    pip("install", "--upgrade", "pip")
    pip("install", "nanobind")
    pip("install", "-e", str(ROOT / "python"))


if __name__ == "__main__":
    main()
