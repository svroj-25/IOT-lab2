# scripts/copy_fw.py
Import("env")
import os, shutil

project_dir = env.subst("$PROJECT_DIR")
OUT = os.path.join(project_dir, ".pio", "build", "wokwi")
os.makedirs(OUT, exist_ok=True)

def copy_files(*args, **kwargs):
    build_dir = env.subst("$BUILD_DIR")
    progname = env.subst("$PROGNAME")
    for ext in [".bin", ".elf"]:
        src = os.path.join(build_dir, f"{progname}{ext}")
        if os.path.isfile(src):
            dst = os.path.join(OUT, f"firmware{ext}")
            shutil.copyfile(src, dst)
            print(f"[wokwi] successfully copied {src} -> {dst}")

# Run when binaries are freshly built
env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", copy_files)
env.AddPostAction("$BUILD_DIR/${PROGNAME}.elf", copy_files)

# Also copy immediately if binaries already exist
copy_files()


