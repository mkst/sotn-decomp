import os
import sys

from typing import Optional
from pathlib import Path

from src.splat.util import options

sys.path.append(f"{os.getcwd()}/{options.opts.extensions_path}")
from raw import PSXSegRaw

class PSXSegTilelayout(PSXSegRaw):
    pass

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.tilelayout.bin"
